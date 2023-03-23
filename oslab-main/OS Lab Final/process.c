//.c file, run in linux
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

//.c file, run in linux
int main(int argc, char *argv[]){
	pid_t pid1= fork();
	pid_t pid2 = fork();

	if(pid1<0){
	        printf("fork1 has failed\n");
		return 1;
	}
	else if(pid1==0){
		if(pid2<0){
			printf("fork2 has failed\n");
			exit(-1);
		}
		else if(pid2==0){
			printf("I am child process 3 created by forking first child of main process. My PID is %d, parent PID is %d\n",(int) getpid(),(int) getppid());
		        sleep(5);
			printf("process 3 has finished sleeping.\n(Process 3 exiting)\n");
			exit(3);
			
		}
		else {
			printf("I am child process 2 created by first fork of main process. My PID is %d, parent PID is %d\n",(int) getpid(),(int) getppid());
			//waiting for child process 3
			wait(NULL);
			printf("process 2 has finished waiting for child process 3.\n(Process 2 exiting)\n");
		        exit(2);	
		}
	}
	else {
		if(pid2<0){
			printf("fork2 has failed\n");
			exit(-1);
		}
		else if(pid2==0){
			printf("I am child process 4 created by the second fork of main process. My PID is %d, parent PID is %d\n",(int) getpid(),(int) getppid());
			sleep(7);
			printf("process 4 has finished sleeping.\n(Process 4 is exiting)\n");
			exit(4);
		}
		else {
			printf("I am the main parent process.My process id is %d\n",(int) getpid());
			//waiting for process 2 and 4 to finish
			wait(NULL);
			wait(NULL);
			printf("main parent process has finished waiting for its child process 2 and 4.\n(Main parent process is exiting)\n");
			exit(1);
		}
	
	}
	return 0;


}
