/*
Sample Solution-1 for Lab-1, Problem-4

run this file as: gcc FileName.c -o ExecutableName -lrt 

*/

#include <stdio.h>
#include <time.h>

// Macro definitions to ensure portablity between both sun.cs and linux.cs

#if defined(sun)
    #define CLOCKNAME CLOCK_HIGHRES
#else
    #define CLOCKNAME CLOCK_PROCESS_CPUTIME_ID
#endif

unsigned int input;

enum input_offset {
        DOS,DSBF,ER,DC,KIC,DLC,BP,CM
};

unsigned int output;

enum output_offset {
        BELL,DLA,BA
};

void set_input_bit(enum input_offset shift) {
        int temp;
        scanf("%u", &temp);
        input |= (temp & 1) << shift;
}

unsigned int get_output_bit(enum output_offset shift) {
        return (output >> shift) & 1;
}

void read_inputs_from_ip_if(){
        printf("-- INPUT --\n");
        input = 0; // reset input;
        printf("DOS  = "); set_input_bit(DOS);
        printf("DSBF = "); set_input_bit(DSBF);
        printf("ER   = "); set_input_bit(ER);
        printf("DC   = "); set_input_bit(DC);
        printf("KIC  = "); set_input_bit(KIC);
        printf("DLC  = "); set_input_bit(DLC);
        printf("BP   = "); set_input_bit(BP);
        printf("CM   = "); set_input_bit(CM);
}

void write_output_to_op_if() {
        printf("-- OUTPUT --\n");
        printf("BELL = %u\n", get_output_bit(BELL));
        printf("DLA  = %u\n", get_output_bit(DLA));
        printf("BA   = %u\n", get_output_bit(BA));
}


//The code segment which implements the decision logic
inline void control_action(){

	//Reset output
	output = 0;
	
	//Requirement 1, 2, 3
	switch (input & 0xf)
	{
		case 5:
		case 7:
		case 13:
			output =  0x1;
	}

	//Requirement 4
	switch (input & 0x31)
	{
		case 32:
		case 49:
			output = output | 0x2;
	}

	//Requirement 5
	if ((input & 0xc0) == 0xc0)
			output = output | 0x4;

}

/* ---     You should not have to modify anything below this line ---------*/

/*timespec diff from
http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
*/
struct timespec diff(struct timespec start, struct timespec end) {
	struct timespec temp;
	//the if condition handles time stamp end being smaller than than 
	//time stamp start which could lead to negative time.
	
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

int main(int argc, char *argv[]) {
	unsigned int cpu_mhz;
	unsigned long long int begin_time, end_time;
	struct timespec timeDiff,timeres;
	struct timespec time1, time2, calibrationTime;
	
	clock_gettime(CLOCKNAME, &time1);
	clock_gettime(CLOCKNAME, &time2);
	calibrationTime = diff(time1,time2); //calibration for overhead of the function calls
	clock_getres(CLOCKNAME, &timeres);  // get the clock resolution data
	
	read_inputs_from_ip_if(); // get the sensor inputs
	
	clock_gettime(CLOCKNAME, &time1); // get current time
	control_action();                 // process the sensors
	clock_gettime(CLOCKNAME, &time2);   // get current time
	
	write_output_to_op_if();    // output the values of the actuators
	
	timeDiff = diff(time1,time2); // compute the time difference
	
	printf("Timer Resolution = %u nanoseconds \n ",timeres.tv_nsec);
	printf("Calibrartion time = %u seconds and %u nanoseconds \n ", calibrationTime.tv_sec, calibrationTime.tv_nsec);
	printf("The measured code took %u seconds and ", timeDiff.tv_sec - calibrationTime.tv_sec);
	printf(" %u nano seconds to run \n", timeDiff.tv_nsec - calibrationTime.tv_nsec);
	
	return 0;
}


