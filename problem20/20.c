/*
============================================================================
Name : 20.c
Author : Anuj Chaudhary
Description : Find out the priority of your running program. Modify the priority with nice command.
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

int main() {
    pid_t a = getpid();
    int b = getpriority(PRIO_PROCESS, a);

    if (b == -1 && errno != 0) {
        perror("error");
        return 1;
    }

    printf("current priority: %d\n", b);

    int c = nice(2); //inc by 5

    if (c == -1 && errno != 0) {
        perror("cant change");
        return 1;
    }

    b = getpriority(PRIO_PROCESS, a);  //new

    if (b == -1 && errno != 0) {
        perror("cant get new");
        return 1;
    }

    printf("New priority: %d\n", b);

    return 0;
}

