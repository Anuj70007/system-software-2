/*
============================================================================
Name : 9.c
Author : Anuj Chaudhary
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 20th sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// This function will be called when SIGINT is caught
void handle_sigint(int signum) {
    printf("Caught SIGINT signal. This message won't show until we reset.\n");
}

int main() {
    // Step 1: Ignore the SIGINT signal
    signal(SIGINT, SIG_IGN);
    printf("Currently ignoring SIGINT. Press Ctrl+C, and it won't stop the program.\n");

    // Give the user some time to press Ctrl+C
    sleep(5);

    // Step 2: Reset SIGINT to its default action
    signal(SIGINT, SIG_DFL);
    printf("SIGINT is now set to its default action. Press Ctrl+C to terminate the program.\n");

    // Step 3: Keep the program running to wait for user input
    while (1) {
        sleep(1); // Wait here until interrupted
    }

    return 0; // This line will never be reached
}

