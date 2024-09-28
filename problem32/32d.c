/*
============================================================================
Name : 32d.c
Author : Anuj Chaudhary
Description : Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
Date: 28th sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key;
    int semid;

    // Generate unique key
    key = ftok("semaphore_file", 'S');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the semaphore ID
    semid = semget(key, 1, 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Remove the semaphore
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        exit(1);
    }

    printf("Semaphore removed.\n");
    return 0;
}

