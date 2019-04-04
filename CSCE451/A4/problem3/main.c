#include <stdio.h>
#include "include.h"

char buffer[32];
bool yellow_wire = false;
bool green_wire = false;
bool blue_wire = false;
bool red_wire = false;

int main() {
    yellow();
    printf("YELLOW: %d %s", yellow_wire, buffer);
    blue_preflight();
    printf("BLUE: %d %s", blue_wire, buffer);
    char input[30];
    green_preflight(input);
    printf("GREEN: %d %s", green_wire, input);
    printf("RED: %d", red_wire);
    kaboom();
}
