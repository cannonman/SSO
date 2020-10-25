#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

char *comm [10];
char *arg [10];

void forker(int arg, char *argv[]){
	
	int fd[2];
	char readbuffer[100];
	int pid;
	int out;
	char *path [15] = "/bin/";
       	path += argv[arg];

	switch(pid=fork()){
		case 0: //child
			out = dup(STDOUT_FILENO);
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execl (path, argv[arg], argv[arg+1], NULL);
			close(fd[1]);
			exit(0);
			break;
		case -1:
			printf("error");
			break;

		default: //parent
			sleep(1);
			close(fd[1]);
			dup2(fd[0],0);
			execl("/bib/echo", "echo", NULL);
			exit(0);
			break;	
	}
}


int main(int argc, char *argv[]){
	
	printf("%s \n", argv[0]);
	printf("%s \n", argv[1]);
	printf("%s \n", argv[2]);
		
	forker(1, argv);
	return 0;
}
