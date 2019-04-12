#include <stdio.h>
#include "include.h"

void yellow() {
    yellow_preflight();
    if (*buffer == '8') {
        if (*(buffer+1) == '4') {
            if (*(buffer+2) == '3') {
                if (*(buffer+3) == '7') {
                    if (*(buffer+4) == '1') {
                        if (*(buffer+5) == '0') {
                            if (*(buffer+6) == '6') {
                                if (*(buffer+7) == '5') {
                                    wire_yellow = 0;
				    puts("\x1B[43m \x1B[0m\x1B[33m UNLOCK PASSWORD 1 ACCEPTED, LOCK DISENGAGED\x1B[0m");
				    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    wire_yellow <<= 10;
}
