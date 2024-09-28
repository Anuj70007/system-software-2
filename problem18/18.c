/*
============================================================================
Name : 18.c
Author : Anuj Chaudhary
Description : Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
Date: 27th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe1[2];  // First pipe: from "ls -l" to "grep ^d"
    int pipe2[2];  // Second pipe: from "grep ^d" to "wc -l"
    pid_t pid1, pid2, pid3;

    // Create the first pipe
    if (pipe(pipe1) == -1) {
        perror("Pipe1 failed");
        exit(1);
    }

    // Fork first child for "ls -l"
    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        // Child 1 process: Execute "ls -l"
        // Redirect stdout to the write end of the first pipe
        close(pipe1[0]);              // Close the read end of the first pipe
        dup2(pipe1[1], STDOUT_FILENO); // Redirect stdout to pipe1's write end
        close(pipe1[1]);              // Close the original write end after duplication

        // Execute "ls -l"
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls failed");
        exit(1);
    }

    // Create the second pipe
    if (pipe(pipe2) == -1) {
        perror("Pipe2 failed");
        exit(1);
    }

    // Fork second child for "grep ^d"
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid2 == 0) {
        // Child 2 process: Execute "grep ^d"
        close(pipe1[1]);              // Close the write end of the first pipe
        dup2(pipe1[0], STDIN_FILENO);  // Redirect stdin to pipe1's read end
        close(pipe1[0]);              // Close the original read end after duplication

        close(pipe2[0]);              // Close the read end of the second pipe
        dup2(pipe2[1], STDOUT_FILENO); // Redirect stdout to pipe2's write end
        close(pipe2[1]);              // Close the original write end after duplication

        // Execute "grep ^d"
        execlp("grep", "grep", "^d", (char *)NULL);
        perror("execlp grep failed");
        exit(1);
    }

    // Fork third child for "wc -l"
    pid3 = fork();
    if (pid3 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid3 == 0) {
        // Child 3 process: Execute "wc -l"
        close(pipe2[1]);              // Close the write end of the second pipe
        dup2(pipe2[0], STDIN_FILENO);  // Redirect stdin to pipe2's read end
        close(pipe2[0]);              // Close the original read end after duplication

        // Execute "wc -l"
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("execlp wc failed");
        exit(1);
    }

    // Parent process: close all pipes
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    // Wait for all children to finish
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}

