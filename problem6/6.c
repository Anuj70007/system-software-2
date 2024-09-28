/*
============================================================================
Name : 6.c
Author : Anuj Chaudhary
Description : Write a simple program to create three threads.
Date: 20th sep, 2024.
============================================================================
*/




#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function that will be executed by each thread
void* thread_function(void* arg) {
    long thread_id = (long)arg; // Cast the argument to long to get thread ID
    printf("Hello from thread %ld\n", thread_id);
    return NULL; // Exit the thread
}

int main() {
    pthread_t threads[3]; // Array to hold thread identifiers
    int rc;

    // Create three threads
    for (long i = 0; i < 3; i++) {
        rc = pthread_create(&threads[i], NULL, thread_function, (void*)i);
        if (rc) {
            fprintf(stderr, "Error creating thread %ld: %d\n", i, rc);
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

