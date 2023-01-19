# Cache-Simulator-in-C

In this programming project, you will need to develop a cache simulator and to measure the cache 
performance (miss ratio, etc.). Input to the cache simulator is a list of memory addresses accessed. 
Outputs from the cache simulator are cache performance metrics such as cache miss ratio. It is 
mandatory that you write this project in C. 
Detailed description:
* The cache simulator will run based on a memory trace file that is a list of memory addresses 
referenced during the execution of a program. The cache simulator should output cache statistics 
such as miss ratio, etc.
 * Assume the following cache parameters as the basis.
 * 64KB cache and 64B cache block
 * Single-level cache
 * Direct-mapped cache
 * Write-through policy
 * Data/instruction integrated cache
However, your simulator will run the simulation a couple more times to test different cache configurations (a total of 12 cases):
 * Block size varies 16B~128B (4 cases)
 * Direct-mapped cache, 4-set associative cache, and 8-set associative cache (3 cases)
Your job is to build a simulator that reads a memory trace and simulates the action of a cache. Your simulator should keep track of which memory blocks are loaded into cache. As it processes each memory reference from the trace, it should check to see if the corresponding memory address is in the cache or not. 
* Of course, this is just a simulation of cache, so you do not actually need to read and write data from memory. Just keep track of which blocks are in the cache. 
* Write-through policy is assumed in this assignment. Since we do not actually read or write, write policy does not affect the cache performance such as miss ratio. Memory trace file:
* As an input to the cache simulator, you will use four memory traces – two integer programs and two floating point programs. You can access the fourtrace files (each about 15MB) from the class webpage but can also be found from https://www.spec.org/cpu92/cint92.html:
 * 085.gcc.din
 * 022.li.din
 * 078.swm256.din
 * 047.tomcatv.din
Each trace is a real recording of a running program, taken from the SPEC benchmarks. Each trace only consists of one million memory accesses taken from the beginning of each program. 
Each trace is a series of lines, each listing three fields per line: “accesstype address size/data.” Address and size/data are hexadecimal. Accesstype is
 0 read
 1 write
 2 instruction fetch
* Addresses are byte addresses. In other words, memory address 0000000c mean the 13th byte from the top of the memory. Every memory reference accesses a word data (4 bytes) regardless the size/data field. For example, “1 0000000c 0” denotes that a word data is written on memory address 0000000c. In other words, data at memory address 0000000c, 0000000d, 0000000e and 0000000f will be written. For this reason, all memory addresses in the trace files are word-aligned.
* For more information about the trace files, please visit SPEC (Standard Performance Evaluation  Corporation) webpage: http://www.spec.org/benchmarks.html#cpu Testing 
Please test the 4 test traces under the 12 different configurations (Block size - 16B, 32B, 64B and 128B; 
Mapping – direct, 4-way set associative, and fully associative

# To Compile:
  	1) Open cmd in same folder as cache.c
	2) gcc cache.c
	3) executable file a.exe will be created in folder same as cache.c
# To Run:
 Windows Powershell:
	1)open windows power shell in same folder as a.exe executable file
 	1) ./a or ./a.exe
	2) Make Sure that all the 4 trace files are in the same folder as the a.exe as I have hardcoded the files names in code.
or

Windows cmd:
 1)open windows cmd in same folder as a.exe executable file
 2) a.exe
 3) Make Sure that all the 4 trace files are in the same folder as the a.exe as I have hardcoded the files names in code.
