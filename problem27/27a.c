/*
============================================================================
Name : 27a.c
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
    printf("using execl:\n");
    execl("/bin/ls", "ls", "-Rl", (char *)NULL);
    perror("execl fail");
    return 1;
}

