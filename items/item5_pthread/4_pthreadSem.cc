/**
 * Usage of semaphore. Operation P, sem - 1, Operation V, sem + 1
*/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

#define THREAD_NUM 3
#define REPEAT_TIMES 5
#define DELAY 4

sem_t sem[THREAD_NUM];

void *thread_func(void *arg);

int main(int argc, char *argv[]){

    pthread_t thread[THREAD_NUM];
    void *tret;

    srand((int)time(0));


    for(int no = 0; no < THREAD_NUM - 1; no++){
        // sem_init(sem_t *sem, int pshared, unsigned int value)
        sem_init(&sem[no], 0, 0);
    }

    // last initialized as 1
    sem_init(&sem[THREAD_NUM - 1], 0, 1);

    for(int no = 0; no < THREAD_NUM; no++){
        if(pthread_create(&thread[no], NULL, thread_func, &no) != 0){
	    cout << "Create thread[" << no << "] error." << endl;
	    exit(1);
 	}else{
	    cout << "Create thread[" << no << "] success." << endl;
	}
    }

    for(int no = 0; no < THREAD_NUM; no++){
	if(pthread_join(thread[no], &tret) != 0){
	    cout << "Join thread[" << no << "] error." << endl;
	    exit(1);
 	}else{
	    cout << "Join thread[" << no << "] success." << endl;
	}
	
    }

    // destroy all semaphore
    for(int no = 0; no < THREAD_NUM; no++){
	sem_destroy(&sem[no]);
    }

    return 0;
}

void *thread_func(void *arg){
    int threadNum = *(int *)arg;
    
    // P
    sem_wait(&sem[threadNum]);

    cout << "Thread[" << threadNum << "] is starting." << endl;

    for(int count = 0; count < REPEAT_TIMES; count++){
        int delay_time = (int)(DELAY * (rand() / (double)RAND_MAX)) + 1;
        sleep(delay_time);
	cout << "Thread: " << threadNum << ", job: " << count << " delay_time: " << delay_time << endl;
    }

    cout << "Thread[" << threadNum << "] is exiting." << endl;

    // V
    sem_post(&sem[(threadNum + THREAD_NUM - 1) % THREAD_NUM]);

    pthread_exit(NULL);
}
