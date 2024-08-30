/*
============================================================================
Name : 22.c
Author : Anuj Chaudhary
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the
parent processes. Check output of the file
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int desc = open("happy.txt", O_WRONLY | O_CREAT, 0644);
    if (desc < 0) {
        perror("fails");
        return 1;
    }
    pid_t t = fork();

    if (t < 0) {
        perror("fails fork");
        close(desc);
        return 1;
    } else if (t == 0) {
        const char *cm = "child msg\n";
        write(desc, cm, strlen(cm));
    } else {
        const char *pm = "parent msg\n";
        write(desc, pm, strlen(pm));
        wait(NULL); 
    }

    close(desc);
    return 0;
}


