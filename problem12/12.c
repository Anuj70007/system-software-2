/*
============================================================================
Name : 12.c
Author : Anuj Chaudhary
Description : Write a program to find out the opening mode of a file. Use fcntl.
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void check(int in) {    //chackeing
    if (in & O_RDONLY) { 
        printf("readonly mode\n");
    }
    if (in & O_WRONLY) {
        printf("writeonly mode\n");
    }
    if (in & O_RDWR) {
        printf("read/Write mode\n");
    }
    if (!(in & (O_RDONLY | O_WRONLY | O_RDWR))) {
        printf("not known\n");
    }
}

int main() {
    int fd = open("happy.txt", O_RDWR | O_CREAT, 0644); //opening file
    if (fd < 0) {
        perror("fails top open file");
        return 1;
    }

    int g = fcntl(fd, F_GETFL); // getting fd using fcntl
    if (g < 0) {
        perror("fails getting fd");
        close(fd);
        return 1;
    }
   check (g); //check

    close(fd); //close fd

    return 0;
}

