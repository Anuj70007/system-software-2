/*
============================================================================
Name : 14.c
Author : Anuj Chaudhary
Description : Write a program to find the type of a file.
a. Input should be taken from command line.
b. program should be able to identify any type of a file.
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("Regular\n");
    } else if (S_ISDIR(mode)) {
        printf("folder\n");
    } else if (S_ISLNK(mode)) {
        printf("link file\n");
    } else if (S_ISCHR(mode)) {
        printf("Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO pipe file \n");
    } else if (S_ISSOCK(mode)) {
        printf("Socket\n");
    } else {
        printf("not known\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "error: %s give file \n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    struct stat file_stat;

    if (stat(file_path, &file_stat) != 0) {
        perror("stat");
        return EXIT_FAILURE;
    }
    type(file_stat.st_mode);

    return EXIT_SUCCESS;
}

