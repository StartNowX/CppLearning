#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T>
T foo(T*) {
    static_assert(std::is_copy_constructible<T>::value, "error");
    // static assertion that does not depend on template parameters will result in compile error
    // int a = 2;
    // static_assert(sizeof(int) > 10, "smakll");
    std::cout << "this is void pointer." << std::endl;
}

template <typename RT, typename T1, typename T2>
RT max1(T1 a, T2 b) {
    std::cout << "max with one parameter." << std::endl; 
    return a > b ? a : b;
}

template <typename T1, typename T2>
auto max2(T1 a, T2 b) -> decltype(true ? a : b) { // c++11, must has decltype
// auto max2(T1 a, T2 b) { // C++ 14, can use only auto
    std::cout << "max with one parameter." << std::endl; 
    return a > b ? a : b;
}


template <typename T1, typename T2>
auto max3(T1 a, T2 b) -> typename std::decay<decltype(true ? a : b)> { // c++11, must has decltype
    std::cout << "max with one parameter." << std::endl; 
    return a > b ? a : b;
}

template <typename T1, typename T2>
//typename std::common_type<T1, T2>::type max4(T1 a, T2 b) {
std::common_type_t<T1, T2> max4(T1 a, T2 b) { // C++ 14
    return a > b ? a : b;
}

int main(int argc, char* argv[]) {

    std::cout << "begin template..." << std::endl;

    // void *ptr = nullptr;
    // foo(ptr);

    int *ptr = nullptr;
    foo(ptr);

    auto res1 = ::max1<double>(4, 7.2); 
    std::cout << "max value: " << res1 << ", type is " << typeid(res1).name() << std::endl;
    auto res2 = ::max2(4, 7.2);
    std::cout << "max value: " << res2 << ", type is " << typeid(res2).name()  << std::endl;
    auto res3 = ::max2(4, 7.2);
    std::cout << "max value: " << res3 << ", type is " << typeid(res3).name()  << std::endl;


    auto res4 = ::max4(3, 5.5);
    std::cout << "max value: " << res4 << ", type is " << typeid(res4).name()  << std::endl;

    std::cout << "end template..." << std::endl;
    return 0;
}
