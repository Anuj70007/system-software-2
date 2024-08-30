/*
============================================================================
Name : 18b.c
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
    int input;
    desc = open("happy.txt", O_RDWR);
    if (desc < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Select mangoes from 1, 2, 3: ");
    scanf("%d", &input);

    struct {
        int mangoes;
        int mangoes_c;
    } m;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (input - 1) * sizeof(m);
    lock.l_len = sizeof(m);
    lock.l_pid = getpid();

    lseek(desc, (input - 1) * sizeof(m), SEEK_SET);

    if (read(desc, &m, sizeof(m)) < 0) {
        perror("read");
        close(desc);
        exit(EXIT_FAILURE);
    }

    printf("Before critical section\n");

    // Lock the record
    if (fcntl(desc, F_SETLKW, &lock) < 0) {
        perror("fcntl F_SETLKW");
        close(desc);
        exit(EXIT_FAILURE);
    }

    printf("Current mangoes: %d\n", m.mangoes_c);
    m.mangoes_c++;

    lseek(desc, -1 * sizeof(m), SEEK_CUR);
    if (write(desc, &m, sizeof(m)) < 0) {
        perror("write");
        close(desc);
        exit(EXIT_FAILURE);
    }

    printf("To buy mangoes, press Enter\n");
    getchar();
    getchar();  


    lock.l_type = F_UNLCK;
    if (fcntl(desc, F_SETLK, &lock) < 0) {
        perror("fcntl F_SETLK");
        close(desc);
        exit(EXIT_FAILURE);
    }

    printf("Mangoes bought: %d\n", m.mangoes_c);

    close(desc);
    return 0;
}

