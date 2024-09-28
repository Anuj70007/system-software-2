/*
============================================================================
Name : 2.c
Author : Anuj Chaudhary
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 20th sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

// Function to print resource limits in a simple way
void a(int b, const char *c) {
    struct rlimit d; // Structure to hold the resource limits

    // Try to get the limits for the specified resource
    if (getrlimit(b, &d) == 0) {
        // Print the resource name
        printf("%s:\n", c);

        // Check if the current limit is unlimited
        if (d.rlim_cur == RLIM_INFINITY)
            printf("  Current limit: Unlimited\n");
        else
            printf("  Current limit: %ld\n", (long)d.rlim_cur);

        // Check if the maximum limit is unlimited
        if (d.rlim_max == RLIM_INFINITY)
            printf("  Maximum limit: Unlimited\n");
        else
            printf("  Maximum limit: %ld\n", (long)d.rlim_max);
    } else {
        // If there's an error, print a message
        perror("Oops, something went wrong with getrlimit");
    }
}

int main() {
    // Let's print out various system resource limits using our function
    a(RLIMIT_CPU, "CPU time (seconds)"); // Time the process can use the CPU
    a(RLIMIT_FSIZE, "File size (bytes)"); // Maximum file size the process can create
    a(RLIMIT_DATA, "Data segment size (bytes)"); // Data segment limit
    a(RLIMIT_STACK, "Stack size (bytes)"); // Stack size limit for the process
    a(RLIMIT_CORE, "Core file size (bytes)"); // Max size of core file that can be created
    a(RLIMIT_RSS, "Resident set size (bytes)"); // Max resident set size
    a(RLIMIT_NOFILE, "Number of open files"); // Max number of open files for the process
    a(RLIMIT_AS, "Address space size (bytes)"); // Address space limit for the process
    a(RLIMIT_NPROC, "Number of processes"); // Max number of processes the user can have
    a(RLIMIT_MEMLOCK, "Locked-in-memory address space (bytes)"); // Memory that can be locked
    a(RLIMIT_LOCKS, "Number of file locks"); // Max number of file locks
    a(RLIMIT_SIGPENDING, "Number of pending signals"); // Max number of pending signals
    a(RLIMIT_MSGQUEUE, "Bytes allocated for POSIX message queues"); // Max bytes for message queues
    a(RLIMIT_NICE, "Nice value"); // Limit on the nice value for priority
    a(RLIMIT_RTPRIO, "Real-time priority"); // Max real-time priority for the process
    a(RLIMIT_RTTIME, "Real-time timeout (microseconds)"); // Timeout for real-time scheduling

    return 0;
}

