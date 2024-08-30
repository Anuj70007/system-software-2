/*
============================================================================
Name : 3.c
Author : Anuj Chaudhary
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call.
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <fcntl.h>  
#include <unistd.h> 
#include <stdlib.h> 

int main() {
    const char *name = "happy.txt";
    int fd = creat(name, 0600);
    if (fd == -1) {
        perror("failed");
        exit(EXIT_FAILURE);
    }
    printf("file descriptor is '%s': %d\n", name, fd);
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
  getchar();    
  return 0;
}

