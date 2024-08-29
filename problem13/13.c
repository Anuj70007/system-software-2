#include <sys/select.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    fd_set a;
    struct timeval b;
    int c;

    FD_ZERO(&a);
    FD_SET(STDIN_FILENO, &a);

    b.tv_sec = 10;
    b.tv_usec = 0;
    c = select(STDIN_FILENO + 1, &a, NULL, NULL, &b);
    if (c == -1) {
        perror("select");
        return 1;
    }
    if (c == 0) { 
        printf("No data available within %d seconds.\n", 10);
    } else {
        if (FD_ISSET(STDIN_FILENO, &a)) {
            char data[256];
            ssize_t reading = read(STDIN_FILENO, data, 255);
            if (reading > 0) {
                data[reading] = '\0';
                printf("data total: %s\n", data);
            } else if (reading == 0) {
                printf("end detected.\n");
            } else {
                perror("read");
                return 1;
            }
        }
    }

    return 0;
}

