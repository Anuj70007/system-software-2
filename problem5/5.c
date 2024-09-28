/*
============================================================================
Name : 5.c
Author : Anuj Chaudhary
Description : Write a program to print the system limitation of
a. maximum length of the arguments to the exec family of functions.
b. maximum number of simultaneous process per user id.
c. number of clock ticks (jiffy) per second.
d. maximum number of open files
e. size of a page
f. total number of pages in the physical memory
g. number of currently available pages in the physical memory
Date: 20th sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <limits.h>

// Function to print system limitations
void print_system_limits() {
    // a. Maximum length of arguments to the exec family
    printf("Maximum length of arguments to the exec family: %ld\n", (long)ARG_MAX);

    // b. Maximum number of simultaneous processes per user ID
    struct rlimit proc_limit;
    if (getrlimit(RLIMIT_NPROC, &proc_limit) == 0) {
        printf("Maximum number of simultaneous processes per user ID: %ld (soft), %ld (hard)\n",
               (long)proc_limit.rlim_cur, (long)proc_limit.rlim_max);
    } else {
        perror("Failed to get process limit");
    }

    // c. Number of clock ticks (jiffy) per second
    printf("Number of clock ticks (jiffy) per second: %ld\n", sysconf(_SC_CLK_TCK));

    // d. Maximum number of open files
    struct rlimit open_files_limit;
    if (getrlimit(RLIMIT_NOFILE, &open_files_limit) == 0) {
        printf("Maximum number of open files: %ld (soft), %ld (hard)\n",
               (long)open_files_limit.rlim_cur, (long)open_files_limit.rlim_max);
    } else {
        perror("Failed to get open files limit");
    }

    // e. Size of a page
    long page_size = sysconf(_SC_PAGE_SIZE);
    printf("Size of a page: %ld bytes\n", page_size);

    // f. Total number of pages in the physical memory
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        printf("Total number of pages in physical memory: %ld\n", info.totalram / page_size);
    } else {
        perror("Failed to get system information");
    }

    // g. Number of currently available pages in physical memory
    printf("Number of currently available pages in physical memory: %ld\n", info.freeram / page_size);
}

int main() {
    print_system_limits();
    return 0;
}

