/*
============================================================================
Name : 29.c
Author : Anuj Chaudhary
Description : Write a program to remove the message queue.
Date: 28th sep, 2024.
============================================================================
*/
// first create message queue to be removed use 27 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PROJECT_ID 'C'  // Unique project identifier for key generation

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

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID failed");
        exit(EXIT_FAILURE);
    }

    printf("Message queue removed successfully.\n");

    return 0;
}

