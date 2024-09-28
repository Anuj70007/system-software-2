/*
============================================================================
Name : 10c.c
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

// Handler for SIGFPE
void handle_sigfpe(int a) {
    printf("Caught SIGFPE (Floating Point Exception). Exiting...\n");
    exit(1);
}

int main() {
    // Step 1: Set up sigaction to catch SIGFPE
    struct sigaction b;
    b.sa_handler = handle_sigfpe; // Assign the handler
    sigemptyset(&b.sa_mask); // No additional signals are blocked
    b.sa_flags = 0; // Default behavior

    sigaction(SIGFPE, &b, NULL); // Register the handler for SIGFPE

    // Step 2: Trigger SIGFPE by dividing by zero
    int c = 1;
    int d = 0;
    printf("Triggering SIGFPE by dividing by zero...\n");
    int e = c / d; // This will trigger SIGFPE

    return 0; // This line will not be executed
}


