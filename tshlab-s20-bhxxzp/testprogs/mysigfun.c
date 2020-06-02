/*
 * mysigfun.c - Weird signal handlers
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include "config.h"

int syncfd, standalone;
char buf[MAXBUF];

void sigalrm_handler(int signum) {
    _exit(0);
}

void sigint_handler(int signum) {
    kill(getpid(), SIGSTOP);
}

void sigtstp_handler(int signum) {
    raise(SIGQUIT);
}

int main(int argc, const char *argv[]) {
    char *str;
    char *cmdp;
    int rc;
    struct stat stat;

    signal(SIGALRM, sigalrm_handler);
    signal(SIGINT,  sigint_handler );
    signal(SIGTSTP, sigtstp_handler);

    alarm(JOB_TIMEOUT);

    /*
     * Determine if the shell is running standalone or under the
     * control of the driver program. If running under the driver, get
     * the number of the driver's synchronizing domain socket
     * descriptor.
     */
    standalone = 1;
    if ((str = getenv("SYNCFD")) != NULL) {
        syncfd = atoi(str);              /* Get descriptor number */
        if (fstat(syncfd, &stat) != -1) {/* Is is open? */
            standalone = 0;
        }
    }
    /*
     * If the job is being run by the driver, then synchronize with
     * the driver over its synchronizing domain socket.  Ignore any
     * command line argument.
     */

    if (!standalone) {
        alarm(JOB_TIMEOUT);
        cmdp = "";
        if ((rc = send(syncfd, cmdp, strlen(cmdp), 0)) < 0) {
            perror("send");
            exit(1);
        }
        if ((rc = recv(syncfd, buf, MAXBUF, 0)) < 0) {
            perror("recv");
            exit(1);
        }
        exit(0);
    // Otherwise spin until timing out
    } else {
        if (argc > 1) {
            alarm(atoi(argv[1]));
        } else {
            alarm(JOB_TIMEOUT);
        }
        while(1);
    }

    /* Control should never reach here */
    exit(1);
}
