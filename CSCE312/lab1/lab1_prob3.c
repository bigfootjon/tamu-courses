// CSCE312: Lab-1 Problem-3

/*
run this file as : gcc filename.c -o executableName
*/


#include <stdio.h>

unsigned int DOS;
unsigned int DSBF;
unsigned int ER;
unsigned int DC;
unsigned int KIC;
unsigned int DLC;
unsigned int BP;
unsigned int CM;

unsigned int BELL;
unsigned int DLA;
unsigned int BA;


void read_inputs_from_ip_if(){
        printf("-- INPUT --\n");
	printf("DOS  = "); scanf("%u", &DOS);
	printf("DSBF = "); scanf("%u", &DSBF);
	printf("ER   = "); scanf("%u", &ER);
	printf("DC   = "); scanf("%u", &DC);
	printf("KIC  = "); scanf("%u", &KIC);
	printf("DLC  = "); scanf("%u", &DLC);
	printf("BP   = "); scanf("%u", &BP);
	printf("CM   = "); scanf("%u", &CM);
}

void write_output_to_op_if() {
        printf("-- OUTPUT --\n");
	printf("BELL = %u\n", BELL);
	printf("DLA  = %u\n", DLA);
	printf("BA   = %u\n", BA);
}


//The code segment which implements the decision logic
void control_action(){
	// combined requirements 1,2,3:
	if (ER && (!DSBF || !DC)) BELL = 1; else BELL = 0;
	// requirement 4
	if ((DOS && DLC) || (!DOS && !KIC && DLC)) DLA = 1; else DLA = 0;
	// requirement 5
	if (CM && BP) BA = 1; else BA = 0;
}

/* --- You should not have to modify anything below this line ---------*/

int main(int argc, char *argv[])
{
	
	/*The main control loop which keeps the system alive and responsive for ever, 
	until the system is powered off */
	for (; ; )
	{
		read_inputs_from_ip_if();
		control_action();
		write_output_to_op_if();

	}
	
	return 0;
}
