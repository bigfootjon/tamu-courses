/*
Instructions -

To run this program - first compile to crete an executable, 
then run the executable code.

Type the following in the Linux console/shell to compile and make an executable using the gcc complier-

gcc lab1_prob2.c -o lab1_prob2

To run the executable named "lab1_prob2", type the following-

./lab1_prob2
*/


#include <stdio.h> //For input/output
#include <sys/time.h> //For gettimeofday() function

int main()
{
	FILE *my_file_pointer;
	if ( (my_file_pointer = fopen("lab1_prob2_out.txt", "w")) == NULL)
	{
		printf("Error opening the file, so exiting\n");
		exit(1);
	}

	fprintf(my_file_pointer, "The sizes of different data type for this machine and compiler are -\n");
	fprintf(my_file_pointer, "unsigned int data type is %d bytes or %d bits long\n",sizeof(unsigned int), sizeof(unsigned int)*8 ); 
	fprintf(my_file_pointer, "double data type is %d bytes or %d bits long\n",sizeof(double), sizeof(double)*8 );
	fprintf(my_file_pointer, "long data type is %d bytes or %d bits long\n",sizeof(long), sizeof(long)*8 );
	fprintf(my_file_pointer, "long long data type is %d bytes or %d bits long\n",sizeof(long long), sizeof(long long)*8 );
	fprintf(my_file_pointer, "char data type is %d bytes or %d bits long\n",sizeof(char), sizeof(char)*8 );
	fprintf(my_file_pointer, "float data type is %d bytes or %d bits long\n",sizeof(float), sizeof(float)*8 );
	fprintf(my_file_pointer, "timeval struct data type is %d bytes or %d bits long\n",sizeof(struct timeval), sizeof(struct timeval)*8 );

	fclose(my_file_pointer); //To close the output file, mandatory to actually get an output !

	return 0;
}
