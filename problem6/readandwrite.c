#include <unistd.h>

int main() {
    char start[1024];
    ssize_t size;

    while ((size = read(STDIN_FILENO, start, sizeof(start))) > 0) {
        write(STDOUT_FILENO, start, size);
    }

    return 0;
}

