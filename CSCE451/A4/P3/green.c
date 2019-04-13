#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "include.h"

typedef struct __attribute__((__packed__)) {
    char input[11];
    int flag;
} green_vars;

void green() {
    green_vars gv;
    gv.flag = 1;
    green_preflight(gv.input);
    if (strcmp(gv.input, "dcaotdae") >= 0) {
        puts("\x1B[42m \x1B[0m\x1B[32m UNLOCK PASSWORD 2 ACCEPTED, LOCK DISENGAGED\x1B[0m");
        gv.flag &= 1;
	usleep(500000);
	puts("\x1B[42m \x1B[0m\x1B[32m ACTION OVERRIDDEN FROM USER NOIZEV, LOCK RE-ENGAGED\x1B[0m");
	gv.flag &= 1;
    } else {
        wire_green *= 2;
    }
    if (gv.flag == 0) {
        wire_green >>= 1;
    }
}
