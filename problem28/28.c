/*
============================================================================
Name : 28.c
Author : Anuj Chaudhary
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 28th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
// remember to have message queue from 27 question can be created

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

    // Structure to hold the message queue info
    struct msqid_ds queue_info;

    // Get current message queue status
    if (msgctl(msgid, IPC_STAT, &queue_info) == -1) {
        perror("msgctl IPC_STAT failed");
        exit(EXIT_FAILURE);
    }

    // Print current permissions
    printf("Current permissions: %o\n", queue_info.msg_perm.mode);

    // Modify the permissions (e.g., make it read-write for owner and group, but not for others)
    queue_info.msg_perm.mode = 0660;

    // Set the new permissions
    if (msgctl(msgid, IPC_SET, &queue_info) == -1) {
        perror("msgctl IPC_SET failed");
        exit(EXIT_FAILURE);
    }

    // Get the updated message queue status
    if (msgctl(msgid, IPC_STAT, &queue_info) == -1) {
        perror("msgctl IPC_STAT failed");
        exit(EXIT_FAILURE);
    }

    // Print updated permissions
    printf("Updated permissions: %o\n", queue_info.msg_perm.mode);

    return 0;
}

