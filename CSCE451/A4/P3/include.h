extern char buffer[32];
extern char *display[];
extern int wire_yellow;
extern int wire_green;
extern int wire_blue;
extern int wire_red;
extern int libc_start_main_done;

void gettimeleft(void);
void disarm_handler(int);
void *libc_start_main(void *);
void menu(void);
void kaboom(void);

void yellow_preflight(void);
void yellow(void);

void green_preflight(char *);
void green(void);

void blue_preflight(void);
void blue(void);

int *red_preflight(void);
void red(void);
void postred(void);
