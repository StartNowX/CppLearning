#include <iostream>
#include "user.hpp"

using namespace std;

int main(int argc, char* argv[]){
    int ret;

    ret = CreateCls();
    std::cout << "CreateCls ret == " << ret << std::endl;

    ret = InitCls();
    std::cout << "InitCls ret == " << ret << std::endl;

    ret = ShowCls();
    std::cout << "ShowCls ret == " << ret << std::endl;

    ret = DestroyCls();
    std::cout << "DestroyCls ret == " << ret << std::endl;

    return 0;
}
