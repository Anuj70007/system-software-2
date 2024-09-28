/*
============================================================================
Name : 21b.c
Author : Anuj Chaudhary
Description : Write two programs so that both can communicate by FIFO -Use two way communications
Date: 27th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_TO_READER "fifo_to_reader"
#define FIFO_TO_WRITER "fifo_to_writer"
#define MESSAGE_SIZE 100

int main() {
    // Open FIFOs for reading and writing
    int fd_to_reader = open(FIFO_TO_READER, O_RDONLY);
    int fd_to_writer = open(FIFO_TO_WRITER, O_WRONLY);
    if (fd_to_reader == -1 || fd_to_writer == -1) {
        perror("Failed to open FIFO");
        return 1;
    }

    char message[MESSAGE_SIZE];
    while (1) {
        // Read the message from the writer
        ssize_t bytesRead = read(fd_to_reader, message, MESSAGE_SIZE);
        if (bytesRead > 0) {
            printf("Received from writer: %s\n", message);

            // If the message is "exit", break the loop
            if (strcmp(message, "exit") == 0) {
                break;
            }

            // Sending a response back to the writer
            printf("Enter a response to send to writer: ");
            fgets(message, MESSAGE_SIZE, stdin);
            message[strcspn(message, "\n")] = 0; // Remove newline

            write(fd_to_writer, message, strlen(message) + 1); // +1 for null terminator
            printf("Sent to writer: %s\n", message);
        }
    }

    close(fd_to_reader);
    close(fd_to_writer);
    return 0;
}

