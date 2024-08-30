/*
============================================================================
Name : 24.c
Author : Anuj Chaudhary
Description : WWrite a program to create an orphan process.
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t t = fork();
    if (t < 0) {
        perror("fail fork");
        return 1;} else if (t == 0) {
        sleep(7); //so that parent exits and child becomes orphan :)
        printf("child id %d (orphan), adopted by new:- %d\n", getpid(), getppid());} else {
        printf("parent id %d\n", getpid());
        exit(0); 
    }
    return 0;
}

