#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void call(int n, int m) {
	if (n <= 1) {
		printf("%d\n", m);
		return;
	}
	if (!fork()) {
		call(n-1, m*n);
	}
}

int main(int argc, char** argv) {
	if (argc < 2) return 1;
	int n = atoi(argv[1]);
	int m = n;
	call(n-1, m);
	wait(NULL);
}
