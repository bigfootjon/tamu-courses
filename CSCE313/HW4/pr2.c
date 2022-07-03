#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main() {
	int request_fd[2];
	int reply_fd[2];
	pipe(request_fd);
	pipe(reply_fd);
	if (fork() == 0) { // Child
		close(reply_fd[READ]);
		dup2(request_fd[READ], STDIN_FILENO);
		dup2(reply_fd[WRITE], STDOUT_FILENO);
		execv("./picodbd", NULL);
	} else { // Parent
		close(request_fd[READ]);

		// Example request:
		char request[1];
		request[0] = 'a';
		write(request_fd[WRITE], request, 1);
		char reply[1];
		int bytes_read = read(reply_fd[READ], reply, 1);
		
		wait(NULL);
	}
}
