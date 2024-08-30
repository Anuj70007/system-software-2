/*
============================================================================
Name : 11.c
Author : Anuj Chaudhary
Description : Write a program to open a file, duplicate the file descriptor and append the file with both the
descriptors and check whether the file is updated properly or not.
a. use dup
b. use dup2
c. use fcntl
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int desc = open("happy.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (desc < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    int desc_dup = dup(desc);
    if (desc_dup < 0) {
        perror("failed dup");
        close(desc);
        exit(EXIT_FAILURE);
    }
    int desc_dup2 = dup2(desc, 10); //10 is the number we have given as which fd we want
    if (desc_dup2 < 0) {
        perror("fail dup2");
        close(desc);
        close(desc_dup);
        exit(EXIT_FAILURE);
    }
    int desc_fcntl = fcntl(desc, F_DUPFD, 11);
    if (desc_fcntl < 0) {
        perror("fail fcntl");
        close(desc);
        close(desc_dup);
        close(desc_dup2);
        exit(EXIT_FAILURE);
    }
 const char *mess[] = { "old one FD\n","dup1 FD\n","dup2 FD\n",
        "fcntl FD\n"
    };
    write(desc, mess[0], strlen(mess[0]));
    write(desc_dup, mess[1], strlen(mess[1]));
    write(desc_dup2, mess[2], strlen(mess[2]));
    write(desc_fcntl, mess[3], strlen(mess[3]));
    
    close(desc);
    close(desc_dup);
    close(desc_dup2);
    close(desc_fcntl);
    
    FILE *input = fopen("happy.txt", "r");
    if (input) {
        char line[256];
        printf("contents:\n");
        while (fgets(line, sizeof(line), input)) {
            printf("%s", line);}fclose(input);} 
      else {
        perror("fail to open");
    }

    return 0;
}

