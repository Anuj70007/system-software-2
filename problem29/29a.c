/*
============================================================================
Name : 29a.c
Author : Anuj Chaudhary
Description : Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO,SCHED_RR)
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

int main() {
    
    int cp = sched_getscheduler(0);
    if (cp == -1) {
        perror("getschedul fail");
        exit(EXIT_FAILURE);
    }

    printf("Current policy: %d\n", cp);


    int np = SCHED_FIFO;  
    struct sched_param param;
    param.sched_priority = 1;  
    if (sched_setscheduler(0, np, &param) == -1) {
        perror("setschedule fail");
        exit(EXIT_FAILURE);
    }

    cp = sched_getscheduler(0);
    if (cp == -1) {
        perror("getschedul fail");
        exit(EXIT_FAILURE);
    }

    printf("New policy: %d\n", cp);

    return 0;
}

