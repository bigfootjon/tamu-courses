#include <unistd.h>
#include <stdio.h>

int main() {
	int fd[2];
	pipe(fd);
	if (fork() == 0) { // Child
		dup2(fd[0], STDOUT_FILENO);
		dup2(fd[1], STDIN_FILENO);
		execv("./picodbd", NULL);
	} else { // Parent
		// Example requests:
		write(fd[1], "a\n", 2);
		char message[100];
		int bytes_read = read(fd[0], message, 100);
		printf("%s", message);
	}
}
