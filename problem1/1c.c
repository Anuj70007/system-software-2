/*
============================================================================
Name : 1c.c
Author : Anuj Chaudhary
Description : Create the following types of a files using (i) shell command (ii) system call
a. soft link (symlink system call)
b. hard link (link system call)
c. FIFO (mkfifo Library Function or mknod system call)
Date: 30th Aug, 2024.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    int result = mkfifo("fifo_systemcall", 0666);
    if (result == 0) {
        printf("success\n");
    } else {
        perror("Fails");
    }
    return 0;
}
