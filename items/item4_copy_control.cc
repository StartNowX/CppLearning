/**
 * 本章节主要涉及C++面向对象的拷贝控制操作，主要涉及的几个函数为：
 *      1. 拷贝构造函数
 *      2. 拷贝赋值运算符
 *      3. 移动构造函数
 *      4. 移动赋值运算符
 *      5. 析构函数
 * 1和3定义了当用同类型的另一个对象【初始化】本对象时做什么
 * 2和4定义了当用同类型的另一个对象【赋值】本对象时做什么
 *
 * 如果一个类没有定义这些拷贝控制成员，编译器会自动为其定义缺失的操作
 */

#include <iostream>

#define PRINT_INFO(str) std::cout << str << std::endl;
#define PRINT_MEM_INFO(str, x) std::cout << str << x << std::endl;

/** 拷贝构造函数
 * 1. 即便用户定义了其他构造函数，编译器也会合成一个拷贝构造函数（但默认构造函数不会这样）
 * 2. 拷贝构造函数传参【必须是引用】，如果传值，会陷入循环，一般是const的
 * 3. 一个类中如果有【移动构造函数】，则拷贝初始化是通过【移动构造实现的】
 *
 * 4. 注意区分【直接初始化】和【拷贝初始化】的区别
 *      前者相当于函数匹配的过程，后者是拷贝的过程（如vector中的push和emplace）
 *
 * 调用拷贝构造初始化的几种情况
 *  1. 用【=】定义变量时
 *  2. 以非引用的形式给函数传参
 *  3. 函数返回一个非引用形式的对象作为返回值（现在gcc已经做优化了，编译时加上-fno-elide-constructors才会调用）
 *  4. 用花括号列表初始化一个数组中的元素或一个聚合类中的成员
 */

/** 析构函数
 * 一个类只能有【唯一一个】析构函数，且不能被重载
 *  1. 析构时按初始化的顺序逆序析构
 *  2. 隐式析构时内置的指针类型不会delete其指向的对象
 *
 *  3. 当指向一个对象的引用或指针离开作用域时，不会调用析构
 *  4. 析构函数本身并不是直接销毁成员，【成员是在析构函数体之后隐含的析构阶段被销毁的】，用于用户删除自己申请的堆内存？
 */

/** 三五法则
 * 拷贝构造函数、拷贝赋值运算符和析构函数，是三个可以操作控制类的拷贝操作
 * 新标准下，一个类还可以定义移动构造函数和移动赋值运算符
 *
 * 2. 需要析构函数的类也需要拷贝和赋值操作
 *
这里可以这样理解：对于需要显示声明析构函数的类（即具有不平凡析构函数），说明类中具有需要手动操作或释放的资源（特别是类中的指针成员），如果这里使用合成拷贝构造函数，那么合成拷贝构造函数默认的执行操作只是把指针再指向新的对象，这就会导致两个指针指向同一个对象，最后出现double
free的问题
 * 需要拷贝操作的类也需要赋值操作，反之亦然
 */
class FDatas {
   public:
    FDatas(const std::string& str, int n) : id_(str), value_(n) {
        // std::cout << "default copy, id_ = " << this->id_ << std::endl;
        PRINT_MEM_INFO("default copy, id_ = ", this->id_);
    }
    FDatas(const FDatas& fd) {
        this->id_ = fd.id_;
        this->value_ = fd.value_;

        PRINT_MEM_INFO("this is copy constructor. id_ = ", this->id_);
    }

    // 重载运算符，必须定义为成员函数，这样运算符左侧的则能绑定到隐式的this参数中
    FDatas& operator=(const FDatas& fd) {
        this->id_ = fd.id_;
        this->value_ = fd.value_;
        PRINT_MEM_INFO("this is copy operator, id_ = ", fd.id_);
        return *this;
    }

    ~FDatas() { PRINT_INFO("this is deconstructor"); }

   public:
    void Print() { PRINT_MEM_INFO("Print id_ = ", this->id_); }

   private:
    std::string id_;
    int value_;
};

// gcc会做优化，返回临时对象时，不会构造临时对象了，加上-fno-elide-constructors才会
FDatas CopyData(FDatas fd) {
    PRINT_INFO("test CopyData");
    // 拷贝构造
    FDatas tmp_fd = fd;

    return tmp_fd;
}
void TestCopyConstructor() {
    FDatas fd("abc", 13);  // 直接初始化
    FDatas fd1 = fd;       // 拷贝初始化
    FDatas fd1_1(fd);      // 直接初始化

    PRINT_INFO("test copy data");

    // fd1拷贝给形参，调用拷贝构造函数
    FDatas fd2 = CopyData(fd1);

    FDatas fd3("ff", 12);
    fd3 = fd2;  // 拷贝赋值运算符

    PRINT_INFO("sdf");
    fd3.~FDatas();  // 即便显示调用了析构函数，最后还是会调用一次析构，因为这时候对象还是在内存中
    fd3.Print();
    PRINT_INFO("sdf111");
}

// POD
class A {};
class A1 {
    A1(const A& a) {}
};
class B {
    ~B();
};
// 用std::is_trivial<T>::value判断是否为平凡类型
void TestPOD() {
    PRINT_MEM_INFO("is_trival FDatas: ", std::is_trivial<FDatas>::value);
    PRINT_MEM_INFO("is_trival A: ", std::is_trivial<A>::value);    // 1
    PRINT_MEM_INFO("is_trival A1: ", std::is_trivial<A1>::value);  // 0, 有不平凡的构造函数
    PRINT_MEM_INFO("is_trival B: ", std::is_trivial<B>::value);    // 0, 有不平凡的析构函数
}

/** 拷贝控制
 * 1. default关键字
 *      * 显示要求编译器生成合成版本的控制函数
 *      * 如果在类内使用，编译器会将其隐式声明为inline，如果不希望是inline，只能在类外定义时加入default
 * 2. delete
 *      * c11可以在函数列表后添加`=delete`将函数定义为删除的，这样用户便不可再调用之
 *      * `=delete`必须出现在函数第一次声明时，而`=default`则不是
 *          * 编译器在一开始编译时就需要知道该函数是否可删除，而default是编译器在生成代码时才需要
 *      * 不能delete析构函数
 *          * 析构函数被delete的类，可以被动态分配，但是不能delete，见TestDefaultAndDelete
 *
 * 3. private拷贝控制
 *      * 还可以将拷贝构造函数等定义为private，以阻止用户使用，但并不能阻止类内其他成员和友元使用
 *      * 如果为了不让其他成员和友元使用，可以声明为private，但是不定义
 *      * 如果需要阻止拷贝，建议还是使用`delete`
 */
class FDataNew {
   public:
    FDataNew() = default;
    FDataNew(const FDataNew& fdn) = default;
    FDataNew& operator=(const FDataNew& fdn);

    ~FDataNew() = default;
};
FDataNew& FDataNew::operator=(const FDataNew& fdn) = default;

struct FD {
    FD() = default;
    ~FD() = delete;
};
void TestDefaultAndDelete() {
    FDataNew fdn;
    FDataNew fdn1(fdn);

    FD* fd = new FD();  // Ok
    // delete fd;          // error, 析构函数被delete了
}

int main(int argc, char* argv[]) {
    // TestCopyConstructor();
    // TestPOD();

    TestDefaultAndDelete();
    return 0;
}