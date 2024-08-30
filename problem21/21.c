/*
============================================================================
Name : 21.c
Author : Anuj Chaudhary
Description : Write a program, call fork and print the parent and child process id.
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t t = fork();

    if (t < 0) {
        perror("failed to make");
        return 1;
    } else if (t == 0) {
        printf("child id = %d, parent id = %d\n", getpid(), getppid());
    } else {
         printf("child id = %d, parent id = %d\n", getpid(), getppid());
    }
    return 0;
}

