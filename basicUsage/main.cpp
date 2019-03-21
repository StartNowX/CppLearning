#include <iostream>
#include <string>
#include "PersonManage.hpp"

int main(int argc, char* argv[]){

    PersonManage person1;
    person1.SetName("Jack Ma");
    person1.GetName();

    const PersonManage person2("Jack Ma", 58, 170);
    person2.SetName(name);
    person2.GetName();

    return 1;
}
