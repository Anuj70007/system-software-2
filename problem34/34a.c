/*
============================================================================
Name : 34a.c
Author : Anuj Chaudhary
Description : Write a program to create a concurrent server.
a. use fork
b. use pthread_create
Date: 28th sep, 2024.
============================================================================
*/
// concurrent_server_fork.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080      // Port number
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int valread;

    // Read message from client
    valread = read(client_socket, buffer, BUFFER_SIZE);
    buffer[valread] = '\0'; // Null-terminate the received string
    printf("Received: %s\n", buffer);

    // Send response back to the client
    const char *message = "Hello from the server!";
    send(client_socket, message, strlen(message), 0);
    printf("Response sent to client.\n");

    // Close the client socket
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Step 1: Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Bind the socket to the specified IP and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Step 3: Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // Step 4: Accept an incoming connection
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (client_socket < 0) {
            perror("Accept failed");
            continue; // Continue to accept other clients
        }

        // Step 5: Fork a new process to handle the client
        if (fork() == 0) { // Child process
            close(server_fd); // Close the listening socket in the child
            handle_client(client_socket); // Handle client communication
            exit(0); // Terminate child process
        }

        // Parent process can close the client socket and continue
        close(client_socket);
    }

    // Close the server socket
    close(server_fd);
    return 0;
}

