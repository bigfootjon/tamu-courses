#include <stdbool.h>

extern char buffer[32];
extern bool yellow_wire;
extern bool green_wire;
extern bool blue_wire;
extern bool red_wire;

void kaboom(void);

void yellow_preflight(void);
void yellow(void);

void green_preflight(char *);
void green(void);

void blue_preflight(void);
void blue(void);

void red_preflight(void);
void red(void);
void postred(void);
