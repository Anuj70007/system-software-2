/*
============================================================================
Name : 7.c
Author : Anuj Chaudhary
Description :Write a program to copy file1 into file2 ($cp file1 file2)
Date: 30th Aug, 2024.
============================================================================
*/
#include <fcntl.h>
#include <unistd.h>

int main(int input, char *file[]) {
    if (input != 3) return 1;

    int Fdo = open(file[1], O_RDONLY);
    int Fdn = open(file[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (Fdo < 0 || Fdn < 0) return 1;

    char buffer[1024];
    ssize_t total;
    while ((total = read(Fdo, buffer, 1024)) > 0) {
        if (write(Fdn, buffer, total) != total) return 1;
    }

    close(Fdo);
    close(Fdn);
    return 0;
}

