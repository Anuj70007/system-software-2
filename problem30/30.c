/*
============================================================================
Name : 30.c
Author : Anuj Chaudhary
Description : Write a program to run a script at a specific time using a Daemon process.
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

void run() {
 if (fork() != 0) exit(EXIT_SUCCESS);

    if (setsid() < 0) exit(EXIT_FAILURE); 

    if (fork() != 0) exit(EXIT_SUCCESS);

    umask(0);

    chdir("/home/anujchaudhary/Documents/temp/problem30");

    freopen("daemon.log", "w", stdout);
    freopen("daemon.log", "w", stderr);

    close(STDIN_FILENO); 
}
void fun() {
    execl("/home/anujchaudhary/Documents/temp/problem30/scrrpt.sh", "scrrpt.sh", (char *)NULL);
    perror("fail execl");
    exit(EXIT_FAILURE);
}


int main() {
run();
    
    int time = 60; //after 1 min sec
    sleep(time); 
    fun(); 
    
   
    exit(EXIT_SUCCESS);

    return 0;
}

