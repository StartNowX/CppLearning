#include "Stack.hpp"

template <class T>
Stack<T>::Stack(){
    top = 0;
}

template <class T>
bool Stack<T>::isempty() const{
    return 0 == top;
};

template <class T>
bool Stack<T>::isfull() const{
    return MAX == top;
};

template <class T>
bool Stack<T>::push(const T& item){
    if(top < MAX){
        items[top++] = item;
        return true;
    }
    else{
        return false;
    }
};

template <class T>
bool Stack<T>::pop(T& item){
    if(top > 0){
        item = items[--top];
        return true;
    }
    else{
        return true;
    }
}

/*
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
*/
