/*
============================================================================
Name : 25.c
Author : Anuj Chaudhary
Description : Write a program to create three child processes. The parent should wait for a particular child (use
waitpid system call).
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t t[3];  
    for (int i = 0; i < 3; i++) {
        pid_t id = fork();
        
        if (id < 0) {
            perror("fail fork");
            exit(1);
        } else if (id == 0) {
            printf("Child %d id: %d created\n", i + 1, getpid());
            sleep(2 * (i + 1));
            printf("Child %d id: %d exiting\n", i + 1, getpid());
            exit(i + 1);  
        } else {
           
            t[i] = id;  
        }
    }
    int stat;
    pid_t ctw = t[1];  
    printf("Parent id %d waiting for child %d id %d\n", getpid(), 2, ctw);
    if (waitpid(ctw, &stat, 0) < 0) {
        perror("waitpid failed");
        exit(1);
    }
    if (WIFEXITED(stat)) {
        printf("Child %d (PID: %d) terminated with exit status %d\n", 2, ctw, WEXITSTATUS(stat));
    } else {
        printf("Child %d id: %d not exit\n", 2, ctw);
    }
    while (wait(NULL) > 0);
    return 0;
}

