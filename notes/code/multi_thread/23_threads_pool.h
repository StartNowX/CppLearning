#ifndef THREADS_POOL_H_
#define THREADS_POOL_H_

#include <condition_variable>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

class Task {
   public:
    virtual void doIt() { std::cout << "handle a task ..." << std::endl; }

    virtual ~Task() { std::cout << "destruct a task ..." << std::endl; }
};

class TaskPool {
   public:
    TaskPool();
    ~TaskPool();
    TaskPool(const TaskPool& rhs) = delete;
    TaskPool& operator=(const TaskPool& rhs) = delete;

   public:
    void Init(int thread_num = 5);
    void Stop();

    void AddTask(Task* task);
    void RemoveAllTasks();

   private:
    void ThreadFunc();

   private:
    std::list<std::shared_ptr<Task>> m_task_list_;
    std::mutex m_mutex_list_;
    std::condition_variable m_cv_;
    bool m_running_;
    std::vector<std::shared_ptr<std::thread>> m_threads_list_;
};

#endif  // THREADS_POOL_H_