#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <iostream>
#include <list>

class Tasks {
   public:
    Tasks(int task_id) : task_id_(task_id) {}
    ~Tasks() {}

    void DoTask() {
        std::cout << "Handle a task, task id is " << task_id_ << std::endl;
    }

   private:
    int task_id_;
};

pthread_mutex_t my_mutex;
std::list<Tasks *> tasks;
// sem_t my_semaphore;
pthread_cond_t my_cv;

void *consumer_thread(void *args) {
    Tasks *task_ptr = NULL;
    while (true) {
        pthread_mutex_lock(&my_mutex);
        // 使用while防止虚假唤醒
        while (tasks.empty()) {
            pthread_cond_wait(&my_cv, &my_mutex);
        }

        task_ptr = tasks.front();
        tasks.pop_front();
        std::cout << "pthread id is " << pthread_self() << ", LWP("
                  << syscall(SYS_gettid) << ")." << std::endl;
        pthread_mutex_unlock(&my_mutex);

        if (NULL == task_ptr) {
            continue;
        }

        task_ptr->DoTask();
        delete task_ptr;
    }
    return NULL;
}

int task_id = 0;
void *producer_thread(void *args) {
    // int task_id = 0;
    Tasks *task_ptr = NULL;
    while (true) {
        // 消费者线程中释放资源
        task_ptr = new Tasks(task_id);

        pthread_mutex_lock(&my_mutex);
        tasks.push_back(task_ptr);
        std::cout << "produce one thread, thread id is " << task_id
                  << std::endl;
        pthread_mutex_unlock(&my_mutex);

        // 一次唤醒一个线程,具体唤醒哪个,比较随机,pthread_cond_broadcast唤醒多个线程
        pthread_cond_signal(&my_cv);

        task_id++;

        sleep(1);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_mutex_init(&my_mutex, NULL);
    pthread_cond_init(&my_cv, NULL);

    pthread_t consumers[5];
    for (int i = 0; i < 5; ++i) {
        pthread_create(&consumers[i], NULL, consumer_thread, NULL);
    }

    // 创建一个生产者
    // pthread_t producer;
    // pthread_create(&producer, NULL, producer_thread, NULL);
    // 创建多个生产者,
    // 当有多个生产者时,会出现资源数大于1,可以满足多个消费者线程同时执行
    pthread_t producers[3];
    for (int i = 0; i < 1; ++i) {
        pthread_create(&producers[i], NULL, producer_thread, NULL);
    }
    for (int i = 0; i < 1; ++i) {
        pthread_join(producers[i], NULL);
    }
    // pthread_join(producer, NULL);

    // 若创建生产者之前join, 则消费者一直在阻塞
    for (int i = 0; i < 5; ++i) {
        pthread_join(consumers[i], NULL);
    }
    // pthread_join(producer, NULL);

    pthread_mutex_destroy(&my_mutex);
    pthread_cond_destroy(&my_cv);

    return 0;
}