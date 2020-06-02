#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include "cachelab.h"

int main(int argc, char* argv[]) {
    // Read from command line and update variables
    int opt; int s; int E; int b; char* filename; bool verbose = false;
    while ((opt = getopt(argc, argv, "s:E:b:t:v")) != -1) {
      switch(opt) {
      case 'v':
        verbose = true;
        break;
      case 's':
        s = atoi(optarg);
        break;
      case 'E':
        E = atoi(optarg);
        break;
      case 'b':
        b = atoi(optarg);
        break;
      case 't':
        filename = optarg;
        break;
      default:
        printf("Error\n");
        break;
      }
    }

    // Define what a line is in the cache
    struct line {
      int valid;
      long long tag;
      bool dirty;
      int LRU;
    };
    typedef struct line line;

    // Allocate a cache (2D array) of "line" structs
    int S = 1<<s; int B = 1<<b; int i; int j; int k;

    line** cache = malloc(sizeof(line*)*S);
    for (i=0; i < S; i++) {
      cache[i] = (line *)malloc(sizeof(line)*E);
    }

    // Initliaze values
    for (i = 0; i < S; i++) {
      for (j = 0; j < E; j++) {
        cache[i][j].valid = 0;
        cache[i][j].tag = 0;
        cache[i][j].dirty = false;
        cache[i][j].LRU = E;
      }
    }

    // Retrieve trace data and set variables
    FILE* trace = fopen(filename,"r");

    int hits = 0; int misses = 0;

    int evictions = 0; int dirty_bytes = 0; int dirty_evictions = 0;

    char instruction; long long unsigned address; int size;

    long long unsigned tbits; long long unsigned sbits;

    int t_index = s+b; int t = 64-t_index; int s_index = t+b;

    bool hit; bool write; bool eviction;

    // Read from trace file and execute each instruction
    while (fscanf(trace, " %c %llx,%d",&instruction,&address,&size)!=-1) {

      // Find Tag
      tbits = address>>t_index;

      // Find Set
      if (t!=64) sbits = (address<<t)>>s_index;
      if (t==64) sbits = 0; // Edge Case
      line* row = cache[sbits];

      // Set Flags
      hit = false;
      write = false;
      eviction = false;
      bool cdirty = false;

      // Iterate through the Set and Look for Hits
      for (i = 0; i < E; i++) {

        if ((row[i].tag == tbits)&&(row[i].valid == 1)) hit = true;

        // Found a Hit
        if (hit) {

          hits++;

          // Decrement LRU position of lines that were previously behind
          int prev = row[i].LRU;
          row[i].LRU = E;

          for (j = 0; j < E; j++) {
            if ((i != j) && (row[j].LRU>prev)) row[j].LRU--;
          }

          // Account for dirty Bytes
          if (instruction == 'S') {
            row[i].dirty = true;
            cdirty = true;
          }
        }
        if (hit) break;
      }

      // NO HITS --> MISS
      if (!hit) {

        misses++;

        // Look for open spot in the set
        for (i = 0; i < E; i++) {

          if (row[i].valid == 0) {

              // Write into open spot in cache
              write = true;
              row[i].valid = 1;
              row[i].tag = tbits;
              row[i].LRU = E;

              // Decrement LRU position of valid lines
              for (j = 0; j < E; j++) {
                if ((i != j) && (row[j].valid == 1)) row[j].LRU--;
              }

              // Account for dirty Bytes
              if (instruction == 'S') {
                row[i].dirty = true; // Dirty Bytes
                cdirty = true;
              }

          }
          if (write) break;
        }

        // No open spot in set -> eviction
        if (!write) {

          evictions++;

          // Search for LRU line
          for (j = 0; j < E; j++) {

            if (row[j].LRU == 1) {
              // Evitct old Line and write through
              eviction = true;
              if (row[j].dirty) dirty_evictions+=B; // Possible dirty_eviction
              row[j].tag = tbits;
              row[j].LRU = E;
              row[j].dirty = false;

              // Account for new dirty Bytes
              if (instruction == 'S') {
                row[j].dirty = true;
                cdirty = true;
                }

              // Decrement LRU position of all other lines
              for (k = 0; k < E; k++) {
                if (k != j) row[k].LRU--;
              }
            }
            if (eviction) break;
          }

        }
      }

      // Verbose Option
      if (verbose) {
        printf("%c %llx,%d",instruction,address,size);
        if (hit) printf(" hit\n");
        if (!hit && write) printf(" miss\n");
        if (!hit && !write) printf(" miss eviction\n");
        if (cdirty) printf("dirty!\n");
      }
    }

    // Caluclate # of dirty bytes at end of simulation
    for (i = 0; i < S; i++) {
      for (j = 0; j < E; j++) {
        line tmp = cache[i][j];
        if (tmp.dirty) {
          dirty_bytes+=B;
          printf("i = %d, j = %d\n", i, j);}
      }
    }

    // Print Summary
    printSummary(hits,misses,evictions,dirty_bytes,dirty_evictions);

    // Free Cache memory
    for (i = 0; i < s; i++) {
      free(cache[i]);
    }
    free(cache);

    // Return from Main
    return 0;
}