/*
============================================================================
Name : 32b.c
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
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Define size of shared memory

union semun {
    int val; 
    struct semid_ds *buf;
    unsigned short *array;
};

void semaphore_wait(int semid) {
    struct sembuf sb = {0, -1, 0};  
    semop(semid, &sb, 1);
}

void semaphore_signal(int semid) {
    struct sembuf sb = {0, 1, 0};  
    semop(semid, &sb, 1);
}

int main() {
    key_t key;
    int semid, shmid;
    char *shared_mem;
    char buffer[100];

    // Generate key for semaphore and shared memory
    key = ftok("shmfile", 'S');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create binary semaphore
    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the semaphore to 1 (unlocked)
    union semun sem_attr;
    sem_attr.val = 1;
    if (semctl(semid, 0, SETVAL, sem_attr) == -1) {
        perror("semctl");
        exit(1);
    }

    // Create shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory
    shared_mem = (char *)shmat(shmid, NULL, 0);
    if (shared_mem == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Enter critical section (protect shared memory from concurrent writes)
    semaphore_wait(semid);  

    // Writing to shared memory
    printf("Enter data to write to shared memory: ");
    fgets(buffer, 100, stdin);
    strncpy(shared_mem, buffer, SHM_SIZE);
    printf("Data written to shared memory.\n");

    semaphore_signal(semid);  

    // Detach from shared memory
    shmdt(shared_mem);

    // Remove semaphore and shared memory
    shmctl(shmid, IPC_RMID, NULL); 
    semctl(semid, 0, IPC_RMID);

    return 0;
}

