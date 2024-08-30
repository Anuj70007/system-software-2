/*
============================================================================
Name : 15.c
Author : Anuj Chaudhary
Description : . Write a program to display the environmental variable of the user (use environ)
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
extern char **environ;
int main() {
    char **a,*b;

    a = environ;  // environ global var a is now pointing to all environment variabel

    while (*a) {  // looping to all
        b = *a;    //one by one
        printf("%s\n", b);
        a++;
    }

    return 0;
}

