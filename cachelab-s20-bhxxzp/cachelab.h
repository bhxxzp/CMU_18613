/*
 * cachelab.h - Prototypes for Cache Lab helper functions
 */

#include <stdlib.h>
#ifndef CACHELAB_TOOLS_H
#define CACHELAB_TOOLS_H

/* Maximum number of transpose functions that can be registered */
#define MAX_TRANS_FUNCS 100
/* Maximum value of M or N in transpose functions */
#define MAXN 256
/* Number of temp's allocated in temp array.  Designed to fill cache to capacity */
#define TMPCOUNT 256


typedef struct trans_func {
    void (*func_ptr)(size_t M, size_t N, const double[N][M], double[M][N], double *);
    const char *description;
    char correct;
    long num_hits;
    long num_misses;
    long num_evictions;
} trans_func_t;

/*
 * printSummary - This function provides a standard way for your cache
 * simulator * to display its final hit and miss statistics
 */
void printSummary(long hits,  /* number of  hits */
                  long misses, /* number of misses */
                  long evictions, /* number of evictions */
                  long dirty_bytes, /* number of dirty bytes in cache at the end */
                  long dirty_evictions); /* number of evictions of dirty lines*/

/* Fill the matrix with data */
void initMatrix(size_t M, size_t N, double A[N][M], double B[M][N]);

/*
 * copyMatrix - Make a copy of a matrix
 */
void copyMatrix(size_t M, size_t N, double Adst[N][M], const double Asrc[N][M]);


/* The baseline trans function that produces correct results. */
void correctTrans(size_t M, size_t N, const double A[N][M], double B[M][N]);

/* Add the given function to the function list */
void registerTransFunction(void (*trans)(size_t M, size_t N, const double[N][M], double[M][N], double *),
                           const char *desc);

#endif /* CACHELAB_TOOLS_H */
