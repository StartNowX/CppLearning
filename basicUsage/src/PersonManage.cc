#include <iostream>
#include "PersonManage.hpp"

#define NAMELENGTH 128

PersonManage::PersonManage(){
    this -> name = new char[NAMELENGTH];
    std::cout << " call default constructor function." << std::endl;
}

PersonManage::PersonManage(const std::string& name, const int age, const int height){
    this -> name = new char[NAMELENGTH];
    memcpy(this->name, name.c_str(), sizeof(char) * name.size());
    this -> name[name.size()] = '\0';
    this -> age = age;
    this -> height = height;
    std::cout << " call defined constructor function." << std::endl;
}

PersonManage::~PersonManage(){
    std::cout << " call deconstructor function." << std::endl;
    delete []name;
    name = NULL;
}

void PersonManage::SetName(const std::string& name){
    memcpy(this->name, name.c_str(), sizeof(char) * name.size());
    this -> name[name.size()] = '\0';
    std::cout << " call non-const function." << std::endl;
}

void PersonManage::SetName(const std::string& name) const{
    // this -> name = name.c_str();  // Error const function

    for(size_t i = 0; i < name.size(); i++){
        this -> name[i] = name[i];
    }
    this -> name[name.size()] = '\0';
    std::cout << " call const function." << std::endl;
};

void PersonManage::GetName() const{

    std::cout << " name: " << this -> name << std::endl;
}
