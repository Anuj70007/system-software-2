/*
============================================================================
Name : 1a.c
Author : Anuj Chaudhary
Description : Create the following types of a files using (i) shell command (ii) system call
a. soft link (symlink system call)
b. hard link (link system call)
c. FIFO (mkfifo Library Function or mknod system call)
Date: 30th Aug, 2024.
============================================================================
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  
int main(int count, char* file[]) 
{ 

    int a = symlink(file[1], file[2]); 
    if (a == 0) { 
    printf("success"); 
    }
    else{
    printf("fails");
    }
  
    return 0; 
}
