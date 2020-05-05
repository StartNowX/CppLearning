#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;


void* simpleThread(void*){
    cout << "This is a thread" << endl;
}

void init_thread(){
    int ret = 0;
    pthread_t simpleID;
    ret = pthread_create(&simpleID, NULL, simpleThread, NULL);
    if(ret != 0){
        cout << "create simple thread error." << endl;
        exit(EXIT_FAILURE);
    }else{
	cout << "init thread success" << endl;
    }
    pthread_join(simpleID, NULL);
}

int main(int argc, char *argv[]){

    std::cout << "Init thread" << endl;
    init_thread();

    //sleep(1);
    return 0;
}
