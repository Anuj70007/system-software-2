/*
============================================================================
Name : 12.c
Author : Anuj Chaudhary
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process
Date: 27th sep, 2024.
============================================================================
*/




#include <stdio.h>
#include <unistd.h>  // for fork(), getpid(), getppid(), sleep()
#include <signal.h>  // for kill()
#include <stdlib.h>  // for exit()

int main() {
    pid_t a;  // Variable to store the fork result (PID)

    // Forking the process to create a child
    a = fork();

    if (a < 0) {
        // If fork() returns a negative value, creation of the child process failed
        perror("Fork failed");
        exit(1);
    }

    if (a == 0) {
        // Inside the child process

        printf("Child process: My PID is %d, my parent's PID is %d\n", getpid(), getppid());

        // The child process will now send the SIGKILL signal to the parent (getppid() gets parent's PID)
        printf("Child process: Killing parent process (PID: %d)\n", getppid());
        kill(getppid(), SIGKILL);

        // Sleep for a while to observe that the parent is killed and the child becomes an orphan
        sleep(2);

        // After the sleep, the child will have become an orphan and will be adopted by init
        printf("Child process: Now my parent is PID %d (this should be 1 or init)\n", getppid());

        // Continue doing something (or you can just exit)
        printf("Child process: Doing some work...\n");
        sleep(5);

        printf("Child process: Work done, now exiting.\n");
        exit(0);
    } else {
        // Inside the parent process
        printf("Parent process: My PID is %d, I created a child with PID %d\n", getpid(), a);

        // Sleep to give the child time to kill the parent
        sleep(10);  // This sleep may not be fully executed as the parent will be killed before this finishes
    }

    return 0;
}

