#include <iostream>

using namespace std;

struct length {
    double value;
    enum class unit : int {
        metre,
        kilometre,
        millimetre,
        centimetre,
        inch,
        foot,
        yard,
        mile,
    };

    static constexpr double factors[] = {1.0, 1000.0, 1e-3, 1e-2, 0.0254, 0.3048, 0.9144, 1609.344};

    explicit length(double val, unit u = unit::metre) { value = val * factors[static_cast<int>(u)]; }
    // explicit length(double val, unit u = unit::metre) { value = val * factors[1]; }

    // 在非构造函数中调用factors时，不需要在类外定义factors
    void set() { double b = factors[static_cast<int>(unit::metre)]; }
};

constexpr double length::factors[];  // 非构造函数中调用可以不用写

/**
 * 支持不同类型的单位相加，但是调用时，需要如下的方式
 * length a(1.0, length::unit::metre);
 * lenght b(1.0, length::unit::kilometre)
 * a+b
 */
length operator+(length lhs, length rhs) { return length(lhs.value + rhs.value); }

/**
 * 为了支持1.0_m + 10.0_cm的写法，重载“”运算符
 *
 * 不能是成员函数，且传参数必须是long double
 */
length operator"" _m(long double v) { return length(v, length::unit::metre); }
length operator"" _cm(long double v) { return length(v, length::unit::centimetre); }
length operator"" _km(long double v) { return length(v, length::unit::kilometre); }

void TestOperator() {
    auto res = 1.0_m + 10.0_cm;
    cout << "res = " << res.value << endl;
}

int main(int argc, char* argv[]) {
    TestOperator();

    // double pi = 3.14159'26535'89793;  // C++14后支持数字型字面量加上'增加可读性
    // cout << "pi = " << pi << endl;

    return 0;
}