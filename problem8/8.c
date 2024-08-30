/*
============================================================================
Name : 8.c
Author : Anuj Chaudhary
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read.
Close the file when end of file is reached.
Date: 30th Aug, 2024.
============================================================================
*/
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define size 1024

int main(int input, char *file[]) {
    if (input != 2) return 1;

    int fd = open(file[1], O_RDONLY);
    if (fd < 0) return 1;

    char buffer[size];
    ssize_t total;
    ssize_t i;

    while ((total = read(fd, buffer, size)) > 0) {
        for (i = 0; i < total; i++) {
            if (buffer[i] == '\n') {
                write(STDOUT_FILENO, buffer, i + 1);
                memmove(buffer, buffer + i + 1, total - i - 1);
                total -= i + 1;
                i = -1;
            }
        }
        if (total > 0) {
            write(STDOUT_FILENO, buffer, total);
        }
    }

    close(fd);
    return 0;
}

