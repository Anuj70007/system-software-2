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

// This function gets called whenever the real-time timer expires
void a(int b) {
    printf("Timer expired: ITIMER_REAL\n");
}

int main() {
    struct itimerval c;  // This struct holds the timer settings

    // We need to set up a handler to catch the SIGALRM signal
    signal(SIGALRM, a);

    // Setting the initial timer value: 10 seconds and 10 microseconds
    c.it_value.tv_sec = 10;    // 10 seconds
    c.it_value.tv_usec = 10;   // 10 microseconds

    // Setting the interval timer: this will go off every 10 seconds and 10 microseconds
    c.it_interval.tv_sec = 10; // 10 seconds interval
    c.it_interval.tv_usec = 10; // 10 microseconds interval

    // Now, let's actually set the timer using ITIMER_REAL
    if (setitimer(ITIMER_REAL, &c, NULL) == -1) {
        perror("Oops, couldn't set ITIMER_REAL");
        exit(1);
    }

    // We're going to wait here indefinitely for the signal to arrive
    while (1) {
        pause(); // This will make the process sleep until a signal arrives
    }

    return 0;
}

