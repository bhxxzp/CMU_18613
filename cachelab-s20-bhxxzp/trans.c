/*
 * Name: Peng Zeng
 * AndrewID: pengzeng
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(size_t M, size_t N, double A[N][M], double B[M][N], double *tmp);
 * A is the source matrix, B is the destination
 * tmp points to a region of memory able to hold TMPCOUNT (set to 256) doubles
 * as temporaries
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 2KB direct mapped cache with a block size of 64 bytes.
 *
 * Programming restrictions:
 *   No out-of-bounds references are allowed
 *   No alterations may be made to the source array A
 *   Data in tmp can be read or written
 *   This file cannot contain any local or global doubles or arrays of doubles
 *   You may not use unions, casting, global variables, or
 *     other tricks to hide array data in other forms of local or global memory.
 */
#include "cachelab.h"
#include "contracts.h"
#include <stdbool.h>
#include <stdio.h>
#define MIN(a, b) (((a) > (b)) ? (b) : (a))
/* Forward declarations */
static bool is_transpose(size_t M, size_t N, const double A[N][M],
                         const double B[M][N]);
static void trans(size_t M, size_t N, const double A[N][M], double B[M][N],
                  double *tmp);
static void trans_tmp(size_t M, size_t N, const double A[N][M], double B[M][N],
                      double *tmp);

static void trans32(size_t M, size_t N, const double A[N][M], double B[M][N],
                    double *tmp);

static void trans63(size_t M, size_t N, const double A[N][M], double B[M][N],
                    double *tmp);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
static const char transpose_submit_desc[] = "Transpose submission";

static void transpose_submit(size_t M, size_t N, const double A[N][M],
                             double B[M][N], double *tmp) {
    /*
     * This is a good place to call your favorite transposition functions
     * It's OK to choose different functions based on array size, but
     * your code must be correct for all values of M and N
     */

    if (M == N && M == 32) {
        trans32(M, N, A, B, tmp);
    } else if (M == 63 && N == 65) {
        trans63(M, N, A, B, tmp);
    } else if (M == N)
        trans(M, N, A, B, tmp);
    else
        trans_tmp(M, N, A, B, tmp);
}
/*
 * You can define additional transpose functions below. We've defined
 * some simple ones below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
static const char trans_desc[] = "Simple row-wise scan transpose";

/*
 * The following shows an example of a correct, but cache-inefficient
 *   transpose function.  Note the use of macros (defined in
 *   contracts.h) that add checking code when the file is compiled in
 *   debugging mode.  See the Makefile for instructions on how to do
 *   this.
 *
 *   IMPORTANT: Enabling debugging will significantly reduce your
 *   cache performance.  Be sure to disable this checking when you
 *   want to measure performance.
 */
static void trans(size_t M, size_t N, const double A[N][M], double B[M][N],
                  double *tmp) {
    size_t i, j;

    REQUIRES(M > 0);
    REQUIRES(N > 0);

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            B[j][i] = A[i][j];
        }
    }

    ENSURES(is_transpose(M, N, A, B));
}

// get the idea from:
// http://csapp.cs.cmu.edu/public/waside/waside-blocking.pdf
static void trans32(size_t M, size_t N, const double A[N][M], double B[M][N],
                    double *tmp) {
    size_t i, j, k, l;

    REQUIRES(M > 0);
    REQUIRES(N > 0);

    for (i = 0; i < N; i += 8) {
        for (j = 0; j < M; j += 8) {
            for (k = i; k < i + 8; k++) {
                l = j;
                // Input from A
                double a0 = A[k][l], a1 = A[k][l + 1];
                double a2 = A[k][l + 2], a3 = A[k][l + 3];
                double a4 = A[k][l + 4], a5 = A[k][l + 5];
                double a6 = A[k][l + 6], a7 = A[k][l + 7];
                // Insert to B
                B[l][k] = a0;
                B[l + 1][k] = a1;
                B[l + 2][k] = a2;
                B[l + 3][k] = a3;
                B[l + 4][k] = a4;
                B[l + 5][k] = a5;
                B[l + 6][k] = a6;
                B[l + 7][k] = a7;
            }
        }
    }

    ENSURES(is_transpose(M, N, A, B));
}

// Get the idea from website: https://www.cnblogs.com/liqiuhao/p/8026100.html?
// utm_source=debugrun&utm_medium=referral
static void trans63(size_t M, size_t N, const double A[N][M], double B[M][N],
                    double *tmp) {
    size_t length, i_range, j_range, i, j, k, l;

    REQUIRES(M > 0);
    REQUIRES(N > 0);

    length = 4;
    i_range = (65 + length - 1) / length;
    j_range = (65 + length - 1) / length;
    for (i = 0; i < i_range; i++) {
        for (j = 0; j < j_range; j++) {
            for (k = i * length; k < MIN(N, i * length + length); k++) {
                for (l = j * length; l < MIN(M, j * length + length); l++) {
                    B[l][k] = A[k][l];
                }
            }
        }
    }

    ENSURES(is_transpose(M, N, A, B));
}

/*
 * This is a contrived example to illustrate the use of the temporary array
 */

static const char trans_tmp_desc[] =
    "Simple row-wise scan transpose, using a 2X2 temporary array";

static void trans_tmp(size_t M, size_t N, const double A[N][M], double B[M][N],
                      double *tmp) {
    size_t i, j;
    /* Use the first four elements of tmp as a 2x2 array with row-major
     * ordering. */
    REQUIRES(M > 0);
    REQUIRES(N > 0);

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            int di = i % 2;
            int dj = j % 2;
            tmp[2 * di + dj] = A[i][j];
            B[j][i] = tmp[2 * di + dj];
        }
    }

    ENSURES(is_transpose(M, N, A, B));
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions(void) {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);
    registerTransFunction(trans_tmp, trans_tmp_desc);
    registerTransFunction(trans32, trans_desc);
    registerTransFunction(trans63, trans_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
static bool is_transpose(size_t M, size_t N, const double A[N][M],
                         const double B[M][N]) {
    size_t i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return false;
            }
        }
    }
    return true;
}
