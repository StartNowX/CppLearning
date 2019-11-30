/**
 * Primer Edition 5
 */

#include <iostream>
#include <string>

using namespace std;

void diff_pointarray_arraypoint(void) {
    int arr[5] = {0, 1, 2, 3, 4};
    int(*ap)[5] = &arr;
    std::cout << "elements in array point are: " << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "index: " << i << ": " << (*ap)[i] << std::endl;
    }

    std::cout << "elements in point array are: " << std::endl;
    int arr1[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    int *pa[3];
    for (int i = 0; i < 3; ++i) {
        pa[i] = arr1[i];
    }
    for (int i = 0; i < 3; ++i) {
        int *tmp = pa[i];
        for (int j = 0; j < 2; j++) {
            std::cout << "index: " << i << ": " << j << " : " << tmp[j] << std::endl;
        }
    }
}

void chg_params_length(std::initializer_list<std::string> ils) {
    cout << "elements in initializer list are: " << endl;

    for (const auto &elm : ils) {
        cout << " " << elm;
    }
    cout << endl;
}

#include <cstdarg>
void chg_params_length(int pre, ...) {
    va_list args_ptr;
    int sum{0};
    int arg_num{0};
    sum += pre;

    va_start(args_ptr, pre);
    do {
        arg_num = va_arg(args_ptr, int);
        sum += arg_num;
    } while (arg_num != 0);

    va_end(args_ptr);
    std::cout << "sum is " << sum << std::endl;
}

int &get_val(int *array, int index) { return array[index]; }

void test_get_val(void) {
    int ap_tmp[10] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    for (int i = 0; i < 10; ++i) {
        get_val(ap_tmp, i) = i;
    }
    std::cout << "tmp ap values are: " << std::endl;
    for (auto &elm : ap_tmp) {
        std::cout << " " << elm;
    }
    std::cout << std::endl;
}

// ch6.3
// 声明一个返回数组指针的函数
// method 1
// int (*array_function1(int i))[5] {}
// using array_list = int[10];
// array_list* array_function(int i) {}

// method 2
// 使用尾置返回类型
// auto func(int i) -> int(*)[10]

// method 3
// 使用decltype，不负责把数组类型转为指针，因此需要*
// int odd[] = {1, 2, 3, 4, 5}
// decltype(odd) *func(int i) { return &odd; }
int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};
decltype(odd) *attr_ptr(int i) { return (i % 2) ? &odd : &even; }
void test_return_array_point(void) {
    int(*ap)[5] = attr_ptr(3);
    std::cout << "array point value are: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << " " << (*ap)[i];
    }
    std::cout << std::endl;
}

// test define
#define DO_IF(cond, do_expr) \
    if (cond) {              \
        do_expr;             \
    }

void test_do_if(void) {
    int a = 1;
    DO_IF(a, std::cout << "Yes, this is do_if!" << std::endl);
}

const string &shorter_string(const string &s1, const string &s2) { return s1.size() < s2.size() ? s1 : s2; }
string &shorter_string(string &s1, string &s2) {
    auto &r = shorter_string(const_cast<const string &>(s1), const_cast<const string &>(s2));
    return const_cast<string &>(r);
}

void test_shorter_string(void) {
    const string s1 = "thisisme";  // top-level const, ignore in shorter_string()
    const string s2 = "yeap";
    const string shorter = shorter_string(s1, s2);
    // shorter_string(s1, s2) = "hhhh"; // error
    std::cout << "The shorter string is: " << shorter << std::endl;

    string s3 = "no_const_string";
    string s4 = "this_is_no_const_string";
    string res = shorter_string(s3, s4);
    std::cout << "Non const string is " << res << std::endl;

    shorter_string(s3, s4) = "hhh";
    std::cout << "s3 = " << s3 << std::endl;  // s3 = "hhh"
    std::cout << "s4 = " << s4 << std::endl;
}

// ch6_7
using FUNC_TYPE = int(int, int);
// typedef int FUNC_TYPE(int, int);
using FUNC_PTR = int (*)(int, int);
// typedef int (*FUNC_PTR)(int, int);
inline int add_func(int a, int b) { return a + b; }
inline void func_type_example(int a, int b, FUNC_TYPE fn) { std::cout << "a + b = " << fn(a, b) << std::endl; }

void test_func_type(void) {
    std::cout << "test_func_type: " << std::endl;
    func_type_example(3, 4, add_func);
}

int main(int argc, char *argv[]) {
    // diff_pointarray_arraypoint();
    chg_params_length({"hello", "world", "This"});
    chg_params_length({"I", "am", "dragon", "what", "are", "you"});

    chg_params_length(1, 2, 3, 4, 5, 0);
    chg_params_length(9, 8, 7, 6, 5, 0);

    test_get_val();

    test_return_array_point();

    test_do_if();

    test_shorter_string();

    test_func_type();

    system("pause");
    return 0;
}