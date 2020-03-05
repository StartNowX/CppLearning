#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <functional> // std::function std::bind

int cmp(int a, int b) {
    return a < b;
}

void UsageLambda() {
    int global_a = 10;
    int global_b = 12;

    // auto func = []{std::cout << "global_a = " << global_a << std::endl;}; // [] don't capture variable, compiler error
    // auto func = [=]{std::cout << "global_a = " << global_a << std::endl;}; // OK, but cann't modify global_a
    // auto func = [&] { std::cout << "global_a = " << ++global_a << std::endl; }; // OK, reference
    // auto func = [global_a] ()mutable { std::cout << "global_a = " << ++global_a << std::endl; }; // OK, mutable means the variable can be modified
    // auto func = [global_a] { std::cout << "global_a = " << global_a << std::endl; }; // OK, reference
    // auto func = [&global_a, global_b](int local_a) { global_a = (local_a > global_b); }; // OK

    auto func = [=, &global_a](int local_a) { global_a = (local_a > global_b); }; // OK
    // auto func = [&global_a, =](int local_a) { global_a = (local_a > global_b); }; // Error

    func(2);
    std::cout << "global_a = " << global_a << ", global_b = " << global_b << std::endl;

    std::function<int (int, int)> func_t = [](int a, int b) { return a + b; };
    std::cout << "func_t(3, 2) = " << func_t(3, 2) << std::endl;

    std::function<int (int, int)> func_t_bind = std::bind([](int a, int b) { return a * b;}, std::placeholders::_1, std::placeholders::_2);
    std::cout << "func_t(4, 5) = " << func_t_bind(4, 5) << std::endl;
}

int main(int argc, char *argv[]) {

    std::vector<int> vec_list{1, 20, 3, 90, 2, 4, 15};
    // std::sort(vec_list.begin(), vec_list.end(), cmp);
    std::sort(vec_list.begin(), vec_list.end(), [](int a, int b) { return a < b; });

    std::cout << "vec list: ";
    for (auto it : vec_list)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    UsageLambda();

    return 0;
}
