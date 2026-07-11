/*Task 1 : Bank Server Process Creation*/
/* Process creation */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#define THREADS 3
#define UPDATES 5
#define PROC 4
#define QUANTUM 2
/*shared variable access by all threads*/
int sharedCounter =0;
/*mutex to protect*/
pthread_mutex_t lock;
/*structure used to pass worker details to each thread */
struct Worker {
int id;
char role[30];
};
/* parent and child process creation,i.e. bank server creates a customer session process */
void process_demo(){
	printf("Bank Server Process Creation \n");
	printf("Main Bank Server PID : %d\n",getpid());
	/* preventing duplicate output after fork */
	fflush(stdout);
	pid_t pid = fork(); //create child
	if(pid < 0){
		printf("Customer session process creation failed.\n");
		exit(1);
}
	/* child process creation*/
	if(pid == 0){
		printf("Customer session process created successfully.\n");
		printf("Customer Session PID : %d\n",getpid());
		printf("Bank Server  PID: %d\n",getppid());
		exit(0);
}
	/* parent waits for child demonstration*/
	wait(NULL);
	printf("Bank server waited for customer session to finish.\n");
}
/*function performed by each transaction worker*/
void *transaction_worker(void *arg){
struct Worker *worker=(struct Worker *)arg;
printf("Worker %d (%s) is processing a transaction.\n",worker->id,worker->role);
return NULL;
}
/*create and manages 3 worker thread*/
void run_threads(){
pthread_t workers[THREADS];
struct Worker workerData[THREADS] ={
{1, "Deposit Handler"},
{2, "Payment Handler"},
{3, "Transfer Handler"}
};
printf("Bank Transaction Worker Thread \n");

/*update the counter 3 times*/
	for(int i = 0;i<THREADS;i++){
		pthread_create(&workers[i],NULL, transaction_worker,&workerData[i]);

}
for(int i = 0; i < THREADS; i++) {
pthread_join(workers[i], NULL);
}
printf("All transaction workers completed.\n");
}

/*round robin scheduling*/
void round_robin(){
/*burst time of four process i.e. p1,p2,p3,p4*/
int burst[PROC]={5,8,6,3};
/*remained burst time*/
int remaining[PROC];
int time =0;
int completed=0;
/*copying burst time into remaining times*/
for (int i=0;i<PROC; i++){
remaining[i]=burst[i];
}
printf("\n Round Robin Scheduling Algorithm \n");
printf("Time Quantum = %d\n" ,QUANTUM);
/*THE proccess continues untill all process finishes*/
while(completed<PROC){
for(int i=0;i<PROC;i++){
if(remaining[i]>0){
/*run for quantum or remained time for the process*/
int run;
if(remaining[i] > QUANTUM){
run = QUANTUM;
}else{
run= remaining[i];
}
printf("Time %d - %d: P%d running\n",time,time+run,i+1);
time=time+run;
remaining[i]=remaining[i]-run;
/*check  for process finished or not */
if(remaining[i]==0){
printf("P%d completed at time %d\n",i+1,time);
completed++;
}
}
}
}
printf("All processes completed.\n");
}

/* main function*/
int main(){
	process_demo();
	run_threads();
	round_robin();
	return 0;
}
