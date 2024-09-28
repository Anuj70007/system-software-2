/*
============================================================================
Name : 4.c
Author : Anuj Chaudhary
Description : Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
Date: 20th sep, 2024.
============================================================================
*/




#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

// Function to read the time stamp counter
static inline uint64_t read_tsc() {
    unsigned int lo, hi;
    // Use the RDTSC instruction
    __asm__ volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    // Variables to hold start and end time
    uint64_t start_time, end_time;

    // Start measuring time
    start_time = read_tsc();

    // Execute getppid() 100 times
    for (int i = 0; i < 100; i++) {
        getppid(); // Get the parent process ID
    }

    // Stop measuring time
    end_time = read_tsc();

    // Calculate the time taken
    uint64_t time_taken = end_time - start_time;

    // Print the result
    printf("Time taken for 100 getppid() calls: %llu CPU cycles\n", (long long unsigned)time_taken);

    return 0;
}

