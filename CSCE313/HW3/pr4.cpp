// declare and initialize semaphores here
semaphore waiting_area{1};
semaphore bathroom_door{3};

#define MALE 0
#define FEMALE 1

vector<int> bathroom;

for(;;) { // forever
	// this code is for female employees. male code is similar.
	
	// here comes the code for the employee to access the bathroom.
	waiting_area.P();
	while(bathroom.size() != 0 && bathroom[0] != FEMALE) yield(); // For male, change FEMALE to MALE
	bathroom_door.P();
	bathroom.push_back(FEMALE); // for male, change FEMALE to MALE
	waiting_area.V();

	// here comes the code for the employee to leave the bathroom.
	bathroom.pop_back();
	bathroom_door.V();
}
