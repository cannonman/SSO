#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

char string1[] = "info from child aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
char string2[] = "info from parent\n";

int main(){
	int a = 64;
	int b = 65;
	int c = 66;
	int pid;
	printf("main process: %d \n",getpid());
	
	int fd[2], nbytes;
	pid_t childpid;
	char readbuffer[1020];

	pipe(fd);

	switch (pid=fork()){
		case 0: // child
			printf("child process %d \n", getpid());
			sleep(5);
			printf ("a in child %d \n", a);

			close(fd[0]);
			write(fd[1], string1,(strlen(string1)+1));
			sleep(5);
			break;

		case -1: //error
			printf("error");
			break;

		default: //parent
			printf("pid: %d \n", pid);
			a++;
			printf("a in parent: %d \n", a);
			printf("parent process, %d \n", getppid());
			sleep(6);
			close(fd[1]);
			nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
			printf("received message:\n %s \n", readbuffer);
			printf("size: %d \n", strlen(readbuffer));
			wait(NULL);
			printf("main process: %d \n", getpid());
			exit(0);
	}
	exit(0);
}
