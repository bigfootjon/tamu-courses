#include <stdio.h>
#include "include.h"

char buffer[32];

int main() {
    yellow_preflight();
    printf("%s", buffer);
    blue_preflight();
    printf("%s", buffer);
    char input[30];
    green_preflight(input);
    printf("%s", input);
    kaboom();
}
