#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *file = "happy.txt";
    int fd = open(file, O_RDWR);
    if (fd == -1) {
        perror("Error opening existing file");
    } else {
        printf("Success: filename: '%s' and fd: %d\n", file, fd);
        close(fd);
    }
    fd = open("newhappy.txt", O_RDWR | O_CREAT | O_EXCL, 0666);
    if (fd == -1) {
        perror("Error creating file with O_CREAT | O_EXCL");
    } else {
        printf("Success: filename: 'newhappy.txt' and fd: %d\n", fd);
        close(fd);
    }

    return 0;
}

