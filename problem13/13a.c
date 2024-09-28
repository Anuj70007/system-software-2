/*
============================================================================
Name : 13a.c
Author : Anuj Chaudhary
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not
Date: 27th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function to catch signals
void signal_handler(int sig) {
    if (sig == SIGUSR1) {
        printf("Received SIGUSR1 signal\n");
    } else if (sig == SIGTERM) {
        printf("Received SIGTERM signal, exiting...\n");
        _exit(0); // Exit the program
    } else {
        printf("Received signal: %d\n", sig);
    }
}

int main() {
    // Registering signal handler for SIGUSR1 and SIGTERM
    signal(SIGUSR1, signal_handler);
    signal(SIGTERM, signal_handler);

    // Trying to catch SIGSTOP (this won't work, no handler for SIGSTOP)
    printf("Waiting for signals (Try sending SIGUSR1, SIGTERM, or SIGSTOP)\n");

    // Infinite loop to keep the program running
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}

