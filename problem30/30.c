/*
============================================================================
Name : 30.c
Author : Anuj Chaudhary
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date: 28th sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Define the size of shared memory
#define PROJECT_ID 'A' // Unique project identifier for ftok

int main() {
    key_t key;
    int shmid;
    char *data;
    int mode;

    // Step 1: Create a unique key for the shared memory
    key = ftok("shmfile", PROJECT_ID);
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Create the shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    // Step 3: Attach the shared memory in read/write mode
    data = (char *)shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    // Step 4: Write some data into the shared memory
    printf("Writing data to shared memory...\n");
    strcpy(data, "Hello, Shared Memory!");

    // Step 5: Detach the shared memory
    if (shmdt(data) == -1) {
        perror("shmdt failed");
        exit(EXIT_FAILURE);
    }

    // Step 6: Attach the shared memory in read-only mode (O_RDONLY)
    printf("Attaching to shared memory in read-only mode...\n");
    data = (char *)shmat(shmid, (void *)0, SHM_RDONLY);
    if (data == (char *)(-1)) {
        perror("shmat failed (read-only)");
        exit(EXIT_FAILURE);
    }

    // Step 7: Try to overwrite the shared memory (this should fail)
    printf("Trying to write to read-only shared memory...\n");
    if (strcpy(data, "This should fail") == NULL) {
        perror("Failed to write to read-only shared memory");
    } else {
        printf("Unexpected success in writing to read-only shared memory!\n");
    }

    // Step 8: Detach the shared memory
    if (shmdt(data) == -1) {
        perror("shmdt failed");
        exit(EXIT_FAILURE);
    }

    // Step 9: Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID failed");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory removed successfully.\n");

    return 0;
}

