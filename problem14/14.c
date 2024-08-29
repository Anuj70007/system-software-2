#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("Regular\n");
    } else if (S_ISDIR(mode)) {
        printf("folder\n");
    } else if (S_ISLNK(mode)) {
        printf("link file\n");
    } else if (S_ISCHR(mode)) {
        printf("Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO pipe file \n");
    } else if (S_ISSOCK(mode)) {
        printf("Socket\n");
    } else {
        printf("not known\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "error: %s give file \n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    struct stat file_stat;

    if (stat(file_path, &file_stat) != 0) {
        perror("stat");
        return EXIT_FAILURE;
    }
    type(file_stat.st_mode);

    return EXIT_SUCCESS;
}

