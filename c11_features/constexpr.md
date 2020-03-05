New features about C++11

## constexpr关键字
`constexpr`是C++11开始新增的特性，限定在**编译时期**的常量。

关于该特性，主要有如下的关注点：
1. 修饰变量时，变量用字面类型常量初始化时，可以声明为`constexpr`；若变量用构造函数初始化，且构造函数也声明为`constexpr`，则该变量可以声明为`constexpr`；
2. 修饰函数时，其返回值不一定是编译期常量。当传参是`constexpr`值，则返回的是编译期的常量；若传参不是`constexpr`值，则和普通函数没有区别，返回的同样是运行时的值
    * 注意C++11（只能有一个return）和C++14对函数体的要求的区别
    * 关于类
        * 构造函数如果声明为方式`constexpr`，其必须有一个空函数体，即成员函数初始化全部用列表初始化的方式
        * 构造函数如果声明为方式`constexpr`，
        * 一个类如果要实例化为`constexpr`，其需要调用的成员函数必须声明为`constexpr`
    * 可以使用std::array必须编译期常量才能编译通过来确认函数的返回值是不是编译期常量，见[参考资料2](https://www.zhihu.com/question/35614219)
3. 注意区分`const`和`constexpr`
