#include <stdio.h>
#include <unistd.h>
#include "include.h"

typedef struct n {
    unsigned int left;
    unsigned int value;
    unsigned int right;
} node_t;

node_t graph[] = {
    {.left =  5, .value = 0x47BBFA96, .right =  2},
    {.left = 15, .value = 0x50171A6E, .right =  7},
    {.left = 10, .value = 0x23DAF3F1, .right =  6},
    {.left =  5, .value = 0x634284D3, .right =  8},
    {.left = 12, .value = 0x344C4EB1, .right = 13},
    {.left =  9, .value = 0x0C4079EF, .right = 15},
    {.left =  2, .value = 0x425EBD95, .right =  3},
    {.left =  9, .value = 0x07ACE749, .right =  6},
    {.left = 11, .value = 0x237A3A88, .right =  3},
    {.left = 12, .value = 0x4B846CB6, .right =  3},
    {.left = 15, .value = 0x1FBA9A98, .right =  8},
    {.left =  5, .value = 0x3A4AD3FF, .right =  8},
    {.left =  3, .value = 0x16848C16, .right =  2},
    {.left =  4, .value = 0x499EE4CE, .right =  7},
    {.left =  8, .value = 0x261AF8FB, .right =  3},
    {.left =  9, .value = 0x770EA82A, .right = 13},
};

const int solution = 1078415764; // from IDA

void blue() {
    blue_preflight();
    unsigned int node_value = 0x47bbfa96;
    node_t cur = graph[0];
    for (int i = 0; i <= 14; ++i) {
        char c = buffer[i];
        bool should_break = false;
        switch (c) {
            case 'L':
                cur = graph[cur.left];
                break;
            case 'R':
                cur = graph[cur.right];
                break;
            case '\n':
                should_break = true;
                break;
            default:
                puts("boom");
                should_break = true;
                break;
        }
        if (should_break) {
             break;
        }
        node_value = cur.value ^ node_value;
    }
    printf("\x1B[46m \x1B[0m\x1B[36m PROGRAMMING GATE ARRAY... ");
    sleep(1);
    puts("SUCCEEDED\x1B[0m");
    usleep(500000);
    if (node_value == solution) {
        puts("\x1B[46m \x1B[0m\x1B[36m VOLTAGE REROUTED FROM REMOTE DETONATION RECEIVER \x1B[0m");
        --wire_blue;
    } else {
        wire_blue += 1;
    }
}
