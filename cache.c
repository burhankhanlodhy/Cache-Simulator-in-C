#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Line{
    unsigned int valid;
	unsigned int tag;
    unsigned int data;
	unsigned int lru;
};
typedef struct Line Line;

// *************** Forward Declaration *************** //

void cache_simulate(int cache_size, int block_size, int set, char* trace_file);
Line **makeCache(int S, int E);
unsigned int getInfo(unsigned int a, unsigned int *set, int set_bits, int tag_bits);
void checkCache(Line **my_cache, unsigned int set, unsigned int tag, int way_size,
unsigned int *hits,  unsigned int *misses, unsigned int *evictions);
void update_lru(Line *set, int line, int way_size); 

int main() {
    char trace[4][30] = {
        "022.li.din",
        "047.tomcatv.din",
        "078.swm256.din",
        "085.gcc.din"
    };
    int way[3] = { 1, 4, 8 };
    int block[4] = { 16, 32, 64, 128 };
    int cache_size = 64 * 1024;
    for (int k = 0; k < 4; k++)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++) {
                cache_simulate(cache_size, block[j], way[i], trace[k]);
            }
}

void cache_simulate(int cache_size, int block_size, int way_size, char* trace_file) {
    int type;
    unsigned int address;
    unsigned int value;
    unsigned int tag;
    unsigned int set;
    unsigned int data;
    int sets = cache_size / block_size / way_size;
    unsigned int set_bits = log2(sets);
    unsigned int tag_bits = 32 - set_bits - log2(block_size);
    Line **cache = makeCache(sets, way_size);

    unsigned int hits = 0;
    unsigned int misses = 0;
    unsigned int evictions = 0;
    unsigned int placements = 0;
    unsigned int replacements = 0;

    FILE *trace = fopen(trace_file, "r"); // read in file
    int ret = fscanf(trace, "%d %x %x", &type, &address, &value);
    while (ret != -1)
    {
        if (type == 2) data = value;
        else if (type == 1 || type == 0) checkCache(cache, set, tag, way_size, &hits, &misses, &evictions);
        tag = getInfo(address, &set, set_bits, tag_bits);
        ret = fscanf(trace, "%d %x %x", &type, &address, &value);
    }
    printf("%s\t ", trace_file);
    if (way_size == 1) printf("Direct-mapped cache\t ");
    else printf("%d-set associative cache\t ", way_size);
    printf("block size %dB\n", block_size);
    printf("miss ratio = %.2f%%, total references = %d, placements = %d, replacements %d\n",
           100.0 * (float)misses / (float)(hits + misses), misses + hits, misses - evictions, evictions);
	fclose(trace);
}

/*
 * Function allocates memory for a cache with S sets and E lines.
 * @param S - Sets in cache
 * @param E - Lines per Set
 * @return - 2D array of lines
 */
Line **makeCache(int S, int E) {
	int i;
	int j;
	Line** cache1 = malloc(sizeof(Line*)*S);
	for(i = 0; i < S; i++) {
		cache1[i] = malloc(sizeof(Line)*E);
		for(j = 0; j < E; j++) {
			cache1[i][j].valid = 0;
			cache1[i][j].lru = j;
		}
	}
	return cache1;
}

/* Function gets set number and tag from address
 * @param a - memory address to get info from
 * @param set - variable to hold returned set number
 * @param set_bits
 * @param tag_bits
 * @return - the tag
 */
unsigned int getInfo(unsigned int a, unsigned int *set, int set_bits, int tag_bits) {
	*set = (a<<tag_bits)>>(32 - set_bits);
	return a>>(32 - tag_bits);
}

/*
 * Function looks for tag in a line, updates valid and LRU, counts hits/miss/eviction
 * @param my_cache - cache structure
 * @param set - set number
 * @param tag - tag we are looking for
 * @param way_size - way count
 * @param hits - number of times we get a hit
 * @param misses - number of times we get a miss
 * @param evictions - number of times we replace a value
 */
void checkCache(Line **my_cache, unsigned int set, unsigned int tag, int way_size,
unsigned int *hits,  unsigned int *misses, unsigned int *evictions) {
	int i;
	for(i = 0; i < way_size; i++) {
		if(my_cache[set][i].valid != 0 && tag == my_cache[set][i].tag) {
			*hits = *hits + 1;
			update_lru(my_cache[set], i, way_size);
			return;
		}
	}
	for(i = 0; i < way_size; i++) {
		if(my_cache[set][i].lru == (way_size - 1)) {
            if(my_cache[set][i].valid != 0) *evictions = *evictions + 1;
			my_cache[set][i].valid = 1;
			my_cache[set][i].tag = tag;
			update_lru(my_cache[set], i, way_size);
			*misses = *misses + 1;
			return;
		}
	}
}

/*
 * Function updates LRU bit
 * @param set - set being updated
 * @param line - line being accessed
 * @param way_size - way count
 */
void update_lru(Line *set, int line, int way_size) {
	int i;
	for(i = 0; i < way_size; i++){
		if(i != line){
			if(set[i].lru < set[line].lru){
				set[i].lru = set[i].lru++;
			}
		}
	}
	set[line].lru = 0;
}

