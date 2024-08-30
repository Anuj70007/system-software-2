/*
============================================================================
Name : 23.c
Author : Anuj Chaudhary
Description : Write a program to create a Zombie state of the running program
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t t = fork();

    if (t < 0) {
        perror("fork failed");
        return 1;
    } else if (t == 0) {
        printf("child id: %d.\n", getpid());
        exit(0);
    } else {
        printf("parent id: %d child zombie\n", getpid());
        sleep(30); //30 sec to check 
        wait(NULL);  //used to kill parent so that zobie process which is child killed
        
    }

    return 0;
}

