/*
============================================================================
Name : 26a.c
Author : Anuj Chaudhary
Description : Write a program to execute an executable program.
a. use some executable program
b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>

int main(int count, char *in[]) {
    if (count > 1) {
        printf("hello my name is , %s!\n", in[1]);
    } else {
        printf("new\n");
    }
    return 0;
}

