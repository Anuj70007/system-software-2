/*
============================================================================
Name : 5.c
Author : Anuj Chaudhary
Description : Write a program to create five new files with infinite loop. Execute the program in the background
and check the file descriptor table at /proc/pid/fd.
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    const char *files[5] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    int fds[5]; 

    while (1) {
        for (int i = 0; i < 5; i++) {
            fds[i] = open(files[i], O_RDWR | O_CREAT | O_TRUNC, 0666);
            if (fds[i] == -1) {
                perror("Error");
                exit(1);
            }
            printf("File name:- %s file descriptor:- %d\n", files[i], fds[i]);
        }
        
        sleep(10);
        for (int i = 0; i < 5; i++) {
            close(fds[i]);
        }

        sleep(1); 
    }

    return 0;
}

