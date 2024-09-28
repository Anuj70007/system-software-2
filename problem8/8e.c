/*
============================================================================
Name : 8e.c
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
#include <sys/time.h>
#include <unistd.h>

void handler(int a) {
    printf("Caught SIGALRM (Setitimer)\n");
    exit(0);
}

int main() {
    struct itimerval b;
    signal(SIGALRM, handler); // Set up the signal handler

    // Set the timer for 2 seconds
    b.it_value.tv_sec = 2; // Initial delay
    b.it_value.tv_usec = 0;
    b.it_interval.tv_sec = 0; // No repeated interval
    b.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &b, NULL);
    printf("Waiting for the alarm...\n");
    pause(); // Wait for signals
    return 0;
}

