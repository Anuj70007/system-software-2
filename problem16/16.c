/*
============================================================================
Name : 16.c
Author : Anuj Chaudhary
Description : Write a program to send and receive data from parent to child vice versa. Use two way
communication
Date: 27th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int parentToChild[2];   // Pipe for sending data from parent to child
    int childToParent[2];   // Pipe for sending data from child to parent
    pid_t pid;
    char parentMessage[] = "Hello from parent!";
    char childMessage[] = "Hello from child!";
    char parentBuffer[100];  // Buffer for parent to read child's message
    char childBuffer[100];   // Buffer for child to read parent's message

    // Create both pipes
    if (pipe(parentToChild) == -1 || pipe(childToParent) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Fork to create a child process
    pid = fork();

    if (pid < 0) {
        // If fork() fails
        perror("Fork failed");
        return 1;
    } else if (pid > 0) {
        // Parent process
        close(parentToChild[0]);  // Close unused read end of parent-to-child pipe
        close(childToParent[1]);  // Close unused write end of child-to-parent pipe

        // Parent writes to the child
        printf("Parent: Sending message to child: \"%s\"\n", parentMessage);
        write(parentToChild[1], parentMessage, strlen(parentMessage) + 1);  // +1 to send null-terminator
        close(parentToChild[1]);  // Close the write end after sending

        // Parent reads the message from the child
        read(childToParent[0], parentBuffer, sizeof(parentBuffer));
        printf("Parent: Received message from child: \"%s\"\n", parentBuffer);
        close(childToParent[0]);  // Close the read end after receiving

    } else {
        // Child process
        close(parentToChild[1]);  // Close unused write end of parent-to-child pipe
        close(childToParent[0]);  // Close unused read end of child-to-parent pipe

        // Child reads the message from the parent
        read(parentToChild[0], childBuffer, sizeof(childBuffer));
        printf("Child: Received message from parent: \"%s\"\n", childBuffer);
        close(parentToChild[0]);  // Close the read end after receiving

        // Child writes back to the parent
        printf("Child: Sending message to parent: \"%s\"\n", childMessage);
        write(childToParent[1], childMessage, strlen(childMessage) + 1);  // +1 to send null-terminator
        close(childToParent[1]);  // Close the write end after sending
    }

    return 0;
}

