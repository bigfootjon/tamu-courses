#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void call(char* str, int offset) {
	fprintf(stderr, "%c", *(str+offset));
	if (offset == 0) {
		fprintf(stderr, "\n");
		return;
	}
	if (!fork()) {
		call(str, offset-1);
	}
}

int main(int argc, char** argv) {
	if (argc < 2) return -1;

	char* str = argv[1];
	int offset = strlen(str);
	call(str, offset);
	wait(NULL);
}

