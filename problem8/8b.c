/*
============================================================================
Name : 8b.c
Author : Anuj Chaudhary
Description : Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
d. SIGALRM (use alarm system call)
e. SIGALRM (use setitimer system call)
f. SIGVTALRM (use setitimer system call)
g. SIGPROF (use setitimer system call)
Date: 20th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int a) {
    printf("Caught SIGINT (Interrupt)\n");
    exit(0);
}

int main() {
    signal(SIGINT, handler); // Set up the signal handler
    printf("Press Ctrl+C to trigger SIGINT...\n");
    while (1) {
        sleep(1); // Wait for the signal
    }
    return 0;
}

