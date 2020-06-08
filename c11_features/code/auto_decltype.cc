#include <iostream>

using namespace std;

// 参考 https://mp.weixin.qq.com/s/lQpDUJkzT55WENzpYfa7sQ
// https://mp.weixin.qq.com/s/cGDtP6IXcRajiPnfJqFdsA
/**
 * auto/decltype: 编译期推导出变量类型，decltype推导表达式的类型
 *
 * auto不声明为引用或指针时，会忽略CV属性，声明为引用或指针时，会保留CV属性;
 * decltype会保留CV属性，decltype(())会返回类型的饮用
 *
 * decltype一般会用于做尾置类型推导
 */
#include <typeinfo>
void TestAuto() {
    int sd = 3;
    auto a = sd;
    cout << "type: " << typeid(a).name() << endl;

    const double d_a = 4.56;
    auto d_a1 = d_a;
    auto& d_a2 = d_a;
    d_a1 = 5.67;
    // d_a2 = 6.78;  // error, d_a2声明为引用，因此保留d_a的cv属性
    cout << "type: " << typeid(d_a1).name() << ", name: " << typeid(d_a2).name() << endl;

    decltype(d_a) b = 3.0;
    cout << "type: " << typeid(b).name() << endl;
}

template <typename T>
void PrintContainer(const T& container) {
    // for (auto it = container.begin(); it != container.end(); ++it) {
    //     cout << " " << *it << endl;
    // }
    for (typename T::const_iterator it = container.begin(); it != container.end(); ++it) {
        cout << " " << *it;
    }
    cout << endl;

    // 这里typename和class没有区别
    for (class T::const_iterator it = container.begin(); it != container.end(); ++it) {
        cout << " " << *it;
    }
    cout << endl;

    // 当定义一个模板的模板时，class用法比较特殊
    typename T::value_type val = 4;
    cout << "param val = " << val << endl;
}

// 函数重载，以支持C语言中的数组形式
template <typename T, size_t N>
void PrintContainer(const T (&a)[N]) {
    typedef const T* ptr;
    for (ptr it = a, end = a + N; it != end; ++it) {
        cout << " " << *it;
    }
    cout << endl;
}

// 统一上面两种打印函数，用自动类型推断auto，同时使用系统函数std::begin和std::end，而不是容器的迭代器
template <typename T>
void PrintContainerUnity(const T& container) {
    using std::begin;
    using std::end;
    for (auto it = begin(container); it != end(container); ++it) {
        cout << " " << *it;
    }
    cout << endl;
}

struct A {
    using INT = int;
};

template <typename T>
void fun() {
    // 必须用typename，依赖参数，如果用class，编译器会认为是类
    typename T::INT c = 2;
    cout << "c = " << c << endl;
}

#include <vector>
void TestAutoVec() {
    vector<int> vec{1, 2, -3, 4};
    PrintContainer(vec);
    int arr[5] = {1, -3, -2, 4};
    PrintContainer(arr);
    PrintContainerUnity(vec);
    PrintContainerUnity(arr);

    fun<A>();

    vector<int>::value_type val = 4;
    cout << "val = " << val << endl;
}

template <typename T>
auto Add(T a, T b) -> decltype(a + b) {
    return a + b;
}

/** C++14，函数返回值可以是auto或decltype(auto)
 * 用auto得到值类型，auto&或auto&&得到引用
 *
 * decltype(auto)得到根据表达式通用的结果决定
 * */
// template <typename T>
// decltype(auto) Add14(T a, T b) {
//     return a + b;
// }

/**
 * 假如a是int，则
 * decltype(a)，获得int类型
 * decltype((a)), 获得int&类型
 * decltype(a+a), 获得int类型（a+a是prvalue）
 */
void TestDecltype() {
    const int i_a = 2;
    decltype(i_a) i_b = 3;
    // i_b = 4;  // error, decltype推导时不会忽略cv属性

    auto res = Add<int>(i_a, i_b);
    std::cout << "res = " << res << endl;

    auto res1 = Add14<int>(i_a, i_b);
    cout << "res1 = " << res1 << endl;

    int i_c = 3;
    int i_d = 4;
    decltype((i_c)) c_b = i_d;
    decltype(i_c) c_d = 3;
    c_b = 5;
    cout << "i_c = " << i_c << ", i_d = " << i_d << ", c_b = " << c_b << endl;
}

int main(int argc, char* argv[]) {
    // TestAuto();

    // TestAutoVec();

    TestDecltype();

    return 0;
}