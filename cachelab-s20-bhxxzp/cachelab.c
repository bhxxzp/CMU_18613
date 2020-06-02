/*
 * cachelab.c - Cache Lab helper functions
 */
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "cachelab.h"


trans_func_t func_list[MAX_TRANS_FUNCS];
int func_counter = 0;

/*
 * printSummary - Summarize the cache simulation statistics. Student
 *                cache simulators must call this function in order to
 *                be properly autograded.
 */
void printSummary(long hits, long misses, long evictions,
                  long dirty_bytes, long dirty_evictions)
{
    printf("hits:%ld misses:%ld evictions:%ld dirty_bytes_in_cache:%ld dirty_bytes_evicted:%ld\n",
            hits, misses, evictions, dirty_bytes, dirty_evictions);
    FILE* output_fp = fopen(".csim_results", "w");
    assert(output_fp);
    fprintf(output_fp, "%ld %ld %ld %ld %ld\n", hits, misses, evictions,
            dirty_bytes, dirty_evictions);
    fclose(output_fp);
}

/*
 * initMatrix - Initialize the given matrices
 */
void initMatrix(size_t M, size_t N, double A[N][M], double B[M][N])
{
    size_t i, j;
    srand(time(NULL));
    for (i = 0; i < N; i++){
        for (j = 0; j < M; j++){
	    /* Initialize with data that can't be represented as int or float */
            A[i][j] = (double) rand()/8.0 + 1e10;
            B[j][i] = (double) rand()/8.0 + 1e10;
        }
    }
}

/*
 * copyMatrix - Make a copy of a matrix
 */
void copyMatrix(size_t M, size_t N, double Adst[N][M], const double Asrc[N][M])
{
    size_t i, j;
    for (i = 0; i < N; i++)
	for (j = 0; j < M; j++)
	    Adst[i][j] = Asrc[i][j];
}

/*
 * correctTrans - baseline transpose function used to evaluate correctness
 */
void correctTrans(size_t M, size_t N, const double A[N][M], double B[M][N])
{
    size_t i, j;
    double tmp;
    for (i = 0; i < N; i++){
        for (j = 0; j < M; j++){
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}



/*
 * registerTransFunction - Add the given trans function into your list
 *     of functions to be tested
 */
void registerTransFunction(void (*trans)(size_t M, size_t N, const double[N][M], double[M][N], double *T),
                           const char *desc)
{
    func_list[func_counter].func_ptr = trans;
    func_list[func_counter].description = desc;
    func_list[func_counter].correct = false;
    func_list[func_counter].num_hits = 0;
    func_list[func_counter].num_misses = 0;
    func_list[func_counter].num_evictions =0;
    func_counter++;
}
