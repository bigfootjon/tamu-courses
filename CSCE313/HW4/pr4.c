#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

#define BUF_SIZE 1024

void do_dir(char * dirname);
void count_process();
void list_process(char * dirname);

int fd[2];

int main(int argc, char ** argv) {
	pipe(fd);
	if (argc != 2) {
		printf("Please pass a directory as an agument\n");
		return 1;
	}
	if (fork() == 0) {
		count_process();
	} else {
		char *dirname = argv[1];
		list_process(dirname);
	}
	return 0;
}

void do_dir(char *dirname) {
	DIR* dir = opendir(dirname);
	struct dirent * direntp;

	while ((direntp = readdir(dir)) != NULL) {
		char * fname = direntp->d_name;
		if (strcmp(fname, ".") == 0 || strcmp(fname, "..") == 0) {
			continue;
		}
		char path[BUF_SIZE];
		snprintf(path, sizeof(path), "%s/%s", dirname, fname);
		write(fd[WRITE], path, sizeof(path));
		printf("%s\n", path);
		DIR * subdir = opendir(path);
		if (subdir != NULL) {
			do_dir(path);
		}
	}
	while (closedir(dir) == -1);
}

void list_process(char * dirname) {
	DIR * dirp;

	dirp = opendir(dirname);
	
	if (dirp == NULL) { 
		perror("Failed to open directory");
		return;
	}
	while (closedir(dirp) == -1);
	
	do_dir(dirname);

	close(fd[WRITE]);
	wait(NULL);
}

void count_process() {
	close(fd[WRITE]);
	int count = 0;
	char buffer[BUF_SIZE];
	while (read(fd[READ], buffer, sizeof(buffer))) {
		++count;
	}
	printf("----- TOTAL ENTRIES: %d -----\n", count);
}
