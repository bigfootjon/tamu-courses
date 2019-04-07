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
                                    wire_yellow = false;
				    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    wire_yellow = true;
}
