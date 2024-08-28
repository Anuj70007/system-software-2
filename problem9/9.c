#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void print_file_info(const char *source, FILE *output) {
    struct stat file_stat;

 
    if (stat(source, &file_stat) != 0) {
        perror("Fails");
        exit(EXIT_FAILURE);
    }
    
    fprintf(output, "File: %s\n", source);
    fprintf(output, "  Inode: %ld\n", (long)file_stat.st_ino);
    fprintf(output, "  Number of hard links: %ld\n", (long)file_stat.st_nlink);
    fprintf(output, "  UID: %u\n", file_stat.st_uid);
    fprintf(output, "  GID: %u\n", file_stat.st_gid);
    fprintf(output, "  Size: %ld bytes\n", (long)file_stat.st_size);
    fprintf(output, "  Block size: %ld bytes\n", (long)file_stat.st_blksize);
    fprintf(output, "  Number of blocks: %ld\n", (long)file_stat.st_blocks);    
    fprintf(output, "  Time of last access: %s", ctime(&file_stat.st_atime));
    fprintf(output, "  Time of last modification: %s", ctime(&file_stat.st_mtime));
    fprintf(output, "  Time of last change: %s", ctime(&file_stat.st_ctime));
}

int main(int count, char *file[]) {
    if (count != 3) {
        fprintf(stderr, "=give: %s source file output file\n", file[0]);
        exit(EXIT_FAILURE);
    }

    FILE *output = fopen(file[2], "w");
    if (output == NULL) {
        perror("Failed");
        exit(EXIT_FAILURE);
    }

    print_file_info(file[1], output);

    fclose(output);

    return 0;
}

