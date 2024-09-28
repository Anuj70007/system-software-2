/*
============================================================================
Name : 33a.c
Author : Anuj Chaudhary
Description : Write a program to communicate between two machines using socket
Date: 28th sep, 2024.
============================================================================
*/
// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080  // Define the port the server will listen on
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *message = "Hello from server";

    // Step 1: Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Define server address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Accept any incoming connections
    address.sin_port = htons(PORT);  // Set the port

    // Step 3: Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Step 4: Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // Step 5: Accept incoming connection from client
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // Step 6: Read data from the client
    int valread = read(new_socket, buffer, BUFFER_SIZE);
    printf("Received from client: %s\n", buffer);

    // Step 7: Send a response back to the client
    send(new_socket, message, strlen(message), 0);
    printf("Message sent to client: %s\n", message);

    // Step 8: Close the socket
    close(new_socket);
    close(server_fd);

    return 0;
}

