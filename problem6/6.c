/*
============================================================================
Name : 6.c
Author : Anuj Chaudhary
Description : rite a program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 30th Aug, 2024.
============================================================================
*/
#include <unistd.h>

int main() {
    char start[1024];
    ssize_t size;

    while ((size = read(STDIN_FILENO, start, sizeof(start))) > 0) {
        write(STDOUT_FILENO, start, size);
    }

    return 0;
}

