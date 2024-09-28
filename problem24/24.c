/*
============================================================================
Name : 24.c
Author : Anuj Chaudhary
Description : Write a program to create a message queue and print the key and message queue id.
Date: 27th sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#define PROJECT_ID 'A' // Unique project identifier

struct message {
    long msg_type; // Message type
    char msg_text[100]; // Message content
};

int main() {
    // Generate a unique key using ftok
    key_t key = ftok("message_queue_file", PROJECT_ID); // Use a file and a project ID
    if (key == -1) {
        perror("ftok failed");
        return EXIT_FAILURE;
    }

    // Create a message queue
    int msgid = msgget(key, 0666 | IPC_CREAT); // Create the queue with read/write permissions
    if (msgid == -1) {
        perror("msgget failed");
        return EXIT_FAILURE;
    }

    // Print the generated key and message queue ID
    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    // Cleanup: Remove the message queue (optional)
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

