#include <unistd.h>
#include <stdio.h>

int main() {
	int wfd[2];
	int rfd[2];
	pipe(wfd);
	pipe(rfd);
	if (fork() == 0) { // Child
		dup2(wfd[0], STDIN_FILENO);
		dup2(rfd[1], STDOUT_FILENO);
		execv("./picodbd", NULL);
	} else { // Parent
		// Example requests:
		char request[1];
		request[0] = 'a';
		while ((int)request[0] < 150) {
			write(wfd[1], request, 1);
			char reply[1];
			int bytes_read = read(rfd[0], reply, 1);
			printf("'%c' -> '%c'\n", request[0], reply[0]);
			request[0] = reply[0];
		}
	}
}
