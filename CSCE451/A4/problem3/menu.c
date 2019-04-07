#include <stdio.h>
#include "include.h"

void menu() {
    gettimeleft();
    printf("----------------------------------------");
    puts("\x1B[93;103m \x1B[0m--\x1B[92;102m \x1B[0m--\x1B[96;106m \x1B[0m--\x1B[91;101m \x1B[0m---");
    int var_14 = 0;
    for (; var_14 < 4; ++var_14) {
        if (var_14 > 2) {
            puts("     HOURS      MINUTES     SECONDS");
        } else {
            puts("ASD");
        }
    }
    printf("+---------------------------------------");
    puts("\x1B[93;103m \x1B[0m--\x1B[92;102m \x1B[0m--\x1B[96;106m \x1B[0m--\x1B[91;101m \x1B[0m--+");
    puts("|                                                   |");
    puts("|      \x1B[93m,\x1B[0m   DR. VON NOIZEMAN'S NUCLEAR BOMB   \x1B[93m,\x1B[0m      |");
    puts("|     \x1B[93m/\x1B[33m!\x1B[93m\\\x1B[0m AUTHORIZED ACCESS ONLY \x1B[31m-\x1B[0m KEEP OUT \x1B[93m/\x1B[33m!\x1B[93m\\\x1B[0m     |");
    puts("|                                                   |");
    if (wire_red == true && wire_yellow == true && wire_blue == true && wire_green == true) {
        puts("|                     \x1B[32m[\x1B[92mDISARM\x1B[32m]\x1B[0m                      |");
    } else {
        char *red_t;
        if (wire_red) {
            red_t = "]";
        } else {
            red_t = "\x1B[32m]\x1B[0m";
        }
        char *red_h;
        if (wire_red) {
            red_h = "\x1B[90m[";
        } else {
            red_h = "\x1B[32m[\x1B[92m";
        }
        char *blue_t = "bt";
        if (wire_blue) {
            blue_t = "]";
        } else {
            blue_t = "\x1B[32m]\x1B[0m";
        }
        char *blue_h;
        if (wire_blue) {
            blue_h = "\x1B[90m[";
        } else {
            blue_h = "\x1B[32m[\x1B[92m";
        }
        char *green_t;
        if (wire_green) {
            green_t = "]";
        } else {
            green_t = "\x1B[32m]\x1B[0m";
        }
        char *green_h;
        if (wire_green) {
            green_h = "\x1B[90m[";
        } else {
            green_h = "\x1B[32m[\x1B[92m";
        }
        char *yellow_t;
        if (wire_yellow) {
            yellow_t = "]";
        } else {
            yellow_t = "\x1B[32m]\x1B[0m";
        }
        char *yellow_h;
        if (wire_yellow) {
            yellow_h = "\x1B[90m[";
        } else {
            yellow_h = "\x1B[32m[\x1B[92m";
        }
        printf("|       %s1%s YELLOW \x1B[0m%s2%s GREEN \x1B[0m%s3%s BLUE \x1B[0m%s4%s RED \x1B[0m      |\n", yellow_h, yellow_t, green_h, green_t, blue_h, blue_t, red_h, red_t);
    }
    puts("|                                                   |");
    puts("+---------------------------------------------------+");
    return;
}

