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
/* parent and child process creation */
void process_demo(){
	printf("Process Creation\n");
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
/*function performed by each worker thread*/
void *worker_task(void *arg){
	int id = *(int *)arg;
/*update the counter 3 times*/
	for(int i = 0;i<UPDATES;i++){
		pthread_mutex_lock(&lock);
  	/*critical section*/
		sharedCounter++;
		printf("thread %d updated counter to %d\n",id,sharedCounter);
		/*unlocking mutex to enter another thread*/
		pthread_mutex_unlock(&lock);
}

	return NULL;
}
/*three worker thread*/
void run_thread(){
	pthread_t threads[THREADS];
	int id[THREADS];
	printf("thread management and synchronization\n");
	/*initialize mutex before thread start*/
	pthread_mutex_init(&lock, NULL);
	/*worker thread*/
	 for (int i = 0; i < THREADS; i++) {
        id[i] = i + 1;

        pthread_create(
            &threads[i],
            NULL,
            worker_task,
            &id[i]
        );
    }

    /* waiting for all threads to finish via pthread_join */
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
   /*destroying mutex when thread complte*/
   pthread_mutex_destroy(&lock);
   /*display result*/
   printf("final counter = %d\n",sharedCounter);

    printf("expected counter  = %d\n",THREADS*UPDATES);
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
	run_thread();
	round_robin();
	return 0;
}
