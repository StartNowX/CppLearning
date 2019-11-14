#include <unistd.h>
#include <iostream>
#include <sstream>
#include <thread>

void PrintThreadFunc(int param) {
    std::cout << "This is PrintThreadFunc, param = " << param << std::endl;

    std::thread::id t_id = std::this_thread::get_id();
    std::cout << "way one: thread id is " << t_id << std::endl;

    std::ostringstream oss;
    oss << t_id;
    std::string oss_str = oss.str();
    std::cout << "way twon: thread id is " << oss_str << std::endl;
}

void Thread1(void){
    std::thread test_thread(PrintThreadFunc, 3);

    std::thread::id t_id = test_thread.get_id();
    std::cout << "out way one: thread id is " << t_id << std::endl;
    
    test_thread.detach();
}

int main(int argc, char *argv[]) {
    Thread1();

    sleep(30);
    return 0;
}