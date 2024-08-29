#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void set_lock(int desc, int type) {
    struct flock lock;
    lock.l_type = type;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;  

    if (fcntl(desc, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
}

void release_lock(int desc) {
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(desc, F_SETLK, &lock) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int desc; //file descriptor
    const char *input = "happy.txt";
    
    desc = open(input, O_RDWR | O_CREAT, 0666);
    if (desc == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("opened successfully.\n");
    printf("write lock :-\n");
    set_lock(desc, F_WRLCK);
    printf("Write lock, enter to release.\n");
    getchar();  
    
    release_lock(desc);
    printf("Write lock released.\n");

    printf("Acquiring read lock...\n");
    set_lock(desc, F_RDLCK);
    printf("Read lock, enter to release.\n");
    getchar();
    release_lock(desc);
    printf("Read lock released.\n");

    close(desc);
    return 0;
}

