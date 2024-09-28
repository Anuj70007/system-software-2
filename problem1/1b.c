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

// This function gets called whenever the virtual timer expires
void a(int b) {
    printf("Timer expired: ITIMER_VIRTUAL\n");
}

int main() {
    struct itimerval c;  // Timer settings structure

    // Set up the signal handler for SIGVTALRM
    signal(SIGVTALRM, a);

    // Initial timer value: 10 seconds and 10 microseconds of CPU time
    c.it_value.tv_sec = 10;    // 10 seconds of virtual time
    c.it_value.tv_usec = 10;   // 10 microseconds of virtual time

    // Interval setting for the timer, to repeat every 10 seconds and 10 microseconds
    c.it_interval.tv_sec = 10; // 10 seconds interval
    c.it_interval.tv_usec = 10; // 10 microseconds interval

    // Setting the ITIMER_VIRTUAL timer
    if (setitimer(ITIMER_VIRTUAL, &c, NULL) == -1) {
        perror("Couldn't set ITIMER_VIRTUAL");
        exit(1);
    }

    // Simulating some CPU work to trigger the timer.
    // This loop just keeps the CPU busy.
    while (1) {
        // Busy wait, so we consume some CPU time
    }

    return 0;
}

