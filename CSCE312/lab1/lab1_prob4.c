// CSCE312: Lab-1 Problem-3

/*
run this file as : gcc filename.c -o executableName
*/


#include <stdio.h>

int sensor_inputs;

enum input_offset {
	DOS,DSBF,ER,DC,KIC,DLC,BP,CM
};

int actuator_outputs;

enum output_offset {
	BELL,DLA,BA
};

enum bitmask {
	req123_filter =  14,
	req123_check  =   4,
	req4p1_filter =  33,
	req4p1_check  =  33,
	req4p2_filter =  49,
	req4p2_check  =  32,
	req5_filter   = 192,
	req5_check    = 102,
}

void set_input_bit(enum input_offset shift) {
	int temp;
	scanf("%u", &temp);
	sensor_inputs |= (temp & 1) << shift;
}

void set_output_bit(enum output_offset shift, unsigned int value) {
	actuator_outputs |= (value & 1) << shift;
}

unsigned int get_output_bit(enum output_offset shift) {
	return (actuator_outputs >> shift) & 1;
}

void read_inputs_from_ip_if(){
        printf("-- INPUT --\n");
	sensor_inputs = 0; // reset input;
	printf("DOS  = "); set_input_bit(DOS);
	printf("DSBF = "); set_input_bit(DSBF);
	printf("ER   = "); set_input_bit(ER);
	printf("DC   = "); set_input_bit(DC);
	printf("KIC  = "); set_input_bit(KIC);
	printf("DLC  = "); set_input_bit(DLC);
	printf("BP   = "); set_input_bit(BP);
	printf("CM   = "); set_input_bit(CM);
	printf("ALL:%u\n", sensor_inputs);
}

void write_output_to_op_if() {
        printf("-- OUTPUT --\n");
	printf("ALL:%u\n", actuator_outputs);
	printf("BELL = %u\n", get_output_bit(BELL));
	printf("DLA  = %u\n", get_output_bit(DLA));
	printf("BA   = %u\n", get_output_bit(BA));
}


//The code segment which implements the decision logic
void control_action() {
	actuator_outputs = 0;
	// Else branches are implied because output is recet every cycle;
	// combined requirements 1,2,3:
	if ((sensor_inputs & req123_filter) == req123_check) set_output_bit(BELL, 1); // 14 means that bits representing 2,4,8 are set
	// requirement 4
	if ((sensor_inputs & req4p1_filter) == req4p1_check) set_output_bit(DLA, 1); // 33 means bits representing 1,32 are set
	if ((sensor_inputs & req4p2_filter) == req4p2_check) set_output_bit(DLA, 1); // 49 means bits representing 1,16,32 are set
	// requirement 5
	if ((sensor_inputs & req5_filter) == req5_check) set_output_bit(BA, 1); // 192 means bits representing 64,128 are set
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
