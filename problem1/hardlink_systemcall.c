#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  
int main(int count, char* file[]) 
{ 

    int a = link(file[1], file[2]); 
    if (a == 0) { 
    printf("success"); 
    }
    else{
    printf("fails");
    }
  
    return 0; 
}
