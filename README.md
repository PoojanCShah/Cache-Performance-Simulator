# COL216 LAB3 : Cache Simulator
1. To run this project : `make cacheSim`
2. To get Simulaor output :
 ```./cacheSim <numSets> <numBlocks> <blockSize> <write-allocate/no-write-allocate> <write-through/write-back> <lru/fifo> < <tracefile>```
3. As an example, a sample [trace file](gcc.trace) is also provided
4. To remove executables : `make clean`
5. [Please see the analysis report here](report.pdf)

## Example Usage : 
```
$ ./cacheSim 16 16 16 write-allocate write-through fifo < gcc.trace

Total loads: 318197
Total stores: 197486
Load hits: 310877
Load misses: 7320
Store hits: 186992
Store misses: 10494
Total cycles: 27389883
```