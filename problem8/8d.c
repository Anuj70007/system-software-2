/*
============================================================================
Name : 8d.c
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
    printf("Caught SIGALRM (Alarm Timer)\n");
    exit(0);
}

int main() {
    signal(SIGALRM, handler); // Set up the signal handler
    alarm(2); // Set an alarm for 2 seconds
    printf("Waiting for the alarm...\n");
    pause(); // Wait for signals
    return 0;
}

