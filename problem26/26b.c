/*
============================================================================
Name : 26b.c
Author : Anuj Chaudhary
Description : Write a program to execute an executable program.
a. use some executable program
b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *program = "./26a";  
    char *args[] = {program, "name", NULL}; 
    printf("exec program %s with agrument 'name'\n", program);
    execvp(program, args);
    perror("exec fail");
    return 1;
}

