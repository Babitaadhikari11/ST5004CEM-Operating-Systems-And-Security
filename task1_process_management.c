/* Process creation */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#define THREADS 3
#define UPDATES 5
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

/* main function*/
int main(){
	process_demo();
	run_thread();
	return 0;
}
