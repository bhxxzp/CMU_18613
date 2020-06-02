/*
 * test-trans.c - Checks the correctness and performance of all of the
 *     student's transpose functions and records the results for their
 *     official submitted version as well.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <sys/types.h>
#include "cachelab.h"
#include <sys/wait.h> // fir WEXITSTATUS
#include <limits.h> // for LONG_MAX
#include <stdbool.h>

/* Grading parameters */
// Number of clock cycles for hit
#define HIT_CYCLES 4
// Number of clock cycles for miss
#define MISS_CYCLES 100
// Log number of sets
#define TEST_LOG_SET 5
// Associativity
#define TEST_ASSOC 1
// Log number of bytes / block
#define TEST_LOG_BLOCK 6


/* The description string for the transpose_submit() function that the
   student submits for credit */
#define SUBMIT_DESCRIPTION "Transpose submission"

/* External function defined in trans.c */
extern void registerFunctions(void);

/* External variables defined in cachelab-tools.c */
extern trans_func_t func_list[MAX_TRANS_FUNCS];
extern int func_counter;

/* Globals set on the command line */
static size_t M = 0;
static size_t N = 0;

/* The correctness and performance for the submitted transpose function */
struct results {
    int funcid;
    bool correct;
    long misses;
    long hits;
};
static struct results results = {-1, false, LONG_MAX, LONG_MAX };

/*
 * Calculates the number of clock cycles for the trace
 */
static long get_clock_cycles(long hits, long misses) {
    long clock_cycles = (HIT_CYCLES * hits + MISS_CYCLES * misses);
    return clock_cycles;
}

/*
 * eval_perf - Evaluate the performance of the registered transpose functions
 */
static void eval_perf(unsigned int s, unsigned int E, unsigned int b,
               bool submission_only) {
    int i, flag;
    long hits, misses, evictions;
    char cmd[334], file_name[255];
    int rval;

    registerFunctions();

    /* Open the complete trace file */
    FILE *full_trace_fp;

    /* Evaluate the performance of each registered transpose function */

    for (i=0; i<func_counter; i++) {
        if (strcmp(func_list[i].description, SUBMIT_DESCRIPTION) == 0 )
            results.funcid = i; /* remember which function is the submission */
        else if (submission_only)
            continue;

        printf("\nFunction %d (%d total)\nStep 1: Validating and generating memory traces\n",i,func_counter);

        sprintf(file_name, "trace.f%d", i);

        sprintf(cmd, "./tracegen-ct -M %ld -N %ld -F %d > %s", M, N, i, file_name);
        flag=WEXITSTATUS(system(cmd));
        if (0 != flag) {
            printf("Validation error at function %d! Run ./tracegen-ct -v -M %zd -N %zd -F %d for details.\n",flag-1,M,N,i);
            continue;
        }
        func_list[i].correct=true;

        /* Save the correctness of the transpose submission */
        if (results.funcid == i ) {
            results.correct = true;
        }


        /* Run the reference simulator */
        full_trace_fp = fopen(file_name, "r");
        assert(full_trace_fp);


        printf("Step 2: Evaluating performance (s=%d, E=%d, b=%d)\n", s, E, b);
        char cmd[323];
        sprintf(cmd, "./csim-ref -s %u -E %u -b %u -t %s > /dev/null",
                s, E, b, file_name);
        rval = system(cmd);
        if (rval) {
            results.correct = false;
            printf("Cache simulator error.  The reference simulator exited with value %d\n", rval);
            continue;
        }

        /* Collect results from the reference simulator */
        FILE *in_fp = fopen(".csim_results","r");
        assert(in_fp);
        if (3!=fscanf(in_fp, "%ld %ld %ld", &hits, &misses, &evictions)) {
            printf("Cache simulator error.  Simulator generated invalid results\n");
            continue;
        }
        fclose(in_fp);
        func_list[i].num_hits = hits;
        func_list[i].num_misses = misses;
        func_list[i].num_evictions = evictions;
        printf("func %d (%s): hits:%ld, misses:%ld, evictions:%ld, clock_cycles:%ld\n",
               i, func_list[i].description, hits, misses, evictions, get_clock_cycles(hits, misses));

        /* If it is transpose_submit(), record number of misses */
        if (results.funcid == i) {
            results.misses = misses;
            results.hits = hits;
        }
    }
}

/*
 * usage - Print usage info
 */
static void usage(char *argv[]) {
    printf("Usage: %s [-h] [-s] -M <rows> -N <cols>\n", argv[0]);
    printf("Options:\n");
    printf("  -h          Print this help message.\n");
    printf("  -s          Check official submission only.\n");
    printf("  -M <rows>   Number of destination matrix rows (max %d)\n", MAXN);
    printf("  -N <cols>   Number of destination matrix columns (max %d)\n", MAXN);
    printf("Example: %s -M 8 -N 8\n", argv[0]);
}

/*
 * sigsegv_handler - SIGSEGV handler
 */
static void sigsegv_handler(int signum) {
    printf("Error: Segmentation Fault.\n");
    printf("TEST_TRANS_RESULTS=0:0\n");
    fflush(stdout);
    exit(1);
}

/*
 * sigalrm_handler - SIGALRM handler
 */
static void sigalrm_handler(int signum) {
    printf("Error: Program timed out.\n");
    printf("TEST_TRANS_RESULTS=0:0\n");
    fflush(stdout);
    exit(1);
}

/*
 * main - Main routine
 */
int main(int argc, char *argv[]) {
    char c;

    bool submission_only = false;


    while ((c = getopt(argc,argv,"hcsM:N:")) != -1) {
        switch(c) {
        case 'M':
            M = (size_t) atoi(optarg);
            break;
        case 'N':
            N = (size_t) atoi(optarg);
            break;
        case 's':
            submission_only = true;
            break;
        case 'h':
            usage(argv);
            exit(0);
        default:
            usage(argv);
            exit(1);
        }
    }

    if (M == 0 || N == 0) {
        printf("Error: Missing required argument\n");
        usage(argv);
        exit(1);
    }

    if (M > MAXN || N > MAXN) {
        printf("Error: M or N exceeds %d\n", MAXN);
        usage(argv);
        exit(1);
    }

    /* Install SIGSEGV and SIGALRM handlers */
    if (signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
        fprintf(stderr, "Unable to install SIGALRM handler\n");
        exit(1);
    }

    if (signal(SIGALRM, sigalrm_handler) == SIG_ERR) {
        fprintf(stderr, "Unable to install SIGALRM handler\n");
        exit(1);
    }

    /* Time out and give up after a while */
    alarm(360);

    /* Check the performance of the student's transpose function */
    eval_perf(TEST_LOG_SET, TEST_ASSOC, TEST_LOG_BLOCK,
              submission_only);

    /* Emit the results for this particular test */
    if (results.funcid == -1) {
        printf("\nError: We could not find your transpose_submit() function\n");
        printf("Error: Please ensure that description field is exactly \"%s\"\n",
               SUBMIT_DESCRIPTION);
        printf("\nTEST_TRANS_RESULTS=0:0\n");
    }
    else {
        printf("\nSummary for official submission (func %d): correctness=%d cycles=%ld\n",
               results.funcid, results.correct, get_clock_cycles(results.hits, results.misses));
        printf("\nTEST_TRANS_RESULTS=%d:%ld\n", results.correct,
                                                get_clock_cycles(results.hits, results.misses));
    }
    return 0;
}
