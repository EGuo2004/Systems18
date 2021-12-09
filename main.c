#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
	int parent[2];
	int child[2];
	pipe(parent);//from parent
	pipe(child);//from child

	char line[100];
    int f = fork();
	
	if(f==0) {
		//parent
		close(parent[READ]);
		close(child[WRITE]);
		while(1) {
			printf("What do you want?\n");
			fgets(line, sizeof(line), stdin);
			write(parent[WRITE], line, sizeof(line));
			read(child[READ], line, sizeof(line));
			printf("Here:%s\n", line);
		}
	} else {
		close(parent[WRITE]);
		close(child[READ]);
		while(1) {
			read(parent[READ], line, sizeof(line));
			int counter;
			for(counter = 0; counter < strlen(line); counter++) {
				line[counter] = toupper(line[counter]);
			}
			write(child[WRITE], line, sizeof(line));
		}
	}
	return 0;
}
