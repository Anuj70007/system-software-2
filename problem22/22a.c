/*
============================================================================
Name : 21b.c
Author : Anuj Chaudhary
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO
Date: 27th sep, 2024.
============================================================================
*/

// create manual mkfifo my_fifo
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>

#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 100

int main() {
    // Open the FIFO for reading
    int fifo_fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO");
        return 1;
    }

    // Set up the select() parameters
    fd_set read_fds;
    struct timeval timeout;
    int retval;

    // Wait for data for up to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    while (1) {
        // Clear the set and add the FIFO file descriptor
        FD_ZERO(&read_fds);
        FD_SET(fifo_fd, &read_fds);

        // Wait for data to be available
        retval = select(fifo_fd + 1, &read_fds, NULL, NULL, &timeout);

        if (retval == -1) {
            perror("select() failed");
            close(fifo_fd);
            return 1;
        } else if (retval == 0) {
            // Timeout occurred, no data was received
            printf("No data within 10 seconds. Timeout occurred.\n");
            break; // Exit the loop if no data is received
        } else {
            // Data is available to read
            char buffer[BUFFER_SIZE];
            ssize_t bytesRead = read(fifo_fd, buffer, BUFFER_SIZE - 1);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0'; // Null-terminate the string
                printf("Read from FIFO: %s\n", buffer);
            } else if (bytesRead == -1) {
                perror("Failed to read from FIFO");
                break;
            }
        }

        // Reset the timeout for the next iteration
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
    }

    close(fifo_fd); // Close the FIFO
    return 0;
}

