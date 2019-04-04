#include <stdio.h>

extern char buffer[32];

void blue_preflight() {
    printf("\x1B[46m \x1B[0m\x1B[36m ENTER CIRCUIT TRAVERSAL PATH: \x1B[0m");
    fgets(buffer, 16, stdin);
}

