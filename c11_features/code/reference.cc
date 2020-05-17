#include <iostream>

using namespace std;

// https://mp.weixin.qq.com/s/rpsU0sE8ZQVAF7qZOrDU3Q

/**
 * 完美转发，简单理解就是给的参数是什么类型，转发的就是什么类型
 *
 * 具体移动语义和完美转发是如何实现的，参考TestMove()和TestForward()，注意完美转发时的类型的折叠规则等
 */

/**
 * 0. 左值、右值
 * 1. 左值引用不能指向右值，但可以是常引用
 * 2. 将左值转为右值的方式：std::move， static_cast<T&&>
 */
void TestLeftRightReference() {
    int i_a = 10;
    int& i_a_r = i_a;
    // int &i_a_r2 = 10; // error
    const int& i_a_r3 = 10;  // OK，常引用，存储位置不同

    struct A {
        int m_a_;
        int m_b_;
    };

    A a = {m_a_ : 7, m_b_ : 9};
    A&& a_r = std::move(a);
    A&& a_r_2 = static_cast<A&&>(a);
    cout << "a_r: " << a_r.m_a_ << " " << a_r.m_b_ << endl;
    cout << "a_r: " << a_r_2.m_a_ << " " << a_r_2.m_b_ << endl;
}

/**
 * 移动语义
 * std::move可以接受任意类型的实参，并将其转为右值引用，其实现方式是：
 *
 *  template <typename T>
 *  typename remove_reference<T>::type&& move(T&& t) {
 *      return static_cast<typename remove_reference<T>::type&&>(t)
 *  }
 *
 *  move的形参是T&&，保证了其可以匹配任何类型的实参
 *  1. 若实参是右值，如“abc”，则推导T为普通类型string，返回值类型就是T&&，即string&&
 *  2. 若实参是左值，如string a，则推导T为T&(T& &&), remove_reference<T>的结果是T，即string，
 *      即返回类型为T&&
 */

struct A {
    A() { cout << "constructor" << endl; }
    A(const A& a) { cout << "copy constructor" << endl; }
    A& operator=(const A& a) {
        cout << "operator =" << endl;
        return *this;
    }
    // 移动构造函数
    A(const A&& a) { cout << "&& move" << endl; }
    // 移动赋值运算符
    A& operator=(const A&& a) { cout << "&& operator" << endl; }

    int m_a_ = 10;
    double m_b_ = 12;

    int&& b_1 = std::move(m_a_);
    int&& b_2 = std::move(3);
};

void TestMove() {
    A a1;
    a1.m_a_ = 10;
    a1.m_b_ = 21.02;

    cout << " ====== 1 ====== " << endl;
    A a2 = a1;
    A a3(a1);

    cout << " ====== 2 ====== " << endl;
    A a4 = std::move(a1);  // 如果没有定义移动构造函数，这里还是会调用拷贝构造函数
    A a5;
    a5 = std::move(a1);  // 如果没有定义移动赋值运算符，这里调用拷贝赋值运算符
}

/**
 * 完美转发
 * std::forward<T>() 必须通过显示模板参数类调用，forward返回该显示类型实参的右值引用
 *  template <typename T>
 *  void TEST(T&& args) {
 *      func(std::forward<T>(args));
 *  }
 *      1. 如果实参是右值，T推导出来为普通非引用类型，std::forward<T>将返回T&&
 *      2. 如果实参是左值，T推导出来为T&(规则1)，T& &&折叠为T&(规则2)，std::forward<T>返回一个左值引用的右值引用，
 *          还是左值引用
 *
 * C++参数绑定的两个例外规则：
 *  1. 将左值传递给函数的右值引用参数，且右值引用指向类型模板参数（如T&&）时，编译期推断模板类型参数为实参的左值引用类型
 *  2. 如果间接创建了一个引用的引用，则这些引用形成了“折叠”
 *      T& &, T& && , T&& &都折叠为T&，T&& &&折叠成T&&
 */
#include <typeinfo>

void PrintT(const A& a) { cout << "left, a.m_a_ = " << a.m_a_ << ", m_b_: " << a.m_b_ << endl; }
void PrintT(A&& a) { cout << "right, a.m_a_ = " << a.m_a_ << ", m_b_: " << a.m_b_ << endl; }

template <typename T>
void Print(T&& t) {
    PrintT(t);  // 对PrintT来说，t都是一个变量，因此都是用左值引用这个
    PrintT(std::forward<T>(t));
}
void TestForward() {
    A a1;
    a1.m_a_ = 301;
    a1.m_b_ = 501;

    Print(a1);  // left, left,    a1是左值，规则1推导出T类型是A&，然后T& &&发生引用折叠，还是T&，即T&
    cout << " before move " << endl;
    // std::move(a1)是右值，模板类型推导时，推出T类型为普通非引用类型T，即A，std::forward<T>返回T的右值引用，即A&&
    Print(std::move(a1));
}

int main(int argc, char* argv[]) {
    // TestLeftRightReference();

    // TestMove();

    TestForward();

    return 0;
}