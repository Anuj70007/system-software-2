/*
============================================================================
Name : 32a.c
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

// Union for semctl operations
union semun {
    int val;  // Value for SETVAL
    struct semid_ds *buf;  // Buffer for IPC_STAT, IPC_SET
    unsigned short *array;  // Array for GETALL, SETALL
};

// Function to perform semaphore operations (P operation)
void semaphore_wait(int semid) {
    struct sembuf sb = {0, -1, 0};  // Wait operation
    semop(semid, &sb, 1);
}

// Function to perform semaphore operations (V operation)
void semaphore_signal(int semid) {
    struct sembuf sb = {0, 1, 0};  // Signal operation
    semop(semid, &sb, 1);
}

int main() {
    key_t key;
    int semid;
    int ticket_number = 100;  // Start ticket number

    // Generate unique key for semaphore
    key = ftok("ticket_file", 'T');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create the semaphore set (binary semaphore, 1 semaphore)
    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the binary semaphore to 1 (unlocked)
    union semun sem_attr;
    sem_attr.val = 1;
    if (semctl(semid, 0, SETVAL, sem_attr) == -1) {
        perror("semctl");
        exit(1);
    }

    // Simulate ticket number creation in a critical section
    printf("Waiting for critical section to create ticket...\n");
    semaphore_wait(semid);  // P operation (wait)
    
    // Critical section (ticket creation)
    printf("Creating ticket...\n");
    sleep(2);  // Simulate time to create a ticket
    ticket_number++;
    printf("Ticket number created: %d\n", ticket_number);

    semaphore_signal(semid);  // V operation (signal)

    // Remove semaphore after use
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        exit(1);
    }

    printf("Semaphore removed.\n");
    return 0;
}

