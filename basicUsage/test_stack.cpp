#include "Stack.hpp"
#include "Stack.cpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    Stack<int> stack;

    int ret = 0;
    std::cout << "isempty =  " << stack.isempty() << std::endl;
    std::cout << "isfull =  " << stack.isfull() << std::endl;

    for(int i = 0; i < 10; i++){
        ret = stack.push(i);
        std::cout << "index " << i << " ret is " << ret << std::endl;
    }

    for(int i = 0; i < 10; i++){
        int tmpItem;
        ret = stack.pop(tmpItem);
        std::cout << "index " << i << " ret is " << ret << " tmpItem is " << tmpItem << std::endl;
    }


    return 0;
}
