/*
============================================================================
Name : 33b.c
Author : Anuj Chaudhary
Description : Write a program to communicate between two machines using socket
Date: 28th sep, 2024.
============================================================================
*/
// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080  // Port the client will connect to
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    const char *message = "Hello from client";

    // Step 1: Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    // Step 2: Define the server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Step 3: Convert IPv4 address from text to binary form (server IP)
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    // Step 4: Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    // Step 5: Send message to the server
    send(sock, message, strlen(message), 0);
    printf("Message sent to server: %s\n", message);

    // Step 6: Receive data from the server
    int valread = read(sock, buffer, BUFFER_SIZE);
    printf("Received from server: %s\n", buffer);

    // Step 7: Close the socket
    close(sock);

    return 0;
}

