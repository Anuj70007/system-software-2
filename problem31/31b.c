/*
============================================================================
Name : 31b.c
Author : Anuj Chaudhary
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
Date: 28th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define PROJECT_ID 'B'  // Project ID for generating unique key

// Function to initialize the semaphore
int initialize_semaphore(int semid, int value) {
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } sem_attr;

    sem_attr.val = value;  // Set the semaphore value

    if (semctl(semid, 0, SETVAL, sem_attr) == -1) {
        perror("semctl failed");
        return -1;
    }
    return 0;
}

int main() {
    key_t key;
    int semid;

    // Step 1: Create a unique key for the semaphore
    key = ftok("semaphore_file", PROJECT_ID);
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Create the semaphore set (with one semaphore)
    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget failed");
        exit(EXIT_FAILURE);
    }

    // Step 3: Initialize the counting semaphore to a value (e.g., 3)
    if (initialize_semaphore(semid, 3) == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Counting semaphore created and initialized to 3.\n");

    // You can remove the semaphore after use with semctl(semid, 0, IPC_RMID)

    return 0;
}

