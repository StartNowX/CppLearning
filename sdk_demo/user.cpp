#include <string>
#include "fabu.hpp"

FABU* fabuPtr;

int CreateCls(){
    std::cout << "Create FABU cls." << std::endl;
    fabuPtr = new FABU();
    if(fabuPtr != NULL){
		return 0;
    }
    return 1;
}

int InitCls(){
    std::cout << "Begin Init Cls." << std::endl;
    std::string name = "jack";
    fabuPtr -> addMem(1024, name);
    return 0;
}

int ShowCls(){
    std::cout << "Begin show cls." << std::endl;
    fabuPtr -> showNum();
    return 0;
}

int DestroyCls(){
    std::cout << "Destroy FABU cls." << std::endl;
    delete fabuPtr;
    if(fabuPtr != NULL){
        fabuPtr = NULL;
        return 1;
    }
    return 0;
}
