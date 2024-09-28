/*
============================================================================
Name : 22b.c
Author : Anuj Chaudhary
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO
Date: 27th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 100

int main() {
    // Open the FIFO for writing
    int fifo_fd = open(FIFO_NAME, O_WRONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for writing");
        return 1;
    }

    // Sending messages to the FIFO
    char message[BUFFER_SIZE];
    printf("Enter a message to send to the reader (type 'exit' to quit): ");
    while (1) {
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = 0; // Remove newline

        if (strcmp(message, "exit") == 0) {
            break; // Exit if the user types 'exit'
        }

        // Write the message to the FIFO
        write(fifo_fd, message, strlen(message) + 1); // +1 for null terminator
        printf("Written to FIFO: %s\n", message);
    }

    close(fifo_fd); // Close the FIFO
    return 0;
}

