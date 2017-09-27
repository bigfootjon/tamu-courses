#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
	if (argc < 2) return -1;
	
	char* str = argv[1];
	int offset = strlen(str) - 1;
	while (offset >= 0) {
		if (!fork()) {
			printf("%c", *(str+offset));
			if (offset == 0) {
				printf("\n");
			}
			return 0;
		}
		--offset;
	}
}

