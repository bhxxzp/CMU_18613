/*
 * mytstpandspin.c - Sends a SIGTSTP to its parent (the shell) then spin
 * for argv[1] s in standalone mode or until driver synchronises.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include "config.h"

void sigalrm_handler(int signum) {
    if (kill(getpid(), SIGTSTP) < 0) {
        perror("kill");
        _exit(1);
    }
    while(1);
    _exit(0);
}

int main(int argc, const char *argv[]) {
    char buf[MAXBUF];
    int syncfd;
    int rc;
    int standalone;
    char *str;
    char *cmdp;
    struct stat stat;

    signal(SIGALRM, sigalrm_handler);
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
     * the driver over its synchronizing domain socket, after being
     * restarted.  Ignore any command line argument.
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
        if (kill(getpid(), SIGTSTP) < 0) {
            perror("kill");
            exit(1);
        }
        while(1);
        exit(0);
        /*
         * Otherwise spin until timing out
         */
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
