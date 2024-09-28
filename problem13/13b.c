/*
============================================================================
Name : 13b.c
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
#include <stdlib.h>

int main() {
    pid_t pid;

    // Ask for the PID of the first program
    printf("Enter the PID of the first program: ");
    scanf("%d", &pid);

    // Send SIGSTOP to the first program
    printf("Sending SIGSTOP to process %d\n", pid);
    if (kill(pid, SIGSTOP) == 0) {
        printf("Successfully sent SIGSTOP to process %d\n", pid);
    } else {
        perror("Failed to send SIGSTOP");
        exit(1);
    }

    // Optional: Sleep for a few seconds to let the user observe the state
    sleep(5);

    // Send SIGCONT to resume the process
    printf("Sending SIGCONT to process %d\n", pid);
    if (kill(pid, SIGCONT) == 0) {
        printf("Successfully sent SIGCONT to process %d\n", pid);
    } else {
        perror("Failed to send SIGCONT");
        exit(1);
    }

    return 0;
}

