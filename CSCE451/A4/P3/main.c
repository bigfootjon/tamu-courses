#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <pthread.h>
#include "include.h"

char buffer[32];
int wire_yellow = true;
int wire_green = true;
int wire_blue = true;
int wire_red = true;
int libc_start_main_done = 0;

int main() {
    pthread_t lsm_thread;

    pthread_create(&lsm_thread, NULL, libc_start_main, NULL);
    signal(10, disarm_handler);

    bool show_menu = true;
    char input[20];
    for (;;) {
        if (show_menu) {
            menu();
	}
	printf("\x1B[100m \x1B[0m\x1B[90m MENU SELECTION: \x1B[0m");
	fgets(input, 20, stdin);
	if (strcmp(input, "1\n") == 0 || strcasecmp(input, "yellow\n") == 0) {
	    yellow();
	} else if (strcmp(input, "2\n") == 0 || strcasecmp(input, "green\n") == 0) {
	    green();
	} else if (strcmp(input, "3\n") == 0 || strcasecmp(input, "blue\n") == 0) {
	    blue();
	} else if (strcmp(input, "4\n") == 0 || strcasecmp(input, "red\n") == 0) {
	    red();
	} else if (strcasecmp(input, "exit\n") == 0 || strcasecmp(input, "quit\n") == 0) {
            return 0;
	} else if (strcasecmp(input, "disarm\n") == 0) {
            raise(10);
	} else if (*input == '\n') {
	    show_menu = false;
            continue;
	} else {
            wire_green = 2;
	}
	printf("\x1B[100m \x1B[0m\x1B[90m PRESS ENTER TO RETURN TO MENU \x1B[0m");
	getchar();
	show_menu = true;
    }
}
