#include "include.h"

void red() {
    const char *alphabet = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";

    int *r = red_preflight();
    unsigned int var_4;
    for (int i = 0; i <= 18; ++i) {
        if (buffer[i] != alphabet[r[2] & 0x1F]) {
            wire_red++;
	    return;
	}
	r[2] = ((unsigned int)r[2] >> 5) | (r[1] << 27);
	r[1] = ((unsigned int)r[1] >> 5) | (r[0] << 27);
	var_4 = (unsigned int)r[0] >> 5;
	r[0] = (unsigned int)r[0] >> 5;
    }
    wire_red = 0;
}
