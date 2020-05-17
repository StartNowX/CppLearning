#include <iostream>

using namespace std;

// 参考 https://mp.weixin.qq.com/s/lQpDUJkzT55WENzpYfa7sQ
// https://mp.weixin.qq.com/s/cGDtP6IXcRajiPnfJqFdsA
/**
 * auto/decltype: 编译期推导出变量类型，decltype推导表达式的类型
 *
 * auto不声明为引用或指针时，会忽略CV属性，声明为引用或指针时，会保留CV属性; decltype会保留CV属性
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
auto Add(T a, T b) -> decltype(a + b) {
    return a + b;
}

void TestDecltype() {
    const int i_a = 2;
    decltype(i_a) i_b = 3;
    // i_b = 4;  // error, decltype推导时不会忽略cv属性

    auto res = Add<int>(i_a, i_b);
    std::cout << "res = " << res << endl;
}

int main(int argc, char* argv[]) {
    // TestAuto();

    TestDecltype();

    return 0;
}