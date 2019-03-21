#include <iostream>
#include <string>
#include "PersonManage.hpp"

int main(int argc, char* argv[]){

    PersonManage person1;
    person1.SetName("Jack Ma");
    person1.GetName();

    const PersonManage person2("Tom Ma", 58, 170);
    person2.SetName("Yelo");
    person2.GetName();

    //enum egg {SMALL, MEDIUM, LARGER};
    //enum t_shirt {SMALL, MEDIUM, LARGER}; // error, redeclaration
    enum class egg {SMALL, MEDIUM, LARGER};
    enum class t_shirt {SMALL, MEDIUM, LARGER}; // use class/struct

    return 1;
}
