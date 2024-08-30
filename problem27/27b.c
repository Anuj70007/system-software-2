/*
============================================================================
Name : 27b.c
Author : Anuj Chaudhary
Description : Write a program to execute ls -Rl by the following system calls
a. execl
b. execlp
c. execle
d. execv
e. execvp
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("using execlp:\n");
    execlp("ls", "ls", "-Rl", (char *)NULL);
    perror("execlp fail");  
    return 1;
}

