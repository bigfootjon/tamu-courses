#include <stdio.h>
#include "include.h"

typedef struct n {
    n *left;
    void *value;
    n *right;
} node_t;

node_t graph;

void blue() {
    blue_preflight();
    int result;
    int v1;
    int v2;
    void *node_value;
    node_t *cur = graph;
    for (int i = 0; i <= 14; ++i) {

    }
    printf("\x1B[46m \x1B[0m\x1B[36m PROGRAMMING GATE ARRAY... ");
    fflush(stdout);
    // TODO
}
