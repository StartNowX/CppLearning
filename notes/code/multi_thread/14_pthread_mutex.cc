#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <iostream>

// mutex的PTHREAD_MUTEX_INITIALIZER属性
void PthreadInit1(void) {
    // // way 1
    // pthread_mutex_t p_mutex = PTHREAD_MUTEX_INITIALIZER;

    // // way 2
    // pthread_mutex_t p_mutex;
    // pthread_mutex_init(&p_mutex, NULL); // default PTHREAD_MUTEX_INITIALIZER

    // way 3
    pthread_mutex_t p_mutex;
    pthread_mutexattr_t p_mutex_attr;
    pthread_mutexattr_init(&p_mutex_attr);
    pthread_mutexattr_settype(&p_mutex_attr, PTHREAD_MUTEX_NORMAL);
    pthread_mutex_init(&p_mutex, &p_mutex_attr);

    int ret = 0;
    std::cout << "thread id is " << pthread_self() << std::endl;
    // ret = pthread_mutex_lock(&p_mutex);

    // ret = pthread_mutex_destroy(&p_mutex);

    // lock会阻塞在此, trylock会返回错误码
    ret = pthread_mutex_trylock(&p_mutex);
    if (0 != ret) {
        if (EBUSY == errno) {
            std::cout << "thread is busy..." << std::endl;
        }
        std::cout << "lock error, ret = " << ret << std::endl;
    }

    ret = pthread_mutex_unlock(&p_mutex);
    ret = pthread_mutex_destroy(&p_mutex);
    if (0 != ret) {
        std::cout << "destroy failed." << std::endl;
    }
    ret = pthread_mutexattr_destroy(&p_mutex_attr);
    if (0 != ret) {
        std::cout << "destroy pthread attr failed." << std::endl;
    }
}

pthread_mutex_t my_mutex;
int resource_no = 0;
void* PtheadLockType2(void* args) {
    pthread_t pid = pthread_self();
    int pid_sys = syscall(SYS_gettid);
    std::cout << "Thread start, thread id is " << pid << " "<< pid_sys << std::endl;

    while (true) {
        pthread_mutex_lock(&my_mutex);
        std::cout << "Mutex lock, resource number is " << resource_no++ << ", thread id is " << pid << " "<< pid_sys <<std::endl;

        pthread_mutex_unlock(&my_mutex);
        std::cout << "Mutex unlock, resource number is " << resource_no << ", thread id is " << pid << " "<< pid_sys << std::endl;

        sleep(1);
    }
    return NULL;
}

void PthreadInit2(void) {
    pthread_mutexattr_t my_attr;
    pthread_mutexattr_init(&my_attr);

    pthread_mutexattr_settype(&my_attr, PTHREAD_MUTEX_NORMAL);
    pthread_mutex_init(&my_mutex, &my_attr);

    pthread_t my_thread[5];

    for (int i = 0; i < 5; ++i) {
        pthread_create(&my_thread[i], NULL, PtheadLockType2, NULL);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_join(my_thread[i], NULL);
    }

    pthread_mutex_destroy(&my_mutex);
    pthread_mutexattr_destroy(&my_attr);
}

int main(int argc, char* argv[]) {
    PthreadInit1();

    PthreadInit2();

    return 0;
}