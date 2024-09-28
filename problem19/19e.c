/*
============================================================================
Name : 19e.c
Author : Anuj Chaudhary
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
d. mknod system call
e. mkfifo library function
Date: 27th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    // Path to the FIFO
    const char *fifo_path = "my_fifo";

    // Create the FIFO using the mkfifo library function
    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo failed");
        return 1;
    }

    printf("FIFO created using mkfifo library function\n");

    return 0;
}

