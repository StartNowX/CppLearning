#include <iostream>
#include <utility>

using namespace std;

void PrintMax(int a, int b) { cout << "[PrintMax] max is: " << (a > b ? a : b) << endl; }
void PrintDoubleMax(int param_a, int& param_b) {
    param_b *= 2;
    cout << "[PrintDoubleMax] max is: " << (param_a > param_b ? param_a : param_b) << endl;
    // cout << "a = " << a << ", b = " << b << endl;
}
void PrintDoubleMax2(int&& param_a, int& param_b) {
    param_b *= 2;

    cout << "[PrintDoubleMax2] max is: " << (param_a > param_b ? param_a : param_b) << endl;
}

// 接受一个可调用对象和两个参数的模板
template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2) {
    f(t2, t1);
}

template <typename F, typename T1, typename T2>
void flip2(F f, T1&& t1, T2&& t2) {
    f(t2, t1);
}

// 完美转发，保持给定实参的左值/右值属性
template <typename F, typename T1, typename T2>
void flip3(F f, T1&& t1, T2&& t2) {
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

// forward原型
template <typename T>
T&& forward(typename remove_reference<T>::type& param) {
    return static_cast<T&&>(param);
}

// move原型
template <typename T>
typename remove_reference<T>::type&& move(T&& param) {
    using ReturnType = typename remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);
}

void TestFlip() {
    if (false) {  // works well
        flip1(PrintMax, 3, 5);
    }

    if (false) {
        int a = 10;
        int b = 8;
        PrintDoubleMax(a, b);  // b = b*2
        // cout << "a = " << a << ", b = " << b << endl;
        // 这里b的值不会被改变，因为flip1的参数t1是普通、非引用的int类型，而非int&
        // 实例化结果：void flip1(void(*fcn)(int, int&), int t1, int t2),
        // PrintDoubleMax中的引用参数param_b被绑定到t2上，而不是flip1的实参b
        flip1(PrintDoubleMax, a, b);
        cout << "[MAIN] a = " << a << ", b = " << b << endl;
    }

    if (false) {
        int a = 4;
        int b = 3;
        // 这里，将传递给flip2的t1一个左值, 推断出T1类型为int&,
        // 导致t1的类型被折叠为int&，然后b被绑定到t1上，PrintDoubleMax的param_b绑定到t1上，所以param_b的改变会被传给t1传给b

        // 万能引用
        // 参考https://www.cnblogs.com/5iedu/p/11308158.html
        flip2(PrintDoubleMax, b, 4);
        cout << "[MAIN] a = " << a << ", b = " << b << endl;  // 4, 6

        // complie error, cannot bind "int" lvalue to "int&&"
        // T1被推断为int&, T2被推断为int，而函数参数是左值表达式，将左值用来实例化一个int&&将导致错误
        // flip2(PrintDoubleMax2, b, 4);
    }

    if (true) {
        int a = 4;
        int b = 3;
        // 可以参考forward的原型进行推理参数为左值或右值的情况
        // 参考https://www.cnblogs.com/5iedu/p/11324772.html
        flip3(PrintDoubleMax2, b, 4);
        cout << "[MAIN] a = " << a << ", b = " << b << endl;  // 4, 6
    }
}

int main(int argc, char* argv[]) {
    TestFlip();

    return 0;
}