#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

pthread_rwlock_t my_rwlock;
int resource_id = 0;

void *read_thread(void *args) {
    while (true) {
        pthread_rwlock_rdlock(&my_rwlock);
        std::cout << "thread read resource id is " << resource_id << " " << pthread_self() << std::endl;

        pthread_rwlock_unlock(&my_rwlock);
        sleep(2);
    }
    return NULL;
}

void *write_thread(void *args) { 
    while(true){
        pthread_rwlock_wrlock(&my_rwlock);
        std::cout << "thread write resource id is " << resource_id << " " << pthread_self() << std::endl;
        resource_id++;
        pthread_rwlock_unlock(&my_rwlock);

        sleep(1);
    }
    return NULL; }

int main(int argc, char *argv[]) {
    pthread_rwlockattr_t my_rwlockattr;
    pthread_rwlockattr_setkind_np(&my_rwlockattr, PTHREAD_RWLOCK_PREFER_READER_NP);
    pthread_rwlock_init(&my_rwlock, &my_rwlockattr);
    
    const int read_num = 2;
    pthread_t reads[read_num];
    for(int i = 0; i < read_num; ++i){
        pthread_create(&reads[i], NULL, read_thread, NULL);
        // pthread_join(reads[i], NULL);
    }
    
    const int writer_num = 3;
    pthread_t writers[writer_num];
    for(int i = 0; i < writer_num; ++i){
        pthread_create(&writers[i], NULL, write_thread, NULL);
        // pthread_join(writers[i], NULL);
    }

    for(int i = 0; i < writer_num; ++i){
        pthread_join(writers[i], NULL);
    }
    for(int i = 0; i < read_num; ++i){
        pthread_join(reads[i], NULL);
    }

    pthread_rwlockattr_destroy(&my_rwlockattr);
    pthread_rwlock_destroy(&my_rwlock);

    return 0;
}