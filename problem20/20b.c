/*
============================================================================
Name : 20b.c
Author : Anuj Chaudhary
Description : Write two programs so that both can communicate by FIFO -Use one way communication
Date: 27th sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "my_fifo"
#define MESSAGE_SIZE 100

int main() {
    // Open the FIFO for reading
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open FIFO for reading");
        return 1;
    }

    // Reading messages from the FIFO
    char message[MESSAGE_SIZE];
    while (1) {
        // Read the message from the FIFO
        ssize_t bytesRead = read(fd, message, MESSAGE_SIZE);
        if (bytesRead > 0) {
            printf("Read from FIFO: %s\n", message);
        }
    }

    close(fd); // Close the FIFO
    return 0;
}

