/*
============================================================================
Name : 25.c
Author : Anuj Chaudhary
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date: 28th sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

#define PROJECT_ID 'B' // Unique project identifier for key generation

int main() {
    // Generate a unique key for the message queue
    key_t key = ftok("message_queue_file", PROJECT_ID); // created file message queue fir ftok
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    // Create or get access to a message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    // Structure to hold message queue information
    struct msqid_ds msg_info;

    // Get message queue information using msgctl()
    if (msgctl(msgid, IPC_STAT, &msg_info) == -1) {
        perror("msgctl failed");
        exit(EXIT_FAILURE);
    }

    // Access permissions (mode)
    printf("Access Permissions: %o\n", msg_info.msg_perm.mode);

    // User ID and Group ID
    printf("Owner UID: %d\n", msg_info.msg_perm.uid);
    printf("Owner GID: %d\n", msg_info.msg_perm.gid);

    // Time of last message sent and received
    printf("Last message sent time: %s", ctime(&msg_info.msg_stime));
    printf("Last message received time: %s", ctime(&msg_info.msg_rtime));

    // Time of last change in message queue
    printf("Last change time: %s", ctime(&msg_info.msg_ctime));

    // Size of the message queue (in bytes)
    printf("Current size of the queue (bytes): %lu\n", msg_info.__msg_cbytes);

    // Number of messages currently in the queue
    printf("Number of messages in the queue: %lu\n", msg_info.msg_qnum);

    // Maximum number of bytes allowed in the queue
    printf("Maximum number of bytes allowed in the queue: %lu\n", msg_info.msg_qbytes);

    // PID of the process that sent the last message
    printf("PID of last msgsnd: %d\n", msg_info.msg_lspid);

    // PID of the process that received the last message
    printf("PID of last msgrcv: %d\n", msg_info.msg_lrpid);

    // Optional cleanup: Remove the message queue (comment this if you want to keep the queue)
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl (remove queue) failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

