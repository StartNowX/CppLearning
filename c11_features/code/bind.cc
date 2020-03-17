#include <functional>
#include <iostream>
#include <memory>
#include <random>

/**
 * bind: 函数模板 bind 生成 f 的转发调用包装器。调用此包装器等价于以一些绑定到 args 的参数调用 f

 * 可调用对象：f，参数：Args
 *
 * https://zh.cppreference.com/w/cpp/utility/functional/bind
 * */

/**
 * std::placeholders::_1, std::placeholders::_2, ..., std::placeholders::_N
 *
 * std::placeholders 命名空间含有占位对象 [_1, . . . _N] ，其中 N 是实现定义的最大数字。
 * 于 std::bind 表达式用作参数时，占位符对象被存储于生成的函数对象，而以未绑定参数调用函数对象时，每个占位符 _N
 * 被对应的第N 个未绑定参数替换。
 *
 * https://zh.cppreference.com/w/cpp/utility/functional/placeholders
 */

void func(int n1, int n2, int n3, const int& n4, int n5) {
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

int gfunc(int n1) { return n1; }

struct Foo {
    void print_sum(int n1, int n2) { std::cout << n1 + n2 << '\n'; }
    int data = 10;
};

void TestBind(void) {
    using namespace std::placeholders;
    {
        int n = 7;
        // 到 bind 的参数被复制或移动，而且决不按引用传递，除非包装于 std::ref 或
        // std::cref，
        // 因此这里最后的n直接把初始值7复制过去
        auto f1 = std::bind(func, _2, 42, _1, std::cref(n), n);
        n = 10;
        f1(1, 2, 1001);  // 1绑定到_1, 2绑定到_2，相当于调用f(2, 42, 1, n, 7);
    }


    {  // 嵌套的bind子表达式共享占位符
        auto f2 = std::bind(func, _3, std::bind(gfunc, _3), _2, 23, 4);
        f2(10, 11, 12);  // func(12, gfunc(12), 11, 23, 4)
    }

    {
        // 常见使用情况：以分布绑定 RNG, 产生随机数
        std::default_random_engine e;
        // 生成随机整数值 i ，均匀分布于闭区间 [a, b] ，即按照以下离散概率函数分布
        std::uniform_int_distribution<> d(0, 10);
        std::function<int()> rnd = std::bind(d, e);  // e 的一个副本存储于 rnd
        for (int i = 0; i < 12; ++i) {
            std::cout << rnd() << " ";
        }
        std::cout << std::endl;
    }

    {  // 绑定指向成员函数指针
        Foo foo;
        // auto pointer = std::bind(&Foo::print_sum, &foo, 123, _2);
        std::function<void(int, int)> pointer = std::bind(&Foo::print_sum, &foo, 123, _2);
        pointer(23, 34);  // foo.print_sum(123, 34)}

        // 绑定指向数据成员指针
        auto f4 = std::bind(&Foo::data, _1);  // 这样可以把对象作为参数
        std::cout << "data = " << f4(foo) << std::endl;

        auto f5 = std::bind(&Foo::data, &foo);  // 这样，固定把foo对象传入
        std::cout << "data = " << f5() << std::endl;
    }

    {
        // 绑定到智能指针
        auto f6 = std::bind(&Foo::data, _1);
        Foo foo;
        std::cout << "smart point: " << f6(std::make_shared<Foo>(foo)) << std::endl;
        // std::make_unique从C++14开始支持
        std::cout << "smart point: " << f6(std::make_unique<Foo>(foo)) << std::endl;
    }
}

int main(int argc, char** argv) {
    TestBind();
    return 0;
}