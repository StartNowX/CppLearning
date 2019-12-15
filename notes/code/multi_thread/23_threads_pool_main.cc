#include "23_threads_pool.h"

#include <chrono>

int main(int argc, char* argv[]) {
    TaskPool task_pool;
    task_pool.Init();

    Task* task = NULL;
    for (int i = 0; i < 3; ++i) {
        task = new Task();
        task_pool.AddTask(task);
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    task_pool.Stop();

    return 0;
}