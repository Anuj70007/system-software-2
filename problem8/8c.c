/*
============================================================================
Name : 8c.c
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
    printf("Caught SIGFPE (Floating Point Exception)\n");
    exit(1);
}

int main() {
    signal(SIGFPE, handler); // Set up the signal handler
    int b = 1;
    int c = 0;
    printf("Triggering SIGFPE by dividing by zero...\n");
    int d = b / c; // This will trigger SIGFPE
    return 0;
}

