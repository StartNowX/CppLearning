#include "OperateOverload.hpp"

int main(int argc, char* argv[]){
    Time tNow;
    Time tPast(3, 20);
    std::cout << "past time is " << tPast << std::endl;

    tNow.Reset(5, 12);
    std::cout << "now time is " << tNow << std::endl;

    Time multTime = tPast * 3;
    std::cout << "past time * 3: " << multTime << std::endl;
    multTime = 4 * tPast;
    std::cout << "4 * past time: " << multTime << std::endl;

    std::cout << "past time is " << tPast << std::endl;
    std::cout << "now time is " << tNow << std::endl;
    std::cout << "tNow - tPast = " << (tNow - tPast) << std::endl;

    return 0;
}
