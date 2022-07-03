#include <stdio.h>
#include "include.h"

void disarm_handler(int i) {
    if (wire_blue == 0 && wire_yellow == 0 && wire_green == 0 && wire_red == 0) {
        libc_start_main_done = 1;
    } else {
        kaboom();
    }
}
