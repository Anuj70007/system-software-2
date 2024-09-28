/*
============================================================================
Name : 7.c
Author : Anuj Chaudhary
Description : Write a simple program to print the created thread ids
Date: 20th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function that will be executed by each thread
void* thread_function(void* arg) {
    pthread_t thread_id = pthread_self(); // Get the thread ID
    printf("Thread created with ID: %lu\n", (unsigned long)thread_id);
    return NULL; // Exit the thread
}

int main() {
    pthread_t threads[3]; // Array to hold thread identifiers
    int rc;

    // Create three threads
    for (int i = 0; i < 3; i++) {
        rc = pthread_create(&threads[i], NULL, thread_function, NULL);
        if (rc) {
            fprintf(stderr, "Error creating thread %d: %d\n", i, rc);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have completed.\n");
    return 0; // Exit the program
}

