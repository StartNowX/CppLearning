#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define THREADS_NUM 3
#define REPEATED_TIME 5
#define DELAY 4

pthread_mutex_t mutex;

void* third_func(void *arg);

int main(int argc, char* argv[]){
    pthread_t thread[THREADS_NUM];
    void *resVal;

    srand((int)time(0));

    pthread_mutex_init(&mutex, NULL);

    for(int no = 0; no < THREADS_NUM; no++){
        if(pthread_create(&thread[no], NULL, third_func, &no) != 0){
	    cout << "create thread [" << no << "] failed." << endl;
	    exit(1);
 	}else{
	    cout << "create thread [" << no << "] success." << endl;
	}
    }

    for(int no = 0; no < THREADS_NUM; no++){
        if(pthread_join(thread[no], &resVal) != 0){
            cout << "pthread join [" << no << "] error." << endl;
            exit(1);
        }else{
            cout << "pthread join [" << no << "] success." << endl;
        }
    }
    
    pthread_mutex_destroy(&mutex);
    return 0;
}

void* third_func(void *arg){
    int third_num = *(int *)arg;

    // lock
    if(pthread_mutex_lock(&mutex) != 0){
        cout << "Thread " << third_num << " lock faild." << endl;
        pthread_exit(NULL);
    }

    cout << "Thread " << third_num << " starting." << endl;
    for(int count = 0; count < REPEATED_TIME; count++){
	int delay_time = (DELAY * (rand() / (double)RAND_MAX)) + 1;
        sleep(delay_time);
        cout << "Thread " << third_num << " job: " << count << " sleep time: " << delay_time << endl;
    }

    cout << "Thread " << third_num << " is exiting." << endl;

    // unclock
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}
