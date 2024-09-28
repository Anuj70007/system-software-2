/*
============================================================================
Name : 1a.c
Author : Anuj Chaudhary
Description : rite a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
a. ITIMER_REAL
b. ITIMER_VIRTUAL
c. ITIMER_PROF
Date: 20th sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

// This function gets called whenever the profiling timer expires
void a(int b) {
    printf("Timer expired: ITIMER_PROF\n");
}

int main() {
    struct itimerval c;  // This struct will hold the timer's settings

    // Set up the handler for the SIGPROF signal
    signal(SIGPROF, a);

    // Setting the initial timer: it will expire in 10 seconds and 10 microseconds
    c.it_value.tv_sec = 10;    // 10 seconds of real time
    c.it_value.tv_usec = 10;   // 10 microseconds of real time

    // Setting the interval: it will trigger every 10 seconds and 10 microseconds
    c.it_interval.tv_sec = 10; // 10 seconds interval
    c.it_interval.tv_usec = 10; // 10 microseconds interval

    // Set the timer using ITIMER_PROF
    if (setitimer(ITIMER_PROF, &c, NULL) == -1) {
        perror("Couldn't set ITIMER_PROF");
        exit(1);
    }

    // Simulating some work to trigger the profiler timer.
    // This loop just keeps the CPU busy.
    while (1) {
        // Busy-wait loop to keep the CPU engaged
    }

    return 0;
}

