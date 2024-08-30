/*
============================================================================
Name : 28.c
Author : Anuj Chaudhary
Description : Write a program to get maximum and minimum real time priority.
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main() {
    int head[] = {SCHED_RR, SCHED_FIFO};  //SCHED_DEADLINE not working removed
    const char *hname[] = {"RR","FIFO"};

    for (int i = 0; i < sizeof(head) / sizeof(head[0]); i++) {
        int p = head[i];
        const char *p_name = hname[i];

    int minn = sched_get_priority_min(p);
        if (minn == -1) {
            perror("min priority failes");
            exit(EXIT_FAILURE);
        }

        int maxx = sched_get_priority_max(p);
        if (maxx == -1) {
            perror("max priority fail");
            exit(EXIT_FAILURE);
        }

    
        printf("%s:\n", p_name);
        printf("Min Priority:- %d\n", minn);
        printf("Max Priority:- %d\n", maxx);
        
    }

    return 0;
}

