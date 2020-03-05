#include <iostream>
#include <string>
#include <array>
#include <type_traits>

constexpr int factorial(int n) {
    return n <= 1 ? 1 : (n * factorial(n - 1));
}

class ConstExprStr {
    public:
      constexpr ConstExprStr(int s) : value_(s) {}
      constexpr int get_value() {
          return value_;
      }
    private:
      int value_;
};

int main(int argc, char* argv[]){
    std::cout << "begin factorial..." << std::endl;

    int n = 4;
    int res = factorial(4);
    //std::array<int, factorial(4)> arr1;
    //std::array<int, factorial(n)> arr2;
    std::cout << "is literal type: " << std::is_literal_type<int>::value << std::endl; 

    for(int i = 0; i < 5; ++i){
        std::cout << "index " << i << ", factorial res = " << factorial(i) << std::endl;
    }

    std::cout << "factorial res = " << res << std::endl;
    std::cout << "end factorial..." << std::endl;

    constexpr int x = 10;
    constexpr ConstExprStr conststr(x);
    std::cout << "ConstExprStr is literal type: " << std::is_literal_type<ConstExprStr>::value << std::endl;
    std::cout << "string is literal type: " << std::is_literal_type<std::string>::value << std::endl;

    std::array<int, conststr.get_value()> arr;
    std::cout << "name is " << conststr.get_value() << std::endl;

    return 0;
}
