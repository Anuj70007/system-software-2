#include <fcntl.h>
#include <unistd.h>

#define SIZE 1024

int main(int input, char *file[]) {
    if (input != 3) return 1;

    int Fdo = open(file[1], O_RDONLY);
    int Fdn = open(file[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (Fdo < 0 || Fdn < 0) return 1;

    char buffer[SIZE];
    ssize_t total;
    while ((total = read(Fdo, buffer, SIZE)) > 0) {
        if (write(Fdn, buffer, total) != total) return 1;
    }

    close(Fdo);
    close(Fdn);
    return 0;
}

