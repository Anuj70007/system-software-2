/*
============================================================================
Name : 26.c
Author : Anuj Chaudhary
Description : Write a program to send messages to the message queue. Check $ipcs -q
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
    key_t key = ftok("message_queue_file", PROJECT_ID); //first create file for ftok
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    // Create or get access to the message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);  // 0666 allows read and write for all
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    // Create a message to send
    struct message msg;
    msg.msg_type = 1;  // Message type must be greater than 0
    strcpy(msg.msg_text, "Hello from the message queue!");

    // Send the message to the queue
    if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("msgsnd failed");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to queue: %s\n", msg.msg_text);

    // Optional: send another message to the queue
    strcpy(msg.msg_text, "Another message to the queue!");
    if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("msgsnd failed");
        exit(EXIT_FAILURE);
    }

    printf("Another message sent to queue: %s\n", msg.msg_text);

    // Display message to check the queue with $ ipcs -q
    printf("Check the message queue with $ ipcs -q to see the messages in the queue.\n");

    return 0;
}

