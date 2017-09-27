#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	if (argc < 2) return -1;

	char* str = argv[1];
	int offset = strlen(str);
	while (offset-- && !fork()) {
		fprintf(stderr, "%c", *(str+offset));
		if (offset == 0) {
			fprintf(stderr, "\n");
		}
	}
	wait(NULL);
}

