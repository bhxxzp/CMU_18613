/*
 * Name: Peng Zeng
 * AndrewID: pengzeng
 */

/*
 *
 * tsh - A tiny shell program. This program is a simplified shell.
 * It supports the following builtin commands:
 * - quit, quit the shell
 * - bg/fg, execute the job in background/foreground
 * - jobs, list the current jobs
 * The shell implements I/O redirection for non-builtin commands and the jobs
 * command. Also, pressing Ctrl-C kills all foreground jobs and Ctrl-Z stops all
 * foreground jobs.
 */

#include "csapp.h"
#include "tsh_helper.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * If DEBUG is defined, enable contracts and printing on dbg_printf.
 */
#ifdef DEBUG
/* When debugging is enabled, these form aliases to useful functions */
#define dbg_printf(...) printf(__VA_ARGS__)
#define dbg_requires(...) assert(__VA_ARGS__)
#define dbg_assert(...) assert(__VA_ARGS__)
#define dbg_ensures(...) assert(__VA_ARGS__)
#else
/* When debugging is disabled, no code gets generated for these */
#define dbg_printf(...)
#define dbg_requires(...)
#define dbg_assert(...)
#define dbg_ensures(...)
#endif

/* Function prototypes */
void eval(const char *cmdline);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);
void sigquit_handler(int sig);
void cleanup(void);
int builtin_command(struct cmdline_tokens *token);
int redirection(struct cmdline_tokens *token);

/*
 *
 * main - The main function of the shell.
 * Output shell prompt tsh> continuously
 * Read user input
 *
 */
int main(int argc, char **argv) {
    char c;
    char cmdline[MAXLINE_TSH]; // Cmdline for fgets
    bool emit_prompt = true;   // Emit prompt (default)

    // Redirect stderr to stdout (so that driver will get all output
    // on the pipe connected to stdout)
    if (dup2(STDOUT_FILENO, STDERR_FILENO) < 0) {
        perror("dup2 error");
        exit(1);
    }

    // Parse the command line
    while ((c = getopt(argc, argv, "hvp")) != EOF) {
        switch (c) {
        case 'h': // Prints help message
            usage();
            break;
        case 'v': // Emits additional diagnostic info
            verbose = true;
            break;
        case 'p': // Disables prompt printing
            emit_prompt = false;
            break;
        default:
            usage();
        }
    }

    // Create environment variable
    if (putenv("MY_ENV=42") < 0) {
        perror("putenv error");
        exit(1);
    }

    // Set buffering mode of stdout to line buffering.
    // This prevents lines from being printed in the wrong order.
    if (setvbuf(stdout, NULL, _IOLBF, 0) < 0) {
        perror("setvbuf error");
        exit(1);
    }

    // Initialize the job list
    init_job_list();

    // Register a function to clean up the job list on program termination.
    // The function may not run in the case of abnormal termination (e.g. when
    // using exit or terminating due to a signal handler), so in those cases,
    // we trust that the OS will clean up any remaining resources.
    if (atexit(cleanup) < 0) {
        perror("atexit error");
        exit(1);
    }

    // Install the signal handlers
    Signal(SIGINT, sigint_handler);   // Handles Ctrl-C
    Signal(SIGTSTP, sigtstp_handler); // Handles Ctrl-Z
    Signal(SIGCHLD, sigchld_handler); // Handles terminated or stopped child

    Signal(SIGTTIN, SIG_IGN);
    Signal(SIGTTOU, SIG_IGN);

    Signal(SIGQUIT, sigquit_handler);

    // Execute the shell's read/eval loop
    while (true) {
        if (emit_prompt) {
            printf("%s", prompt);

            // We must flush stdout since we are not printing a full line.
            fflush(stdout);
        }

        if ((fgets(cmdline, MAXLINE_TSH, stdin) == NULL) && ferror(stdin)) {
            perror("fgets error");
            exit(1);
        }

        if (feof(stdin)) {
            // End of file (Ctrl-D)
            printf("\n");
            return 0;
        }

        // Remove any trailing newline
        char *newline = strchr(cmdline, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        // Evaluate the command line
        eval(cmdline);
    }

    return -1; // control never reaches here
}

/*
 *
 * eval - Parse the command and execute it. If the command is a builtin cmd,
 * execute it directly. Or, create a child process to execute it.
 * If the job is fg job, wait for it finished. If the job is bg job,
 * then run it in the background.
 *
 */
void eval(const char *cmdline) {
    parseline_return parse_result;
    struct cmdline_tokens token;
    int bg;
    pid_t pid; // process id
    jid_t jid; // job id
    sigset_t mask_one, prev_one, mask_all;
    job_state state = BG;
    sigfillset(&mask_all);
    sigemptyset(&mask_one);
    sigemptyset(&prev_one);

    // Parse command line
    parse_result = parseline(cmdline, &token);

    // Block SIGINT and save previous blocked set
    if (parse_result == PARSELINE_ERROR || parse_result == PARSELINE_EMPTY) {
        return;
    }

    // If background then bg = 1; if foreground then bg = 0
    bg = parse_result;

    // Ignore empty lines
    if (token.argv[0] == NULL) {
        return;
    }

    // token.builtin: 0 None 1 Quit 2 Jobs 3 BG 4 FG
    // sio_printf("Builtin: %d\n", token.builtin);

    // sio_printf("bg: %d\n", bg);
    // If not builtin cmd, fork a child process to execve
    if (!builtin_command(&token)) {
        sigprocmask(SIG_BLOCK, &mask_all, &prev_one);
        if ((pid = fork()) == 0) {
            // Unblock SIGCHILD
            sigprocmask(SIG_SETMASK, &prev_one, NULL);

            setpgid(0, 0);

            if (!redirection(&token)) {
                // sigprocmask(SIG_SETMASK, &prev_one, NULL);
                exit(0);
            }
            sigprocmask(SIG_BLOCK, &mask_all, &prev_one);
            if (execve(token.argv[0], token.argv, environ) < 0) {
                if (errno == EACCES) {
                    sio_printf("%s: Permission denied\n", cmdline);
                } else {
                    sio_printf("%s: No such file or directory\n", cmdline);
                }
                exit(0);
            }
        } else if (pid < 0) {
            sio_printf("Fork failed.\n");
            exit(1);
        }

        // sio_printf("bg: %d\n", bg);
        // Add job to the job list
        if (bg == 0) { // foreground
            state = FG;
            add_job(pid, state, cmdline);
            // wait for the process finished
            while ((jid = fg_job()) != 0) {
                sigsuspend(&prev_one);
            }
        } else if (bg == 1) { // background
            state = BG;
            add_job(pid, state, cmdline);
            jid = job_from_pid(pid);
            sio_printf("[%d] (%d) %s\n", jid, pid, cmdline);
        }
    }

    // Unblock all siginal
    sigprocmask(SIG_SETMASK, &prev_one, NULL);
    return;
}

/*****************
 * Signal handlers
 *****************/

/*
 * Sigchld_handler - Invoked when catch SIGCHLD
 * It can reap all zombie children. Each child process
 * will send the SIGCHLD signals to their parent process when
 * they finish.
 */
void sigchld_handler(int sig) {
    int olderrno = errno;
    int status;
    pid_t pid;
    jid_t jid;
    sigset_t mask, prev_one;

    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, &prev_one);

    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
        jid = job_from_pid(pid);

        // For "Ctrl + c"
        if (WIFSTOPPED(status)) {
            job_set_state(jid, ST);
            sio_printf("Job [%d] (%d) stopped by signal %d\n", jid, pid,
                       WSTOPSIG(status));
        }
        // For "Ctrl + z"
        else if (WIFSIGNALED(status)) {
            sio_printf("Job [%d] (%d) terminated by signal %d\n", jid, pid,
                       WTERMSIG(status));
            if (!delete_job(jid)) {
                sio_printf("SIGINT. Fail to delete job.\n");
            }
        }
        // Else
        else if (WIFEXITED(status)) {
            if (!delete_job(jid)) {
                sio_printf("Else. Fail to delete job.\n");
            }
        }
    }

    sigprocmask(SIG_SETMASK, &prev_one, NULL);
    errno = olderrno;
    return;
}

/*
 * Sigint_handler - Invoked when catch SIGINT
 * Send the SIGINT signals to fg jobs
 */
void sigint_handler(int sig) {
    int olderrno = errno;
    pid_t pid;
    jid_t jid;
    sigset_t mask, prev_one;

    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, &prev_one);

    // Send signal to fg
    if ((jid = fg_job()) != 0) {
        pid = job_get_pid(jid);
        if (pid != 0) {
            kill(-pid, SIGINT);
        }
    }
    sigprocmask(SIG_SETMASK, &prev_one, NULL);
    errno = olderrno;
    return;
}

/*
 * Sigtstp_handler - Invoked when catch SIGTSTP
 * Send the SIGTSTP signals to fg jobs
 */
void sigtstp_handler(int sig) {
    int olderrno = errno;
    pid_t pid;
    jid_t jid;
    sigset_t mask, prev_one;

    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, &prev_one);

    // Send signal to fg
    if ((jid = fg_job()) != 0) {
        pid = job_get_pid(jid);
        if (pid != 0) {
            kill(-pid, SIGTSTP);
        }
    }
    sigprocmask(SIG_SETMASK, &prev_one, NULL);
    errno = olderrno;
    return;
}

/*
 * cleanup - Attempt to clean up global resources when the program exits. In
 * particular, the job list must be freed at this time, since it may contain
 * leftover buffers from existing or even deleted jobs.
 */
void cleanup(void) {
    // Signals handlers need to be removed before destroying the joblist
    Signal(SIGINT, SIG_DFL);  // Handles Ctrl-C
    Signal(SIGTSTP, SIG_DFL); // Handles Ctrl-Z
    Signal(SIGCHLD, SIG_DFL); // Handles terminated or stopped child

    destroy_job_list();
}

/*****************
 * Helper functions
 *****************/

/*
 * Execute the bg/fb builtin command
 * Args: char **argv
 * Return: nothing
 */
void do_bgfg(char **argv) {

    pid_t pid;
    jid_t jid;
    sigset_t mask, prev_mask;
    sigfillset(&mask);
    job_state state;
    const char *cmdline = NULL;

    // Check the JID and PID
    if (argv[1] == NULL) {
        sio_printf("%s command requires PID or %%jobid argument\n", argv[0]);
        return;
    }

    // Get jid
    if (argv[1][0] == '%') {
        jid = atoi(&argv[1][1]);
    }
    // Get pid
    else {
        pid = atoi(argv[1]);
        sigprocmask(SIG_BLOCK, &mask, &prev_mask);
        if ((jid = job_from_pid(pid)) == 0) {
            sio_printf("%s: argument must be a PID or %%jobid\n", argv[0]);
            sigprocmask(SIG_SETMASK, &prev_mask, NULL);
            return;
        }
        sigprocmask(SIG_SETMASK, &prev_mask, NULL);
    }
    sigprocmask(SIG_BLOCK, &mask, &prev_mask);
    if (job_exists(jid) == 0) {
        sio_printf("%%%d: No such job\n", jid);
        sigprocmask(SIG_SETMASK, &prev_mask, NULL);
        return;
    }
    sigprocmask(SIG_SETMASK, &prev_mask, NULL);

    if (strcmp(argv[0], "bg") == 0) {
        state = BG;
    } else {
        state = FG;
    }

    sigprocmask(SIG_BLOCK, &mask, &prev_mask);
    pid = job_get_pid(jid);
    cmdline = job_get_cmdline(jid);
    job_set_state(jid, state);
    kill(-pid, SIGCONT);

    if (state == FG) {
        while ((pid = fg_job()) != 0) {
            sigsuspend(&prev_mask);
        }
    } else {
        sio_printf("[%d] (%d) %s\n", jid, pid, cmdline);
    }
    sigprocmask(SIG_SETMASK, &prev_mask, NULL);
    return;
}

/*
 * Check if it is the builtin command
 * If quit command, exit the shell
 * Args: struct cmdline_tokens *token
 * Return: 1 if builtin, otherwise 0
 */
int builtin_command(struct cmdline_tokens *token) {
    sigset_t mask, prev_mask;
    int olderrno = errno;
    sigemptyset(&prev_mask);
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, NULL, &prev_mask);

    // Quit
    if (token->builtin == BUILTIN_QUIT) {
        // sio_printf("QUIT!\n");
        exit(0); // Exit tsh
    }
    // BG\FG
    else if (token->builtin == BUILTIN_BG || token->builtin == BUILTIN_FG) {
        do_bgfg(token->argv);
        sigprocmask(SIG_SETMASK, &prev_mask, NULL);
        errno = olderrno;
        return 1;
    }
    // NOT Buildin command
    else if (token->builtin == BUILTIN_NONE) {
        sigprocmask(SIG_SETMASK, &prev_mask, NULL);
        errno = olderrno;
        return 0;
    }
    // JOBS
    else if (token->builtin == BUILTIN_JOBS) {
        if (token->outfile == NULL) {
            sigprocmask(SIG_BLOCK, &mask, &prev_mask);
            list_jobs(1);
            sigprocmask(SIG_SETMASK, &prev_mask, NULL);
            errno = olderrno;
            return 1;
        }

        else {
            int fd;
            if ((fd = open(token->outfile, O_CREAT | O_TRUNC | O_WRONLY,
                           DEF_MODE)) < 0) {
                if (errno == EACCES) {
                    sio_printf("%s: Permission denied\n", token->outfile);
                } else {
                    sio_printf("%s: No such file or directory\n",
                               token->outfile);
                }
                errno = olderrno;
                return 1;
            }
            sigprocmask(SIG_BLOCK, &mask, &prev_mask);
            list_jobs(fd);
            sigprocmask(SIG_SETMASK, &prev_mask, NULL);
        }
        errno = olderrno;
        return 1;
    }

    return 0;
}

/*
 * Redirect I/O if specified in cmd
 * Args: struct cmdline_tokens *token
 * Return: 1 if redirect successfully, otherwise 0
 */
int redirection(struct cmdline_tokens *token) {
    int olderrno = errno;
    int fd_out;
    int fd_in;
    char *file_in = NULL;
    char *file_out = NULL;
    // Redirect input
    if (token->infile != NULL) {
        file_in = token->infile;
        fd_in = open(file_in, O_RDONLY, DEF_MODE);
        if (fd_in < 0) {
            if (errno == EACCES) {
                sio_printf("%s: Permission denied\n",
                           file_in); // Trace31 Here
            } else {
                sio_printf("%s: No such file or directory\n", file_in);
            }
            errno = olderrno;
            return 0;
        }
        if (dup2(fd_in, 0) == -1) {
            sio_printf("fd_in dup2 failed.\n");
            errno = olderrno;
            return 0;
        }
    }

    // Redirect output
    if (token->outfile != NULL) {
        file_out = token->outfile;
        fd_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, DEF_MODE);
        if (fd_out < 0) {
            if (errno == EACCES) {
                sio_printf("%s: Permission denied\n", file_out);
            } else {
                sio_printf("%s: No such file or directory\n", file_out);
            }
            errno = olderrno;
            return 0;
        }
        if (dup2(fd_out, 1) == -1) {
            sio_printf("fd_out dup2 failed.\n");
            errno = olderrno;
            return 0;
        }
    }
    errno = olderrno;
    return 1;
}