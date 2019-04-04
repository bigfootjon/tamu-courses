#include <stdio.h>

extern char buffer[32];

void yellow_preflight() {
    printf("\x1B[43m \x1B[0m\x1B[33m ENTER UNLOCK PASSWORD 1: \x1B[0m");
    fgets(buffer, 10, stdin);
}
