/**
 * 可变参数模板相关
 */

#include <iostream>
#include <ostream>
#include <string>

using namespace std;

// 可变参数模板
// Args模板参数包，表示0或多个模板参数
// rest函数参数包, 表示0或多个函数参数
template <typename T, typename... Args>
void foo(const T& t, const Args&... rest) {
    // sizeof... 返回常量表达式，表示包中参数的个数
    cout << "模板参数个数: " << sizeof...(Args) << ", 函数参数个数: " << sizeof...(rest) << endl;
}

template <typename T>
ostream& print(ostream& os, const T& t) {
    // cout << "[print one param]" << endl;
    return os << t;
}

template <typename T, typename... Args>
ostream& print(ostream& os, const T& t, const Args&... rest) {  // ... 展开模板参数
    // cout << "[print variadic param]" << endl;
    os << t << ", ";
    // 此处调用时，传递两个参数，将参数包里面的第一个参数绑定到T中，剩余实参为下一个print的参数包,以此保证递归打印
    // 在此之前，一定要声明一个模板的print函数，否则递归调用到最后一次时，会循环打印
    return print(os, rest...);  // ... 展开函数参数
    // 结合ch16_template_overload_main.cc中定义的debug_rep，还可以如下的方式扩展
    // 展开为print(os, debug_rep(a1), debug_rep(a2),.....)
    // 不能写成print(os, debug_rep(rest...)), 这样就变成了print(os, debug_rep(a1,
    // a2,....))
    // print(os, debug_rep(rest)...);
}

void TestVariadicTemplate() {
    //
    if (true) {
        int i = 0;
        double d = 3.14;
        string s = "how now";
        foo(i, 43, d, s);
        foo(s, 32, "hi");
        foo(d, s);
    }

    if (true) {
        int i = 50;
        string s = "well";
        print(cout, i, s, 43);
    }

    return;
}

int main(int argc, char* argv[]) {
    TestVariadicTemplate();
    return 0;
}