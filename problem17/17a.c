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
int main()
{
int desc;
struct{
int ticketno;
}m;
m.ticketno=200;
desc=open("happy.txt",O_CREAT|O_RDWR, 0744);
write(desc,&m,sizeof(m));
close(desc);
desc=open("happy.txt",O_RDONLY);
read(desc,&m,sizeof(m));
printf("ticket no:- %d\n",m.ticketno);
close(desc);
}
