/*
============================================================================
Name : 10b.c
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

// Handler for SIGINT
void handle_sigint(int a) {
    printf("Caught SIGINT (Interrupt). Exiting...\n");
    exit(0);
}

int main() {
    // Step 1: Set up sigaction to catch SIGINT
    struct sigaction b;
    b.sa_handler = handle_sigint; // Assign the handler
    sigemptyset(&b.sa_mask); // No additional signals are blocked
    b.sa_flags = 0; // Default behavior

    sigaction(SIGINT, &b, NULL); // Register the handler for SIGINT
    printf("Press Ctrl+C to trigger SIGINT...\n");

    // Step 2: Keep the program running
    while (1) {
        sleep(1); // Wait for the signal
    }

    return 0; // This line will not be reached
}

