/*Task 1 : Bank Server Process Creation*/
/* Process creation */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#define THREADS 3
#define TRANSACTIONS 5
#define DEPOSIT_AMOUNT 100
#define PROC 4
#define QUANTUM 2

/*structure used to pass worker details to each thread */
struct Worker {
int id;
char role[30];
};
/*shared bank account balance */
int accountBalance = 1000;
/*MUTEXx protect the shared account balance */
pthread_mutex_t accountLock;
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
/* Each worker updates the shared account balance safely */
void *transaction_worker(void *arg) {
struct Worker *worker = (struct Worker *)arg;
for (int i = 0; i < TRANSACTIONS; i++) {
/* lock before updating shared balance */
pthread_mutex_lock(&accountLock);
int oldBalance = accountBalance;
accountBalance = accountBalance+DEPOSIT_AMOUNT;
printf("Worker %d (%s): Rs. %d -> Rs. %d\n",worker->id,worker->role,oldBalance,accountBalance);
/* unlock immediately after update */
pthread_mutex_unlock(&accountLock);
}
return NULL;
}
/*creates and manages 3 transaction workers */
void run_threads() {
pthread_t workers[THREADS];
struct Worker workerData[THREADS] = {
{1, "Deposit Handler"},
{2, "Payment Handler"},
{3, "Transfer Handler"}
};
printf("\n Bank Transaction Worker Threads \n");
printf("Initial Balance = Rs. %d\n", accountBalance);
/* initialize mutex */
pthread_mutex_init(&accountLock, NULL);
/* create 3 worker threads */
for (int i = 0; i < THREADS; i++) {
        pthread_create(&workers[i],NULL,transaction_worker,&workerData[i]);
}
/* wait for all threads to finish */
for(int i = 0; i < THREADS; i++) {
pthread_join(workers[i], NULL);
}
/* destroy mutex */
pthread_mutex_destroy(&accountLock);
printf("Final Balance = Rs. %d\n", accountBalance);
printf("Expected Balance = Rs. %d\n",1000+(THREADS*TRANSACTIONS*DEPOSIT_AMOUNT));
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
