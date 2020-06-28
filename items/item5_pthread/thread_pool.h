#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <future>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

/**
 * https://mp.weixin.qq.com/s/1ZAR-0qyTEqscpbLob0toA
 */

class ThreadPool {
   public:
    ThreadPool(int num);

    template <typename F, typename... Args>
    auto euqueue(F &&f, Args &&... args) -> std::future<std::result_of_t<F(Args...)>>;

    ~ThreadPool();

   private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex queue_mutex_;
    std::condition_variable cv_;
    bool stop_;
    static const int kMinThreadNum_ = 1;
};

inline ThreadPool::ThreadPool(int num) : stop_(false) {
    num = num < kMinThreadNum_ ? kMinThreadNum_ : num;
    for (int i = 0; i < num; ++i) {
        workers_.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lck(this->queue_mutex_);
                    this->cv_.wait(lck, [this] { return this->stop_ || !this->tasks_.empty(); });
                    if (this->stop_ && this->tasks_.empty()) {
                        return;
                    }
                    task = std::move(this->tasks_.front());
                    this->tasks_.pop();
                }
                task();
            }
        });
    }
}

template <typename F, typename... Args>
auto ThreadPool::euqueue(F &&f, Args &&... args) -> std::future<std::result_of_t<F(Args...)>> {
    using return_type = std::result_of_t<F(Args...)>;
    auto task =
        std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::function<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        if (stop_) {
            throw std::runtime_error("erroe");
        }
        tasks_.emplace([task]() { (*task)(); });
    }
    cv_.notify_all();

    return res;
}


/*
class ThreadPool {
   public:
    using PoolSec = std::chrono::seconds;

    struct ThreadConfig {
        int core_threads;
        int max_threads;
        int max_task_size;
        PoolSec timeout;
    };

    enum class ThreadState { kInit = 0, kWaiting = 1, kRunning = 2, kStop = 3 };
    enum class ThreadFlag { kInit = 0, kCore = 1, kCache = 2 };

    using ThreadPtr = std::shared_ptr<std::thread>;
    using ThreadId = std::atomic<int>;
    using ThreadStateAtomic = std::atomic<ThreadState>;
    using ThreadFlagAtomic = std::atomic<ThreadFlag>;

    struct ThreadWrapper {
        ThreadPtr ptr;
        ThreadId id;
        ThreadFlagAtomic flag;
        ThreadStateAtomic state;

        ThreadWrapper() {
            ptr = nullptr;
            id = 0;
            state.store(ThreadState::kInit);
        }
    };

    using ThreadWrapperPtr = std::shared_ptr<ThreadWrapper>;
    using ThreadPoolLock = std::unique_ptr<std::mutex>;

   private:
    ThreadConfig config_;
    std::list<ThreadWrapperPtr> worker_threads_;

    std::queue<std::function<void()>> tasks_;
    std::mutex task_mtx_;
    std::condition_variable task_cv_;

    std::atomic<int> total_func_num_;
    std::atomic<int> waiting_thread_num_;
    std::atomic<int> thread_id_;

    std::atomic<bool> is_shutdown_now_;
    std::atomic<bool> is_shutdown_;
    std::atomic<bool> is_available_;
};
*/