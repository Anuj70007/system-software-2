/*
============================================================================
Name : 15.c
Author : Anuj Chaudhary
Description : Write a simple program to send some data from parent to the child process.
Date: 27th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int a[2];         // Pipe file descriptors: a[0] for read, a[1] for write
    pid_t b;          // Process ID after fork
    char c[] = "Hello, child!";  // Message to send to child
    char d[100];                 // Buffer to store the received message

    // Create the pipe
    if (pipe(a) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Fork the process to create a child
    b = fork();

    if (b < 0) {
        // If fork() fails
        perror("Fork failed");
        return 1;
    } else if (b > 0) {
        // Parent process: write to the pipe
        close(a[0]); // Close the read end in the parent
        printf("Parent: Sending message to child: \"%s\"\n", c);
        write(a[1], c, strlen(c) + 1); // Write message to the pipe
        close(a[1]); // Close the write end after writing

    } else {
        // Child process: read from the pipe
        close(a[1]); // Close the write end in the child
        read(a[0], d, sizeof(d)); // Read message from the pipe
        printf("Child: Received message from parent: \"%s\"\n", d);
        close(a[0]); // Close the read end after reading
    }

    return 0;
}

