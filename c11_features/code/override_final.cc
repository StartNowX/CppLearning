#include <iostream>

class Base {
   public:
    virtual void print() { std::cout << "base" << std::endl; };

    /**
     * final: 指定某个虚函数不能在子类中被覆盖，或者某个类不能被子类继承。
     * 必须是虚函数
     */
    virtual void Input() final { std::cout << "intput final " << std::endl; }
    // void Input1() final {std::cout << "intput final " << std::endl;}

    void bar();
};

class Derive : public Base {
   public:
    /**
     * override,final都是保留字，不是关键字，只有在正确的位置使用才会启用为关键字
     * 作用：
     * 1.在函数比较多的情况下可以提示读者某个函数重写了基类虚函数（表示这个虚函数是从基类继承，不是派生类自己定义的）；
     * 2.强制编译器检查某个函数是否重写基类虚函数，如果没有则报错。
     **/

    // 在成员函数声明或定义中，override 确保该函数为虚函数并覆盖某个基类中的虚函数
    // virtual void print() const override; // error, Base::print()和Derive:print()签名不匹配
    virtual void print() override { std::cout << "derive" << std::endl; }

    // void bar() override; // error, bar()非虚函数
};

void TestOverride(void) {
    {
        Base* a = new Derive();
        a->print();
        delete a;
    }
}

int main(int argc, char* argv[]) {
    TestOverride();

    return 0;
}