#include <stdio.h>
#include <stdbool.h>
#include "cachelab.h"
#include "contracts.h"

/* Forward declarations */
static bool is_transpose(size_t M, size_t N, const double A[N][M],
                         const double B[M][N]);
static void trans(size_t M, size_t N, const double A[N][M], double B[M][N],
                  double *tmp);
static void trans_tmp(size_t M, size_t N, const double A[N][M], double B[M][N],
                      double *tmp);
static void mytrans(size_t M, size_t N, const double A[N][M], double B[M][N],
                    double *tmp);
static void mytrans_tmp(size_t M, size_t N, const double A[N][M],
                        double B[M][N], double *tmp);
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

  if (M == N && M == 32)
    mytrans(M, N, A, B, tmp);
  else if (M == 63 && N == 65)
    mytrans_tmp(M, N, A, B, tmp);
  else if (M == N)
    trans(M, N, A, B, tmp);
  else
    trans_tmp(M, N, A, B, tmp);
}
/*
 * You can define additional transpose functions below. We've defined
 * some simple ones below to help you get started.
 */
static void mytrans(size_t M, size_t N, const double A[N][M], double B[M][N],
                    double *tmp) {
  size_t ii, jj, i, j;
  REQUIRES(M > 0);
  REQUIRES(N > 0);

  for (ii = 0; ii < 32; ii += 8) {
    for (jj = 0; jj < 32; jj += 8) {
      for (j = jj; j < jj + 8; j++) {
        for (i = ii; i < ii + 8; i++) {
          if (i != j) {
            B[i][j] = A[j][i];
          }
        }
        for (i = ii; i < ii + 1; i++) {
          if (i == j) {
            *tmp = A[j][i];
            B[i][j] = *tmp;
          }
        }
        for (i = ii + 1; i < ii + 8; i++) {
          if (i == j) {
            B[i][j] = A[j][i];
          }
        }
      }
    }
  }
  ENSURES(is_transpose(M, N, A, B));
}

static void mytrans_tmp(size_t M, size_t N, const double A[N][M],
                        double B[M][N], double *tmp) {
  size_t ii, jj, i, j;
  REQUIRES(M > 0);
  REQUIRES(N > 0);

  for (ii = 0; ii < N; ii += 4) {
    for (jj = 0; jj < 63; jj += 4) {
      for (i = ii; i < ii + 4 && i < N; i++) {
        for (j = jj; j < jj + 4 && j < M; j++) {
          B[j][i] = A[i][j];
        }
      }
    }
  }
  ENSURES(is_transpose(M, N, A, B));
}
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

/*
 * This is a contrived example to illustrate the use of the temporary array
 */

static const char trans_tmp_desc[] =
    "Simple row-wise scan transpose, using a 2X2 temporary array";

static void trans_tmp(size_t M, size_t N, const double A[N][M], double B[M][N],
                      double *tmp) {
  size_t i, j;
  /* Use the first four elements of tmp as a 2x2 array with row-major ordering.
   */
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