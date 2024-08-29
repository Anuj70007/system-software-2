#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

uint64_t rdtsc(void) {
    unsigned int l, h;
    __asm__ ("rdtsc" : "=a" (l), "=d" (h));
    return ((uint64_t)h << 32) | l;
}
int main() {
    uint64_t s, e;
    pid_t id;

    s = rdtsc();
    id = getpid();

    e = rdtsc();
    uint64_t totaltime = e - s;

    printf("pid:- %d\n", id);
    printf("time for pid: %lu cpu cycles\n", totaltime);

    return 0;
}

