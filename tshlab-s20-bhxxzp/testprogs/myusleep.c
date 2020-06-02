/*
 * myusleep - Shell lab test program
 *
 * Reimplement usleep for portability purposes
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char**argv) {
    if (argc == 2) {
        usleep(atoi(argv[1]));
    }
    return 0;
}
