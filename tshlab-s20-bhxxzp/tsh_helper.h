#ifndef __TSH_HELPER_H__
#define __TSH_HELPER_H__

/*
 * tsh_helper.h: definitions and interfaces for tshlab
 *
 * This file defines enumerations and structs used in tshlab, as well as the
 * interfaces for various helper routines. You should use these routines to
 * help write your tiny shell.
 *
 * Many of the helper routines are focused around maintaining a job list,
 * which you can only access through the routines themselves. Each job is
 * represented by a job ID ranging from 1 to MAXJOBS.
 *
 * The signal safety of each helper function is documented in this file. You
 * must ensure that any helper routines that you call within a signal handler
 * are async-signal-safe.
 *
 * A caveat is that the CSAPP functions, some of which are used in tsh_helper,
 * are technically not async-signal-safe due to the use of strerror. However,
 * we ignore this caveat for the sake of simplicity. See the comment in
 * csapp.h for more details.
 */

#include <stdbool.h>
#include <sys/types.h>

/* Misc manifest constants */
#define MAXLINE_TSH 1024 /* max line size */
#define MAXARGS 128      /* max args on a command line */
#define MAXJOBS 64       /* max jobs at any point in time */

/* Defined in libc */
extern char **environ;

/* Integer type used for job IDs */
typedef int jid_t;

/*
 * Job states: FG (foreground), BG (background), ST (stopped),
 *             UNDEF (undefined)
 * Job state transitions and enabling actions:
 *     FG -> ST  : ctrl-z
 *     ST -> FG  : fg command
 *     ST -> BG  : bg command
 *     BG -> FG  : fg command
 * At most 1 job can be in the FG state.
 */
typedef enum job_state {
    UNDEF, // Undefined (do not use)
    FG,    // Foreground job
    BG,    // Background job
    ST     // Stopped job
} job_state;

/* Parseline return states indicating the type of cmdline that was parsed */
typedef enum parseline_return {
    PARSELINE_FG,    // Foreground job
    PARSELINE_BG,    // Background job
    PARSELINE_EMPTY, // Empty cmdline
    PARSELINE_ERROR  // Parse error
} parseline_return;

/* Types of builtins that can be executed by the shell */
typedef enum builtin_state {
    BUILTIN_NONE, // Not a builtin command
    BUILTIN_QUIT, // quit (exit the shell)
    BUILTIN_JOBS, // jobs (list running jobs)
    BUILTIN_BG,   // bg (run job in background)
    BUILTIN_FG    // fg (run job in foreground)
} builtin_state;

/* Result of parsing a command line from parseline */
struct cmdline_tokens {
    int argc;               // Number of arguments passed
    char *argv[MAXARGS];    // The arguments list
    char *infile;           // The filename for input redirection, or NULL
    char *outfile;          // The filename for output redirection, or NULL
    builtin_state builtin;  // Indicates if argv[0] is a builtin command
    char _buf[MAXLINE_TSH]; // Internal backing buffer (do not use)
};

// These variables are externally defined in tsh_helper.c.
extern const char prompt[]; // Command line prompt (do not change)
extern bool verbose;        // If true, prints additional output

/*
 * Parses a command line, extracting the arguments, input/output redirection
 * files, and whether the command line corresponds to a background job. The
 * results are stored in the token argument, including a modified copy of the
 * command line used as a backing buffer for the other fields.
 *
 * Characters enclosed in single or double quotes are treated as a single
 * argument. The maximum number of arguments that will be parsed is MAXARGS.
 *
 * cmdline: The command line to parse. Only the first MAXLINE_TSH-1
 *   characters will be parsed. The command line is in the form:
 *
 *       command [arguments...] [< infile] [> oufile] [&]
 *
 * token: Pointer to a cmdline_tokens structure. The elements of this
 *   structure will be populated with the parsed tokens.
 *
 * Returns: a value of enumerated type parseline_return:
 *   PARSELINE_EMPTY:        if the command line is empty
 *   PARSELINE_BG:           if the user has requested a BG job
 *   PARSELINE_FG:           if the user has requested a FG job
 *   PARSELINE_ERROR:        if cmdline is incorrectly formatted
 *
 * Error conditions: This function will return PARSELINE_ERROR if it cannot
 *   successfully parse the command line. In this case, the contents of the
 *   token struct may be in an inconsistent state.
 *
 * Async-signal-safety: Not async-signal-safe.
 */
parseline_return parseline(const char *cmdline, struct cmdline_tokens *token);

/*
 * Terminates the shell immediately, printing an error message. This is to be
 * used as a signal handler for the SIGQUIT signal, and should not be called
 * directly.
 *
 * sig: The signal being handled (unused).
 *
 * Async-signal-safety: Async-signal-safe.
 */
void sigquit_handler(int sig);

/*
 * Initializes the job list. This must be done before accessing the job list.
 *
 * Precondition: The job list has not yet been initialized by previously
 *   calling the init_job_list function. Any signal handlers that might access
 *   the job list must not yet have been installed.
 * Async-signal-safety: Not async-signal-safe.
 */
void init_job_list(void);

/*
 * Destroys the job list, freeing any allocated memory used in it.
 *
 * Precondition: The job list must have been previously initialized with
 *   init_job_list before calling this function. Any signal handlers that
 *   might access the job list must be blocked or removed.
 * Async-signal-safety: Not async-signal-safe.
 */
void destroy_job_list(void);

/*
 * Creates a new job, allocating a job ID to represent the job, and writing
 * the job to the job list with the given parameters.
 *
 * pid: The process ID of the main process of the job.
 * state: The initial state of the job (should not be UNDEF).
 * cmdline: The command line used to start the job.
 * Returns: The JID of the added job, or 0 if the job could not be added.
 *
 * Precondition: Signals must be blocked. The pid, state, and cmdline
 *   arguments must be valid. The state must not be equal to UNDEF, and if it
 *   is equal to FG, then there must currently be no foreground job in the
 *   job list.
 * Error conditions: The function may fail to add a job if there are no more
 *   job IDs available (restricted by the MAXJOBS constant).
 * Async-signal-safety: Not async-signal-safe.
 */
jid_t add_job(pid_t pid, job_state state, const char *cmdline);

/*
 * Deletes a job from the job list, removing its data from the job list, and
 * freeing its job ID for use by another job.
 *
 * jid: The job ID of the job to delete.
 * Returns: true if the job was successfully deleted, and false otherwise.
 *
 * Precondition: Signals must be blocked.
 * Error conditions: The function may fail to delete a job if no job with the
 *   given job ID currently exists in the job list.
 * Async-signal-safety: Async-signal-safe.
 */
bool delete_job(jid_t jid);

/*
 * Finds the current foreground job in the job list.
 *
 * Returns: the job ID of the foreground job, or 0 if no such job exists.
 *
 * Precondition: Signals must be blocked.
 * Error conditions: This function will return 0 if there is currently no job
 *   in the job list in the foreground state.
 * Async-signal-safety: Async-signal-safe.
 */
jid_t fg_job(void);

/*
 * Determines whether a job with a given job ID exists in the job list.
 *
 * jid: The job ID to check.
 * Returns: true if a job with the given job ID exists, and false if the
 *   provided job ID is out of range, or if no corresponding job currently
 *   exists in the job list.
 *
 * Precondition: Signals must be blocked.
 * Async-signal-safety: Async-signal-safe.
 */
bool job_exists(jid_t jid);

/*
 * Finds a job corresponding to a process ID.
 *
 * pid: The process ID to search for.
 * Returns: the job ID of the corresponding job, or 0 if no such job was found.
 *
 * Precondition: Signals must be blocked.
 * Error conditions: This function will return 0 if the process ID was out of
 *   range, or no job in the job list has the given process ID.
 * Async-signal-safety: Async-signal-safe.
 */
jid_t job_from_pid(pid_t pid);

/*
 * Writes a representation of the job list to a file descriptor.
 *
 * output_fd: The file descriptor to write to.
 * Returns: true if the function succeeded, or false if an error occurred.
 *
 * Precondition: Signals must be blocked. output_fd must be a valid, open
 *   file descriptor that is open for writing.
 * Error conditions: This function will return false if an error occurred
 *   while writing to the file descriptor.
 * Async-signal-safety: Async-signal-safe.
 */
bool list_jobs(int output_fd);

/*
 * Prints usage instructions for the tiny shell.
 *
 * Async-signal-safety: Not async-signal-safe.
 */
void usage(void);

/*
 * Gets the process ID of a job.
 *
 * jid: The job ID of the job in question.
 * Returns: The process ID of the job.
 *
 * Precondition: Signals must be blocked. The provided job ID must be valid.
 * Async-signal-safety: Async-signal-safe.
 */
pid_t job_get_pid(jid_t jid);

/*
 * Gets the command line of a job.
 *
 * jid: The job ID of the job in question.
 * Returns: The command line of the job.
 *
 * Precondition: Signals must be blocked. The provided job ID must be valid.
 * Async-signal-safety: Async-signal-safe.
 */
const char *job_get_cmdline(jid_t jid);

/*
 * Gets the state of a job.
 *
 * jid: The job ID of the job in question.
 * Returns: The state of the job.
 *
 * Precondition: Signals must be blocked. The provided job ID must be valid.
 * Async-signal-safety: Async-signal-safe.
 */
job_state job_get_state(jid_t jid);

/*
 * Sets the state of a job.
 *
 * jid: The job ID of the job in question.
 * state: The new state of the job.
 *
 * Precondition: Signals must be blocked. The jid and state must be valid.
 *   The state must not be equal to UNDEF, and if it is equal to FG, then
 *   there must currently be no foreground job in the job list.
 * Async-signal-safety: Async-signal-safe.
 */
void job_set_state(jid_t jid, job_state state);

#endif // __TSH_HELPER_H__
