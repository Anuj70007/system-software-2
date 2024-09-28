/*
============================================================================
Name : 23.c
Author : Anuj Chaudhary
Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 27th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <unistd.h>

#define PIPE_NAME "my_pipe"

int main() {
    // Part 1: Get maximum number of open files
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("Maximum number of open files: %lu\n", limit.rlim_cur);
    } else {
        perror("getrlimit failed");
    }

    // Part 2: Create a pipe and get its size
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // Set the pipe size (example size: 4096 bytes)
    // This step is optional as the default size is often sufficient
    if (fcntl(pipe_fd[0], F_SETPIPE_SZ, 4096) == -1) {
        perror("fcntl failed to set pipe size");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return 1;
    }

    // Get the pipe size
    int pipe_size = fcntl(pipe_fd[0], F_GETPIPE_SZ);
    if (pipe_size == -1) {
        perror("fcntl failed to get pipe size");
    } else {
        printf("Size of the pipe (circular buffer): %d bytes\n", pipe_size);
    }

    // Close the pipe file descriptors
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}

