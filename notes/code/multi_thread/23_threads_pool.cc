#include "23_threads_pool.h"

TaskPool::TaskPool() { m_running_ = false; }

TaskPool::~TaskPool() { RemoveAllTasks(); }

void TaskPool::Init(int thread_num) {
    if (thread_num <= 0) {
        thread_num = 5;
    }

    m_running_ = true;

    for (int i = 0; i < thread_num; ++i) {
        std::shared_ptr<std::thread> sp_thread;
        sp_thread.reset(
            new std::thread(std::bind(&TaskPool::ThreadFunc, this)));
        m_threads_list_.push_back(sp_thread);
    }
    std::cout << "Init " << thread_num << " threads." << std::endl;
}

void TaskPool::ThreadFunc() {
    std::shared_ptr<Task> sp_task;
    while (true) {
        std::unique_lock<std::mutex> guard(m_mutex_list_);

        while (m_task_list_.empty()) {
            if (!m_running_) {
                break;
            }

            m_cv_.wait(guard);
        }

        if (!m_running_) {
            break;
        }

        sp_task = m_task_list_.front();
        m_task_list_.pop_front();

        if (sp_task == NULL) {
            continue;
        }

        sp_task->doIt();
        sp_task.reset();
    }
    std::cout << "exit thread, thread id is " << std::this_thread::get_id() << std::endl;
}

void TaskPool::Stop() {
    m_running_ = false;
    m_cv_.notify_all();

    for (auto& iter : m_threads_list_) {
        if (iter->joinable()) {
            iter->join();
        }
    }
}

void TaskPool::AddTask(Task* task) {
    std::shared_ptr<Task> sp_task;
    sp_task.reset(task);

    {
        std::lock_guard<std::mutex> guard(m_mutex_list_);
        m_task_list_.push_back(sp_task);
        std::cout << "Add a task ..." << std::endl;
    }

    m_cv_.notify_one();
}

void TaskPool::RemoveAllTasks() {
    {
        std::lock_guard<std::mutex> guard(m_mutex_list_);
        for (auto& iter : m_task_list_) {
            iter.reset();
        }
        m_task_list_.clear();
    }
}