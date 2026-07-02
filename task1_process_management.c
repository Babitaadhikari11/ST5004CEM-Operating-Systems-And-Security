/* Process creation */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/* parent and child process creation */
void process_demo(){
	printf("Process Creation");
	printf("Parent PID : %d\n",getpid());
	/* preventing duplicate output after fork */
	fflush(stdout);
	pid_t pid = fork(); //create child
	if(pid < 0){
		printf("fork failed");
		exit(1);
}
	/* child process creation*/
	if(pid == 0){
		printf("Child process created successfully.");
		printf("child PID : %d\n",getpid());
		printf("Parent PID: %d\n",getppid());
		exit(0);
}
	/* parent waits for child demonstration*/
	wait(NULL);
	printf("Parent waited for child process.\n");
}
/* main function*/
int main(){
	process_demo();
	return 0;
}
