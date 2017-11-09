#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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
		return 0;
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
		char path[1000];
		snprintf(path, sizeof(path), "%s/%s", dirname, fname);
		printf("L %s\n", path);
		write(fd[1], path, strlen(path)+1);
		DIR * subdir = opendir(path);
		if (subdir != NULL) {
			do_dir(path);
		}
	}
	while (closedir(dir) == -1);
}

void list_process(char * dirname) {
	close(fd[0]);

	DIR * dirp;

	dirp = opendir(dirname);
	
	if (dirp == NULL) { 
		perror("Failed to open directory");
		return;
	}
	while (closedir(dirp) == -1);
	
	do_dir(dirname);

	close(fd[1]);
	wait(NULL);
}

void count_process() {
	close(fd[1]);
	int count = 0;
	char buffer[100];
	while (read(fd[0], buffer, sizeof(buffer))) {
		printf("C %s\n", buffer);
		++count;
	}
	printf("----- TOTAL ENTRIES: %d -----\n", count);
}
