/*
============================================================================
Name : 10.c
Author : Anuj Chaudhary
Description : Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10
bytes (use lseek) and write again 10 bytes.
a. check the return value of lseek
b. open the file with od and check the empty spaces in between the data
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd;
    ssize_t size;
    off_t offset;
    const char *data1 = "1987456743"; 
    const char *data2 = "asdfghjkli";

    fd = open("happy.txt", O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("Failed");
        exit(EXIT_FAILURE);
    }

    size = write(fd, data1, 10);
    if (size != 10) {
        perror("Failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    offset = lseek(fd, 10, SEEK_CUR);
    
    if (offset == (off_t) -1) {
        perror("lseek failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("moved to:- %ld\n", offset);

    size = write(fd, data2, 10);
    if (size != 10) {
        perror("Failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);

    return 0;
}

