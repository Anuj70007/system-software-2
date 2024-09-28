/*
============================================================================
Name : 21a.c
Author : Anuj Chaudhary
Description : Write two programs so that both can communicate by FIFO -Use two way communications
Date: 27th sep, 2024.
============================================================================
*/
// first create manual  mkfifo fifo_to_reader , mkfifo fifo_to_writer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_TO_READER "fifo_to_reader"
#define FIFO_TO_WRITER "fifo_to_writer"
#define MESSAGE_SIZE 100

int main() {
    // Open FIFOs for writing and reading
    int fd_to_reader = open(FIFO_TO_READER, O_WRONLY);
    int fd_to_writer = open(FIFO_TO_WRITER, O_RDONLY);
    if (fd_to_reader == -1 || fd_to_writer == -1) {
        perror("Failed to open FIFO");
        return 1;
    }

    char message[MESSAGE_SIZE];
    while (1) {
        // Sending message to the reader
        printf("Enter a message to send to reader (type 'exit' to quit): ");
        fgets(message, MESSAGE_SIZE, stdin);
        message[strcspn(message, "\n")] = 0; // Remove newline

        if (strcmp(message, "exit") == 0) {
            break;
        }

        // Write the message to the reader FIFO
        write(fd_to_reader, message, strlen(message) + 1); // +1 for null terminator
        printf("Sent to reader: %s\n", message);

        // Read the response from the reader
        read(fd_to_writer, message, MESSAGE_SIZE);
        printf("Received from reader: %s\n", message);
    }

    close(fd_to_reader);
    close(fd_to_writer);
    return 0;
}

