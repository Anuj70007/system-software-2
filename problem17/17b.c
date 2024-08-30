/*
============================================================================
Name : 17a.c
Author : Anuj Chaudhary
Description : Write a program to simulate online ticket reservation. Implement write lock
Write a program to open a file, store a ticket number and exit. Write a separate program, to
open the file, implement write lock, read the ticket number, increment the number and print
the new ticket number then close the file.
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int desc;
    struct {
        int ticketno;
    } m;

    struct flock lock;


    desc = open("happy.txt", O_RDWR);

   
    lock.l_type = F_WRLCK;   
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;        
    lock.l_len = sizeof(m);   
    lock.l_pid = getpid();    

    fcntl(desc, F_SETLKW, &lock);

    printf("Inside critical section\n");

    read(desc, &m, sizeof(m));

    printf("Current ticket number: %d\n", m.ticketno);
    m.ticketno++;

    lseek(desc, 0, SEEK_SET);
    write(desc, &m, sizeof(m));

    printf("Press Enter to unlock\n");
    getchar();  

    
    lock.l_type = F_UNLCK;
    fcntl(desc, F_SETLK, &lock);

    printf("Out of critical section\n");

    close(desc);

    return 0;
}

