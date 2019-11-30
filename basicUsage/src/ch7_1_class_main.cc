#include <iostream>

#include "ch7_class.h"


using namespace std;

int main(int argc, char* argv[]) {
    FriendTest friend_test(21);
    int tmp_a = 10;

    cout << "result is " << AddFriend(friend_test, tmp_a) << endl;

    return 0;
}