#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "include.h"

int *red_preflight() {
    int *r = malloc(sizeof(int)*3);
    r[0] = INT_MAX & rand();
    r[1] = rand();
    r[2] = rand();
    for (int i = 0; i <= 2; ++i) {
        int ri = r[i];
        printf("\x1B[41m \x1B[0m\x1B[31m CLOCK SYNC \x1B[0m%08X\n", ri);
	usleep(500000);
    }
    printf("\x1B[41m \x1B[0m\x1B[31m ENTER CLOCK RESYNCHRONIZATION SEQUENCE: \x1B[0m");
    fgets(buffer, 21, stdin);
    return r;
}
