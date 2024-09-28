/*
============================================================================
Name : 17b.c
Author : Anuj Chaudhary
Description : Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl
Date: 27th sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pipefd[2];  // pipefd[0] for reading, pipefd[1] for writing
    pid_t pid;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    // Fork the process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process: will execute "ls -l"
        close(pipefd[0]);      // Close unused read end of the pipe
        dup2(pipefd[1], 1);    // Duplicate write end of the pipe to stdout (fd 1)
        close(pipefd[1]);      // Close original write end after duplicating
        execlp("ls", "ls", "-l", (char *)NULL);  // Execute ls -l
        perror("execlp failed");
        exit(1);
    } else {
        // Parent process: will execute "wc"
        close(pipefd[1]);      // Close unused write end of the pipe
        dup2(pipefd[0], 0);    // Duplicate read end of the pipe to stdin (fd 0)
        close(pipefd[0]);      // Close original read end after duplicating
        execlp("wc", "wc", (char *)NULL);  // Execute wc
        perror("execlp failed");
        exit(1);
    }

    return 0;
}

