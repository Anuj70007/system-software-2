#include <stdio.h>
#include <stdlib.h>
extern char **environ;
int main() {
    char **a,*b;

    a = environ;  // environ global var a is now pointing to all environment variabel

    while (*a) {  // looping to all
        b = *a;    //one by one
        printf("%s\n", b);
        a++;
    }

    return 0;
}

