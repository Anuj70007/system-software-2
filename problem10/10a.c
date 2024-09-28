/*
============================================================================
Name : 10a.c
Author : Anuj Chaudhary
Description : Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
Date: 20th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Handler for SIGSEGV
void handle_sigsegv(int a) {
    printf("Caught SIGSEGV (Segmentation Fault). Exiting...\n");
    exit(1);
}

int main() {
    // Step 1: Set up sigaction to catch SIGSEGV
    struct sigaction b;
    b.sa_handler = handle_sigsegv; // Assign the handler
    sigemptyset(&b.sa_mask); // No additional signals are blocked
    b.sa_flags = 0; // Default behavior

    sigaction(SIGSEGV, &b, NULL); // Register the handler for SIGSEGV

    // Step 2: Cause a segmentation fault
    int *c = NULL;
    *c = 1; // This will trigger SIGSEGV

    return 0; // This line will not be executed
}

