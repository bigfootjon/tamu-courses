#include <stdbool.h>

extern char buffer[32];
extern bool wire_yellow;
extern bool wire_green;
extern bool wire_blue;
extern bool wire_red;

void gettimeleft(void);
void disarm_handler(int);
void menu(void);
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
