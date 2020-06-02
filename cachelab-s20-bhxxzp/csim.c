/*
 * name: Peng Zeng
 * AndrewID: pengzeng
 */
#include "cachelab.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Line structure
// Define the line in each set.
// Each time we use one line, the LRU of that line will plus one.
typedef struct {
    int valid;
    long long Tag;
    bool dirty;
    int LRU;
} line;

// Help function
void printHelp() {
    printf("\nHelp function\n"
           "Usage: ./csim-ref [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n"
           "-h: Optional help flag that prints usage info\n"
           "-v: Optional verbose flag that displays trace info\n"
           "-s <s>: Number of set index bits (S = 2s is the number of sets)\n"
           "-E <E>: Associativity (number of lines per set)\n"
           "-b <b>: Number of block bits (B = 2b is the block size)\n"
           "-t <tracefile>: Name of the memory trace to replay\n");
};

// FreeCache Function
// Using to free the whole memory
void freeCache(line **cache, int size) {
    for (int i = 0; i < size; i++) {
        free(cache[i]);
    }
    free(cache);
};

void initiateCache(line **cache, int size) {}

// Main function, start from here
int main(int argc, char **argv) {
    // Use getopt function to store input
    int option;
    int s;
    int E;
    int b;
    char *fileroad;
    bool verbose = false;
    while ((option = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (option) {
        case 'h':
            printHelp();
            break;
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
            fileroad = optarg;
            break;
        default:
            break;
        };
    };

    // Create the cache, with s sets, E lines, b blocks
    // Size of cache = S * B * E, we don't need to consider B in Part A
    int S = 1 << s;
    int B = 1 << b;
    // Initiate the sets, 2D
    line **cache = (line **)malloc(sizeof(line *) * S);
    // Can' malloc, free
    if (cache == NULL)
        free(cache);
    for (int i = 0; i < S; i++) {
        // Initiate total lines in each set
        cache[i] = (line *)malloc(sizeof(line) * E);
        // Can't malloc, free
        if (cache[i] == NULL)
            free(cache[i]);
    };

    // Initiate the cache
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < E; j++) {
            cache[i][j].valid = 0;
            cache[i][j].Tag = 0;
            cache[i][j].dirty = 0;
            cache[i][j].LRU = E;
        }
    }

    // Open the file
    FILE *file = fopen(fileroad, "r");
    int Hits = 0;    // Calculate the number of Hit
    int Misses = 0;  // Calculate the number of Misses
    int Evicts = 0;  // Calculate the number of Eviction
    int D_Cache = 0; // Calculate the number of Dirtybyte in Cache
    int D_Evict = 0; // Calculate the number of Dirty in each calculation
    char instruction;
    long unsigned address;
    int size;
    int tag_index = 64 - s - b; // Using to choose to tag
    long long unsigned tag;     // Store the tag
    long unsigned set;          // Store the set

    // Read each instructor in file
    while ((fscanf(file, " %c %lx, %d", &instruction, &address, &size)) != -1) {
        tag = address >> (s + b);
        if ((s + b) != 0) {
            set = (address << tag_index) >> (64 - s);
        } else {
            set = 0;
        }
        line *row = cache[set];

        bool hit = false;
        bool write = false;
        bool miss = true;
        int i;
        int j;

        for (i = 0; i < E; i++) {
            // There is a line valid and it is our aim, then Hits++
            if ((row[i].Tag == tag) && (row[i].valid == 1)) {
                hit = true;
                miss = false;
                // eviction = false;
                Hits++;
                if (instruction == 'S') {
                    row[i].dirty = true;
                }
                // LRU look likes set the line into top of the stack
                // Other lines move down
                int temp = row[i].LRU;
                row[i].LRU = E;
                for (j = 0; j < E; j++) {
                    if ((i != j) && (row[j].LRU > temp)) {
                        row[j].LRU--;
                    }
                }
                break;
            }
        }
        // If miss, then Misses++
        if (miss) {
            Misses++;
            for (i = 0; i < E; i++) {
                if (row[i].valid == 0) {
                    hit = false;
                    write = true;
                    row[i].valid = 1;
                    row[i].Tag = tag;
                    row[i].LRU = E;

                    // LRU: Put one of the empty line to top
                    // Other lines with valid move down
                    for (j = 0; j < E; j++) {
                        if ((i != j) && (row[j].LRU == 1)) {
                            row[j].LRU--;
                        }
                    }

                    if (instruction == 'S') {
                        row[i].dirty = true;
                    }
                    break;
                }
            }

            // Miss and Evict
            if (!write) {
                Evicts++;
                int h;
                int min = E + 1;
                int temp;

                // LRU: look like choosing the line which least recently used
                for (h = 0; h < E; h++) {
                    temp = row[h].LRU;
                    if (temp < min) {
                        min = temp;
                    }
                }

                for (j = 0; j < E; j++) {
                    if (row[j].LRU == min) {
                        if (row[j].dirty) {
                            D_Evict += B;
                        }
                        row[j].Tag = tag;
                        row[j].LRU = E;
                        row[j].dirty = false;
                        if (instruction == 'S') {
                            row[j].dirty = true;
                        }
                        for (int k = 0; k < E; k++) {
                            row[k].LRU--;
                        }
                        break;
                    }
                }
            }
        }

        // If input v, print out the result of each line
        if (verbose) {
            printf("%c %lx,%d", instruction, address, size);
            if (hit) {
                printf(" hit\n");
            }
            if (!hit && write) {
                printf(" miss\n");
            }
            if (!hit && !write) {
                printf(" miss eviction\n");
            }
        }
    }

    // Calculate the Dirtybyte in Cache
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < E; j++) {
            if (cache[i][j].dirty) {
                D_Cache += B;
            }
        }
    }

    // Print Summary
    printSummary(Hits, Misses, Evicts, D_Cache, D_Evict);

    // Free the whole memory
    freeCache(cache, S);

    return 0;
}