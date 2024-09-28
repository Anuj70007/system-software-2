/*
============================================================================
Name : 20a.c
Author : Anuj Chaudhary
Description : Write two programs so that both can communicate by FIFO -Use one way communication
Date: 27th sep, 2024.
============================================================================
*/

//create mauall fifo file mkfifo my_fifo then writers and readers code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "my_fifo"
#define MESSAGE_SIZE 100

int main() {
    // Open the FIFO for writing
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open FIFO for writing");
        return 1;
    }

    // Writing messages to the FIFO
    char message[MESSAGE_SIZE];
    while (1) {
        printf("Enter a message (or type 'exit' to quit): ");
        fgets(message, MESSAGE_SIZE, stdin);

        // Remove newline character from fgets
        message[strcspn(message, "\n")] = 0;

        // Check for exit command
        if (strcmp(message, "exit") == 0) {
            break;
        }

        // Write the message to the FIFO
        write(fd, message, strlen(message) + 1); // +1 for null terminator
        printf("Written to FIFO: %s\n", message);
    }

    close(fd); // Close the FIFO
    return 0;
}

