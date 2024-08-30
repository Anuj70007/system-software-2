/*
============================================================================
Name : 18a.c
Author : Anuj Chaudhary
Description : Write a program to perform Record locking.
a. Implement write lock
b. Implement read lock
Create three records in a file. Whenever you access a particular record, first lock it then modify/access
to avoid race condition
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int desc;
    struct {
        int mangoes;
        int mangoes_c;
    } m[3];
    for (int i = 0; i < 3; i++) {
        m[i].mangoes = i + 1;
        m[i].mangoes_c = 0;
    }
    desc = open("happy.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (desc < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (write(desc, m, sizeof(m)) < 0) {
        perror("write");
        close(desc);
        exit(EXIT_FAILURE);
    }
    close(desc);

    return 0;
}

