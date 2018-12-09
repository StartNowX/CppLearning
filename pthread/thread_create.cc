#include <iostream>

#include <pthread.h>

using namespace std;


void *process_face(void *){
    for(int i = 0; i < 4; i++){
	std::cout << "Face test " << i << " self: " << pthread_self() << endl;
    }

}

void *process_lane(void *){
    for(int i = 0; i < 3; ++i){
        std::cout << "Lane test " << i << " self: " << pthread_self() << endl;
    }
}

void *exit_lane(void *){
    cout << "exit lane thread." << endl;
    pthread_exit((void *)6);
}

int main(int argc, char *argv[]){
    pthread_t face_id, lane_id;

    int ret = 0;
    ret = pthread_create(&face_id, NULL, process_face, NULL);
    if(0 != ret){
        std::cout << "Face thread create error." << std::endl;
    }

    std::cout << "Face sucess -- " << ret << std::endl;
    
    ret = pthread_create(&lane_id, NULL, process_lane, NULL);
    if(0 != ret){
        std::cout << "Lane thread create error." << std::endl;
    }

    std::cout << "Face sucess -- " << ret << std::endl;
    
    pthread_t exit_id;
    void* extCode;
    ret = pthread_create(&exit_id, NULL, exit_lane, NULL);
    cout << "Exit lane sucess .. " << ret << endl;
    pthread_join(exit_id, &extCode);
    cout << "Exit lane code is " << (int)(exit_id) << endl;

    // main thread waits for face thread finish
    pthread_join(face_id, NULL);
    // main thread waits for lane thread finish
    pthread_join(lane_id, NULL);

    return 0;
}
