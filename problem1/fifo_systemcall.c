#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    int result = mkfifo("fifo_systemcall", 0666);
    if (result == 0) {
        printf("success\n");
    } else {
        perror("Fails");
    }
    return 0;
}
