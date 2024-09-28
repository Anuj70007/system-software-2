/*
============================================================================
Name : 10c.c
Author : Anuj Chaudhary
Description :Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
use sigaction system call.
Date: 20th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Handler for SIGINT
void handle_sigint(int a) {
    printf("This won't be printed yet. SIGINT is ignored.\n");
}

int main() {
    // Step 1: Set up sigaction to ignore SIGINT
    struct sigaction b;
    b.sa_handler = handle_sigint; // Assign the handler
    sigemptyset(&b.sa_mask); // No additional signals are blocked
    b.sa_flags = 0; // Default behavior

    // Ignore SIGINT
    sigaction(SIGINT, &b, NULL);
    printf("SIGINT is currently ignored. Press Ctrl+C, and nothing will happen.\n");

    // Wait for a few seconds to allow the user to press Ctrl+C
    sleep(5);

    // Step 2: Reset SIGINT to default action
    b.sa_handler = SIG_DFL; // Reset handler to default
    sigaction(SIGINT, &b, NULL);
    printf("SIGINT is now reset to default action. Press Ctrl+C to terminate the program.\n");

    // Step 3: Keep the program running
    while (1) {
        sleep(1); // Wait for the signal
    }

    return 0; // This line will not be reached
}

