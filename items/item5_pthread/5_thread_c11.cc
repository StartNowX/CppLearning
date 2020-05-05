/**
 * C++11中关于线程的几个接口，几个常用接口的使用，按照志强的文章来https://mp.weixin.qq.com/s/k_MiJav5PG4amFxSIIUgTw
 * 这里主要关注于：
 *     1. 线程创建：std::thread
 *     2. 线程锁：std::mutex
 *     3. 原子操作：std::atomic<T>
 *     4. call_once
 *     5. 条件变量：std::condition_variable(注意虚假唤醒)
 *         * 很多推荐的方式是将条件锁的wait放到while循环中
 *              while(!cond){
 *                  lock.wait();
 *              }
 */

#include <chrono>
#include <iostream>
#include <thread>

#define PRINT(x) std::cout << x << std::endl;
#define PRINT_STR(str, x) std::cout << str << ": " << x << std::endl;

/**
 * std::thread相关，创建线程后可以执行join和detach两种方式，前者是阻塞式，后者是非阻塞式
 *     std::this_thread::sleep_for()
 *     get_id()：注意和getpid的区别，getpid返回的是内核中真实的线程ID，是不同的；get_id返回POSIX描述的线程ID，相对一个进程的，不同进程之间可能是相同的
 *
 * 为了防止code时忘记detach或join两个处理函数，可以进一步将线程封装
 */

#include <unistd.h>  // getpid使用
class ThreadGuard;
void TestThreadGuard();

void TestThread() {
    auto func = []() {
        for (int i = 0; i < 5; ++i) {
            std::cout << "i = " << i << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        PRINT_STR("thread id", getpid());
    };

    auto func1 = [=](int x) { std::cout << "x = " << x << std::endl; };
    std::thread t1 = std::thread(func);
    if (t1.joinable()) {
        // t1.detach();
        t1.join();
    }

    std::thread t2(func1, 20);
    if (t2.joinable()) {
        PRINT_STR("t2 id", t2.get_id());
        t2.join();
    }

    TestThreadGuard();
}
class ThreadGuard {
   public:
    enum class ActionType { join, detach };

    ThreadGuard(std::thread&& t, ActionType action) : thread_(std::move(t)), action_(action) {}
    ~ThreadGuard() {
        if (thread_.joinable()) {
            if (ActionType::join == action_) {
                thread_.join();
            }
            if (ActionType::detach == action_) {
                thread_.detach();
            }
        }
    }

    ThreadGuard(ThreadGuard&&) = default;
    ThreadGuard& operator=(ThreadGuard&&) = default;

    std::thread& get_thread() { return thread_; }

   private:
    std::thread thread_;
    ActionType action_;
};

void TestThreadGuard() {
    ThreadGuard ttt(std::thread([]() {
                        std::cout << "thread guard" << std::endl;
                        for (int i = 0; i < 4; ++i) {
                            std::cout << "i = " << 3 * i << std::endl;
                        }
                    }),
                    ThreadGuard::ActionType::join);
}

/**
 * std::mutex 锁，线程同步的一种手段，有std::mutex/std::recursive_mutex/std::timed_mutex/std::recursive_timed_mutex
 * std::unique_lock，std::lock_guard是C++11提供的两个RAII机制的动态释放锁资源的锁的封装
 *  其中，std::unique_lock轻量级，且可以手动调用unlock函数，因此条件变量常结合其使用
 */
#include <mutex>
void TestMutexAndLock() {
    std::mutex mtx;
    int global_x = 2;
    std::thread t2([&]() {
        // mtx.lock();
        // std::unique_lock<std::mutex> lck(mtx); // 用unique_lock替代mtx.lock/mtx.unlock
        std::lock_guard<std::mutex> lck(mtx);
        for (int i = 4; i < 6; ++i) {
            global_x += i;
            PRINT_STR("global_x", global_x);
        }
        // mtx.unlock();
    });
    if (t2.joinable()) {
        t2.detach();
    }

    std::thread t1([&]() {
        // std::unique_lock<std::mutex> lck(mtx);
        std::lock_guard<std::mutex> lck(mtx);
        // mtx.lock();
        for (int i = 0; i < 3; ++i) {
            global_x += i;
            PRINT_STR("global_x", global_x);
        }
        // mtx.unlock();
    });
    if (t1.joinable()) {
        t1.detach();
    }
}

/**
 * std::atomic<T> 原子类型，同样实现在多线程中对变量的保护，可以替换加锁的方式
 */
#include <atomic>
void TestAtomicBool() {
    // 通过atomic_int保证对global_x的操作时原子操作，但是由于两个线程之间没有加锁，所以打印的顺序还是不固定的
    std::atomic_int global_x;  //    即std::atomic<int> global_x;

    std::thread t2([&]() {
        global_x = 2;
        for (int i = 4; i < 6; ++i) {
            global_x += i;
            PRINT_STR("global_x", global_x);
        }
    });
    if (t2.joinable()) {
        t2.detach();
    }

    std::thread t1([&]() {
        global_x = 0;
        for (int i = 0; i < 3; ++i) {
            global_x += i;
            PRINT_STR("global_x", global_x);
        }
    });
    if (t1.joinable()) {
        t1.detach();
    }
}

// 配合std::once_flag保证函数只会被调用一次
std::once_flag one_flag;
void CallOnce() {
    std::call_once(one_flag, []() { PRINT("call once"); });
}

void TestCallOnce() {
    std::thread threads[4];
    // CallOnce程序只会调用一次
    for (int i = 0; i < 4; ++i) {
        threads[i] = std::thread(CallOnce);
    }

    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }
}

/**
 * 利用condition_variable实现CountDownLatch，类似于倒计时功能
 * 通知：notify_one通知一个等待的线程，notify_all通知所有等待的线程
 * 等待：wait，wait_for(指定限时)，wait_until
 */
#include <condition_variable>
class CountDownLatch {
   public:
    explicit CountDownLatch(uint32_t cnt) : count_(cnt) {}

    void CountDown() {
        // std::lock_guard<std::mutex> lck(mtx_);
        std::unique_lock<std::mutex> lck(mtx_);  // 和条件变量结合使用unique_lock
        --count_;
        if (count_ == 0) {
            cv_.notify_all();
        }
    }

    void Await(uint32_t timeout = 0) {
        // std::lock_guard<std::mutex> lck(mtx_);
        std::unique_lock<std::mutex> lck(mtx_);  // 和条件变量结合使用unique_lock
        while (count_ > 0) {
            if (timeout > 0) {
                cv_.wait_for(lck, std::chrono::milliseconds(timeout));
            } else {
                cv_.wait(lck);
            }
        }
    }

    uint32_t GetCount() const {
        std::unique_lock<std::mutex> lck(mtx_);
        return count_;
    }


   private:
    std::condition_variable cv_;
    mutable std::mutex mtx_;
    uint32_t count_ = 0;
};


int main(int argc, char* argv[]) {
    // TestThread();

    // TestMutexAndLock();

    // TestAtomicBool();

    TestCallOnce();

    // pause();

    return 0;
}