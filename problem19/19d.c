/*
============================================================================
Name : 19d.c
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
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Path to the FIFO
    const char *fifo_path = "my_fifo";

    // Create the FIFO using the mknod system call
    if (mknod(fifo_path, S_IFIFO | 0666, 0) == -1) {
        perror("mknod failed");
        return 1;
    }

    printf("FIFO created using mknod system call\n");

    return 0;
}

