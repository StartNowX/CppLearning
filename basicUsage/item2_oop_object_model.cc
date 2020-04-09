/**
 * C++对象模型的解读，书籍《深度探索C++对象模型》
 *
 * 从博客开始了解 https://www.cnblogs.com/qg-whz/p/4909359.html
 * 参考https://songlee24.github.io/2014/09/02/cpp-virtual-table/的图例
 */


#include <iostream>

using namespace std;

/******* 虚函数表
 * 1. 一个类中存在虚函数，或其基类存在虚函数表，【编译期】就会为【对象】添加一个虚函数指针，指向【类的】虚函数表
 * 2. 虚函数指针一般存储于对象模型内存布局的最先的地方，方便多层继承或多重继承时，能够以最高的效率找到虚函数表
 * 3. 虚函数表存储的是一系列虚函数的地址，一个类的所有对象共用一个虚函数表，其中虚函数的出现顺序和其声明顺序有关
 ******************/
void TestVirPtr(void) {
    class Base {
       public:
        Base() {}
        ~Base() {}

        virtual void print() { std::cout << "this is base print!!!" << std::endl; }

        virtual void set() { std::cout << "this is set function!!!" << std::endl; }
    };

    class Derived1 : public Base {
       public:
        virtual void print() { std::cout << "this is derived1 print!!!" << std::endl; }
    };

    class Derived2 : public Base {
       public:
        virtual void print() { std::cout << "this is derived2 print!!!" << std::endl; }
    };

    Base *p = new Base();
    Base *p1 = new Derived1();
    Base *p2 = new Derived2();

    {
        // 虚函数指针的地址，第一个虚函数的地址
        int *vptr_addr = (int *)(&p);
        std::cout << "virtual function pointer addr: " << vptr_addr << std::endl;

        // 第二个虚函数的地址
        std::cout << "2nd virtual func addr: " << (vptr_addr + 1) << std::endl;
    }

    delete p;
    delete p1;
    delete p2;
}


class Base {
   public:
    Base(int i) : base_i(i){};

    // non-static function
    int get_data() { return base_i; }

    // static function
    static void CountI() {}

    virtual ~Base() {}

    // virtual function
    virtual void print() { std::cout << "Base::print" << std::endl; }

   private:
    int base_i;
    static int base_s;
};

/** 对象模型概述
 * 1. 两种数据成员：static 和 non-static
 * 2. 三种成员函数：static、non-static和virtual
 *
 *  **** 非继承下的C++模型 ****
 * 0. non-static数据成员被存放于类对象之中，static数据成员则在类对象之外；
 *    static&&non-static的成员函数都是类对象之外，而virtual是由虚函数表和虚表指针支持的
 * 1. 每个【类】生成一个虚表（vtbl），存储所有虚函数的指针，具体的存储顺序按照虚函数的声明顺序
 * 2. 每个【对象】生成一个虚表指针（vptr），由编译器生成；虚表指针的设定和重置由类的复制控制（构造函数、赋值、析构等）；
 *    虚表指针的位置，一般是放在类的最顶端，方便快速定位到虚函数表
 * 3. 虚函数表的前面还有一个指向type_info的指针，用以支持RTTI
 *
 *  **** 单继承下的C++模型 ****
 * 1. 当子类没有覆盖（overwrite），直接将子类的虚函数添加到虚函数表中
 * 2. 当子类覆盖了父类的虚函数时，则是将虚函数表中父类虚函数的位置用子类的虚函数替换
 * 由于虚函数表是在【编译时】创建的，所以根据上面两种情况，就能够实现多态了
 *
 *  **** 多继承下的C++模型（非菱形继承） ****
 * 1. 子类的虚函数只放在声明的第一个基类中
 * 2. 若子类覆盖了父类的虚函数，则所有基类的对应的函数都会被覆盖 （这一点保证来多态）
 * 3. 内存布局中，父类的顺序按照声明的顺序来
 *
 * **** 多继承下的C++模型（菱形继承） ****
 * 这种情况会导致子类中包含多份基类的数据，导致内存空间的浪费，因此可以通过虚继承来规避
 */
void TestOopModel(void) {
    Base *p = new Base(2);
    std::cout << "Base vptr = " << (int *)&p << std::endl;

    std::cout << "Base vptr type_info = " << (int *)&p - 1 << std::endl;
}

/** 虚继承
 * 1. 虚继承的子类，如果本身定义了新的虚函数，则编译器为其生成一个虚函数指针（vptr）以及一张虚函数表。
 *    该vptr位于对象内存最前面。
 *      非虚继承：直接扩展父类虚函数表。
 * 2. 虚继承的子类也单独保留了父类的vprt与虚函数表。这部分内容接与子类内容以一个四字节的0来分界。
 * 3. 虚继承的子类对象中，含有四字节的虚表指针偏移值。
 */

int main(int argc, char *argv[]) {
    // TestVirPtr();

    TestOopModel();

    return 0;
}
