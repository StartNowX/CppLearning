/**
 * 实现功能：子线程5次，回到主线程3次，再回到子线程4次，再回到主线程2次，如此循环6次
 */

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

std::mutex mtx_;
std::condition_variable cv_;
thread_local int cnt;

void Worker() {
    while (true) {
        cnt = 5;
        std::unique_lock<std::mutex> lck(mtx_);
        // cv_.wait(lck);
        while (cnt-- > 0) {
            cout << "this is sub worker." << endl;
        }
        cnt = 5;
        cv_.notify_all();

        cv_.wait(lck);
    }
}

int main(int argc, char* argv[]) {
    std::thread sub_worker(Worker);
    sub_worker.detach();

    int loop_num = 6;
    while (loop_num-- > 0) {
        cnt = 3;
        // 要用unique_lock，不能用lock_guard，前者功能更多一点，能够支持手动释放锁等
        std::unique_lock<std::mutex> lck(mtx_);
        cv_.wait(lck);
        while (cnt-- > 0) {
            cout << "this is main worker." << endl;
        }
        // cv_.wait(lck, []() { return cnt-- > 0; });
        cnt = 3;
        // 最后一次执行完主线程后不再执行子线程，直接return
        if (loop_num == 0) {
            return 0;
        }
        cv_.notify_one();
    }

    return 0;
}