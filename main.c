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

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
	int fds[2];
 	pipe( fds );
  	char line[100];
	int f = fork();
	if(f) {
        close( fds[READ] ); 
        write( fds[WRITE], "hello!", 7);
	} else {
	    close(fds[WRITE]);
	    read(fds[WRITE], line, sizeof(line));
	    char* line2;
	    strcpy(line2, line);
	}
}
