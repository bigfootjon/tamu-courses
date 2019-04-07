#include <stdio.h>
#include "include.h"

char buffer[32];
bool wire_yellow = true;
bool wire_green  = true;
bool wire_blue = false;
bool wire_red = true;

void gettimeleft(){}

int main() {
    menu();
    yellow();
    printf("YELLOW: %d %s", wire_yellow, buffer);
    blue_preflight();
    printf("BLUE: %d %s", wire_blue, buffer);
    char input[30];
    green_preflight(input);
    printf("GREEN: %d %s", wire_green, input);
    printf("RED: %d", wire_red);
    kaboom();
}
