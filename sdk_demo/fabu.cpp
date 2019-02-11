#include "fabu.hpp"

/*
extern "c" FABU* CreateFABU(){
    std::cout << "Create FABU." << std::endl;
    return new FABU;
}

extern "c" void DestroyFABU(FABU* fabu){
    delete FABU;
}
*/

FABU::FABU(){
    totalNum = 0;
    std::cout << "This is constructor." << std::endl;
    std::cout << "totalNum is " << totalNum << std::endl;
}

FABU::~FABU(){
    std::cout << "This is destructor." << std::endl;
    std::cout << "totalNum is " << totalNum << std::endl;
}


int FABU::addMem(int memId, std::string& name){
    std::cout << "Add mem: " << memId << " memName: " << name << std::endl;
    this -> memName = name;
    this -> memID = memId;
}

int FABU::showNum(){
    totalNum += 1;
    std::cout << "Show number of members which is " << totalNum << std::endl;
}
