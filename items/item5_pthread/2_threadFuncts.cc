#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

void* pthread_func(void *argv);
void* pthread_func1(void *argv);
void* pthread_func2(void *argv);

pthread_t pid1, pid2;

int main(int argc, char *argv[]){

    pthread_t pid;
    pid = pthread_self();
    // when two pthread equal, return non-zero value, else return zero
    int ret = pthread_equal(pid, pthread_self());
    cout << "res: " << ret << endl;

    // pthread_create(pthread_t *pid, const pthread_attr_t *attr, (void*)(*start_routine)(void *), void *argv)
    ret = pthread_create(&pid1, NULL, pthread_func1, NULL);
    if(ret == 0){
        cout << "Init pthread success." << endl;
    }else{
        cout << "Init pthread falied." << endl;
    }
    cout << "Main Process, PID: " << getpid() << " tid: " << pthread_self() << endl;

    if(pthread_create(&pid1, NULL, pthread_func1, NULL) != 0){
        cout << "pthread 1 created failed." << endl;
        exit(0);
    }

    if(pthread_create(&pid2, NULL, pthread_func2, NULL) != 0){
        cout << "pthread 2 created failed." << endl;
        exit(1);
    }
    

    void *resVal;  // store pthread return value
    // pthread_join(pthread pid, void **thread_return)
    int retcode = pthread_join(pid, &resVal);
    cout << "pthread_func return code is: " << (int *)resVal << endl;

    retcode = pthread_join(pid1, &resVal);
    cout << "pthread_func1 return code is: " << (int *)resVal << endl;

    retcode = pthread_join(pid2, &resVal);
    cout << "pthread_func2 return code is: " << (int *)resVal << endl;

    return 0;
}

void* pthread_func(void *arg){
    cout << "This a test pthread." << endl;
    //pthread_exit(NULL);
    cout << "Pthread PID: " << getpid() << " tid: " << pthread_self() << endl;
    cout << "Parent PID: " << getppid() << endl;
    pthread_exit((void *)2);
}

void* pthread_func1(void *arg){
    cout << "This is pthread 1" << endl;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); // set this thread can be canceled by other pthread
    while(1){
        cout << "Pthread 1 is running." << endl;
        sleep(1);
    }
    pthread_exit((void *)0);
}

void* pthread_func2(void *arg){
    cout << "This is pthread 2" << endl;
    cout << "Pthread PID: " << getpid() << " tid: " << pthread_self() << endl;
    cout << "Parent PID: " << getppid() << endl;

    sleep(5);
    if(pthread_cancel(pid1) == 0){
        cout << "set pthread_cancel for pthread 1" << endl;
    }

    return (void *)2; 
}
