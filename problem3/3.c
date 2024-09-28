/*
============================================================================
Name : 3.c
Author : Anuj Chaudhary
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 20th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

// Function to set a new limit for a specified resource
void set_limit(int a, rlim_t b, rlim_t c) {
    struct rlimit d; // Struct to hold the new limits

    d.rlim_cur = b; // Set the current limit (soft limit)
    d.rlim_max = c; // Set the maximum limit (hard limit)

    // Now, let's try to apply this limit using setrlimit
    if (setrlimit(a, &d) == 0) {
        printf("Successfully set the limit for the resource.\n");
    } else {
        // If there's an error, print out what's wrong
        perror("Error setting the limit");
    }
}

int main() {
    int resource = RLIMIT_NOFILE; // We are setting the limit for open files
    rlim_t soft_limit = 1024; // Setting the soft limit to 1024 files
    rlim_t hard_limit = 2048; // Setting the hard limit to 2048 files

    // Print what we are about to do
    printf("Setting the limit for the number of open files...\n");
    printf("Soft limit: %ld, Hard limit: %ld\n", (long)soft_limit, (long)hard_limit);

    // Call our function to set the resource limit
    set_limit(resource, soft_limit, hard_limit);

    return 0;
}

