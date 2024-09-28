/*
============================================================================
Name : 27a.c
Author : Anuj Chaudhary
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
Date: 28th sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PROJECT_ID 'C'  // Unique project identifier for key generation

// Define the structure for the message
struct message {
    long msg_type;         // Message type, must be > 0
    char msg_text[100];    // Message content
};

int main() {
    // Generate a unique key for the message queue
    key_t key = ftok("message_queue_file", PROJECT_ID);
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    // Get access to the message queue (must already exist)
    int msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    // Create a message structure to receive the message
    struct message msg;

    // Receive a message from the queue (using flag 0 - blocking)
    if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(EXIT_FAILURE);
    }

    // Print the received message
    printf("Received message: %s\n", msg.msg_text);

    return 0;
}

