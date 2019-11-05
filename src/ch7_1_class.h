#ifndef CH7_CLASS_
#define CH7_CLASS_

class FriendTest {
   public:
    friend int AddFriend(const FriendTest& friend_test, int a);

   public:
    FriendTest() = default;
    FriendTest(int num) : number_(num){};
    ~FriendTest(){};

   private:
    int number_;
};

int AddFriend(const FriendTest& friend_test, int a);

#endif  // CH7_CLASS_