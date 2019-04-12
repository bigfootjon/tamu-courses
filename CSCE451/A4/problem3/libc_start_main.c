#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "include.h"

void *libc_start_main(void *ignored) {
	for (;;sleep(1)) {
        if (libc_start_main_done == 1) {
            printf("----------------------------------------");
            puts("\x1B[93;103m \x1B[0m--\x1B[92;102m \x1B[0m--\x1B[96;106m \x1B[0m--\x1B[91;101m \x1B[0m---");
            int var_14 = 0;
            for (; var_14 < 4; ++var_14) {
                if (var_14 > 2) {
                    printf("     HOURS      MINUTES     SECONDS     ");
                } else {
                    int i;
                    switch (var_14) {
                        case 0: i =  0; break;
                        case 1: i = 20; break;
                        case 2: i = 29; break;
                    }
                    printf("\x1B[91m   %s%s  %s%s  %s%s   \x1B[0m", display[i], display[i], display[i], display[i], display[i], display[i]);
                }
                char yellow_symbol;
                if (wire_yellow) {
                        yellow_symbol = ' ';
                } else if (var_14 != 0 && var_14 != 3) {
                    yellow_symbol = '.';
                } else {
                        yellow_symbol = '*';
                }
                char *yellow_bar;
                if (wire_yellow) {
                        yellow_bar = "\x1B[103m";
                } else {
                        yellow_bar = "\x1B[93m";
                }
                printf("%s%c\x1B[0m  ", yellow_bar, yellow_symbol);

                char green_symbol;
                if (wire_green) {
                        green_symbol = ' ';
                } else if (var_14 != 0 && var_14 != 3) {
                    green_symbol = '.';
                } else {
                        green_symbol = '*';
                }
                char *green_bar;
                if (wire_green) {
                        green_bar = "\x1B[102m";
                } else {
                        green_bar = "\x1B[92m";
                }
                printf("%s%c\x1B[0m  ", green_bar, green_symbol);

                char blue_symbol;
                if (wire_blue) {
                        blue_symbol = ' ';
                } else if (var_14 != 0 && var_14 != 3) {
                    blue_symbol = '.';
                } else {
                        blue_symbol = '*';
                }
                char *blue_bar;
                if (wire_blue) {
                        blue_bar = "\x1B[106m";
                } else {
                        blue_bar = "\x1B[96m";
                }
                printf("%s%c\x1B[0m  ", blue_bar, blue_symbol);

                char red_symbol;
                if (wire_red) {
                        red_symbol = ' ';
                } else if (var_14 != 0 && var_14 != 3) {
                    red_symbol = '.';
                } else {
                        red_symbol = '*';
                }
                char *red_bar;
                if (wire_red) {
                        red_bar = "\x1B[101m";
                } else {
                        red_bar = "\x1B[91m";
                }
                printf("%s%c\x1B[0m  ", red_bar, red_symbol);

                putchar('\n');
            }
	    } else if(wire_red > 1 || wire_green > 1 || wire_blue > 1 || wire_yellow > 1) {
                kaboom();
	    } else {
	        continue;
	    }
	    raise(SIGSEGV);
	}
	return NULL;
}
