/* task 1: hospital emergency process and thread management */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define THREADS 3
#define UPDATES 5
#define PROC 4
#define QUANTUM 2

int sharedCounter = 0;
pthread_mutex_t lock;

/* demonstrates process creation using fork */
void show_process_creation(void) {
        pid_t pid;

        printf("\n process creation\n");
        printf("main hospital server pid: %d\n", getpid());

        pid = fork();

        if (pid < 0) {
                printf("fork failed.\n");
                exit(1);
        }

        if (pid == 0) {
                printf("child process created successfully.\n");
                printf("emergency patient session pid: %d\n", getpid());
                printf("parent hospital server pid: %d\n", getppid());
                exit(0);
        } else {
                wait(NULL);
                printf("hospital server waited for patient session.\n");
        }
}

/* task performed by each hospital worker thread */
void *worker_task(void *arg) {
        int id = *(int *)arg;
        int i;

        for (i = 0; i < UPDATES; i++) {
                pthread_mutex_lock(&lock);

                sharedCounter++;
                printf("worker thread %d updated emergency counter to %d\n",
                       id, sharedCounter);

                pthread_mutex_unlock(&lock);
        }

        return NULL;
}

/* demonstrates thread creation and mutex synchronization */
void show_thread_management(void) {
        pthread_t threads[THREADS];
        int ids[THREADS];
        int i;

        printf("\n thread management and synchronization \n");

        pthread_mutex_init(&lock, NULL);

        for (i = 0; i < THREADS; i++) {
                ids[i] = i + 1;
                pthread_create(&threads[i], NULL, worker_task, &ids[i]);
        }

        for (i = 0; i < THREADS; i++) {
                pthread_join(threads[i], NULL);
        }

        pthread_mutex_destroy(&lock);

        printf("final emergency counter = %d\n", sharedCounter);
        printf("expected counter = %d\n", THREADS * UPDATES);
}

/* simulates round robin scheduling */
void round_robin(void) {
        int burst[PROC] = {5, 8, 6, 3};
        int remaining[PROC];
        int time = 0;
        int completed = 0;
        int i;
        int run;

        for (i = 0; i < PROC; i++) {
                remaining[i] = burst[i];
        }

        printf("\nround robin scheduling\n");
        printf("time quantum = %d\n", QUANTUM);

        while (completed < PROC) {
                for (i = 0; i < PROC; i++) {
                        if (remaining[i] > 0) {
                                if (remaining[i] > QUANTUM) {
                                        run = QUANTUM;
                                } else {
                                        run = remaining[i];
                                }

                                printf("time %d - %d: patient task P%d running\n",
                                       time, time + run, i + 1);

                                time = time + run;
                                remaining[i] = remaining[i] - run;

                                if (remaining[i] == 0) {
                                        printf("patient task P%d completed at time %d\n",
                                               i + 1, time);
                                        completed++;
                                }
                        }
                }
        }

        printf("all patient tasks completed.\n");
}

/* explains deadlock prevention */
void deadlock_prevention(void) {
        printf("\n deadlock prevention \n");
        printf("only one mutex is used in this program.\n");
        printf("the mutex is locked only during counter update.\n");
        printf("the mutex is unlocked immediately after update.\n");
        printf("this prevents circular wait and reduces deadlock risk.\n");
}

int main() {
        printf("hospital emergency operating system simulation\n");

        show_process_creation();
        show_thread_management();
        round_robin();
        deadlock_prevention();

        return 0;
}
