#include <iostream>


void TestEnum() {
    enum Color { RED, ORANGE = 20, BLUE };

    Color co = BLUE;
    std::cout << "co = " << co << std::endl;

    // co可以转换为a
    int a = co;
    std::cout << "a = " << a << std::endl;
}

// C++11
// enum class/struct 无区别
void TestEnumClass() {  //无作用域
    {                   /**
                         * 如此定义Color和ColorINT编译时，会报错，RED，ORANGE，BLUE认为重定义了
                         * 由此可见，无作用域的枚举类型，其枚举类型直接暴露在当前的作用域中了，
                         *
                         * enum Color { RED, ORANGE = 10, BLUE };
                         * enum ColorINT : int { RED, ORANGE, BLUE };
                         * enum ColorINT1 : int;
                         *
                         * */

        enum Color { RED, ORANGE = 10, BLUE };
        enum APPLE : int;  // 无作用域枚举，且不定义其枚举项，此时该类型是完整类型，长度已知

        Color a = RED;
        APPLE apple;
        std::cout << "apple = " << apple << std::endl;

        {
            // 无作用域的枚举类型，可以缺省类型名，该方式将所有的枚举项引入到外围的作用域中，如上所述
            enum { apple = 0, orange = 20, pear = 30 };
            std::cout << "apple = " << std::hex << std::showbase << apple << std::endl;
            std::cout << "orange = " << std::hex << std::showbase << orange << std::endl;
            std::cout << "pear = " << std::hex << std::showbase << pear << std::endl;
        }
    }

    // 有作用域，preferred
    {
        enum class Color { RED, ORANGE = 30, BLUE };

        // Color co = BLUE; // error
        Color co = Color::BLUE;
        // int a = co;                               // error, 不能从有作用域枚举到int转换
        // std::cout << "co = " << co << std::endl;  // error, co没法转为int

        // 可以用static_cast获取枚举变量的值
        int a = static_cast<int>(co);
        std::cout << "a = " << a << std::endl;
    }

    {
        enum class NUM16 : int16_t { A, B, C, D };  // 声明底层类型固定的枚举类型，只能是【某个整型类型】
        enum class NUM32 : int32_t { A, B, C, D };

        NUM16 n{NUM16::A};  // c11的列表初始化
    }
}


// union没区别
void TestUnion(void) {
    union FType {
        int16_t f_int16;
        int32_t f_int32;
        int64_t f_int64;
    };

    FType a;
    a.f_int16 = 23;
    std::cout << "16 = " << std::hex << std::showbase << a.f_int16 << std::endl;
    a.f_int32 = 24;
    std::cout << "16 = " << std::hex << std::showbase << a.f_int16 << std::endl;  // 24
    std::cout << "24 = " << std::hex << std::showbase << a.f_int32 << std::endl;  // 24

    // 可以用union来判断大小端口
}

int main(int argc, char* argv[]) {
    TestEnum();

    TestEnumClass();

    TestUnion();

    return 0;
}