/*
============================================================================
Name : 32c.c
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
#include <unistd.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Wait operation for counting semaphore
void semaphore_wait(int semid) {
    struct sembuf sb = {0, -1, 0};  
    semop(semid, &sb, 1);
}

// Signal operation for counting semaphore
void semaphore_signal(int semid) {
    struct sembuf sb = {0, 1, 0};  
    semop(semid, &sb, 1);
}

int main() {
    key_t key;
    int semid;

    // Generate unique key for semaphore
    key = ftok("resource_file", 'R');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create the counting semaphore with an initial value of 2 (2 resources available)
    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize counting semaphore to 2
    union semun sem_attr;
    sem_attr.val = 2;
    if (semctl(semid, 0, SETVAL, sem_attr) == -1) {
        perror("semctl");
        exit(1);
    }

    printf("Waiting for pseudo resource...\n");
    semaphore_wait(semid);  

    // Critical section (using the pseudo resource)
    printf("Resource acquired, working with it...\n");
    sleep(3);  

    semaphore_signal(semid);  
    printf("Resource released.\n");

    return 0;
}

