#include <stdio.h>

void green_preflight(char *input) {
    printf("\x1B[42m \x1B[0m\x1B[32m ENTER UNLOCK PASSWORD 2: \x1B[0m");
    fgets(input, 20, stdin);
}

