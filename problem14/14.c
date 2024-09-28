/*
============================================================================
Name : 14.c
Author : Anuj Chaudhary
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
Date: 27th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int a[2];       // Array to store file descriptors: a[0] for read, a[1] for write
    pid_t b;
    char c[] = "Hello from the pipe!";
    char d[100];
    
    // Create the pipe
    if (pipe(a) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork a new process
    b = fork();

    if (b < 0) {
        // If fork failed
        perror("Fork failed");
        return 1;
    } else if (b > 0) {
        // Parent process: write to the pipe
        close(a[0]); // Close the read end of the pipe, not needed by parent

        printf("Parent: Writing to pipe: \"%s\"\n", c);
        write(a[1], c, strlen(c) + 1); // Write message to pipe
        close(a[1]); // Close the write end after writing

    } else {
        // Child process: read from the pipe
        close(a[1]); // Close the write end of the pipe, not needed by child

        read(a[0], d, sizeof(d)); // Read message from pipe
        printf("Child: Read from pipe: \"%s\"\n", d);
        close(a[0]); // Close the read end after reading
    }

    return 0;
}

