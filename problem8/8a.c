/*
============================================================================
Name : 8a.c
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
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(1);
}

int main() {
    signal(SIGSEGV, handler); // Set up the signal handler
    int *b = NULL;
    *b = 1; // This will trigger SIGSEGV
    return 0;
}

