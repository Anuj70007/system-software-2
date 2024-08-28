#include <stdio.h>
#include <fcntl.h>  
#include <unistd.h> 
#include <stdlib.h> 

int main() {
    const char *name = "happy.txt";
    int fd = creat(name, 0600);
    if (fd == -1) {
        perror("failed");
        exit(EXIT_FAILURE);
    }
    printf("file descriptor is '%s': %d\n", name, fd);
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
  getchar();    
  return 0;
}

