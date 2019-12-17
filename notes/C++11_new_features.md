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


----
参考资料
1. https://docs.microsoft.com/en-us/cpp/cpp/constexpr-cpp?view=vs-2019
2. https://www.zhihu.com/question/35614219
3. https://zh.cppreference.com/w/cpp/language/constexpr

## lambda表达式

### 声明lambda表达式
Lambda表达式的完整声明方式如下
```C++
// mutable指示符标示是否可以用来修改捕获的变量
// exception设定异常
[capture list](params list) mutable exception -> return type {function body}
```
几种简易的“不完整”的lambda表达式，如下：
```C++
[capture list](params list) -> return type {function body}
[capture list](params list) {function body}
[capture list] {function body}
```

### 捕获方式
lambda通过`[]`明确指明其内部可以访问的外部变量
1. `[]`：不捕获任何外部变量
2. `[variable]`：根据变量variable的名字以值的形式捕获变量
3. `[=]`：以值的方式捕获所有外部变量
4. `[&]`：以引用的方式捕获所有外部变量
5. `[=, &x]`：以引用的方式捕获x，以值的方式捕获其余的所有外部变量
    * `[&, =]`是错误的
6. `[&, x]`：以值的方式捕获x，以引用的方式捕获其余的所有外部变量
7. `[this]`：捕获lambda所在类的this指针（复制指针），lambda表达式拥有和当前类成员同样的访问权限
8. `[*this]`：通过传值的方式捕获当前对象

### lambda表达式的类型
C++11将lambda表达式的类型称为**闭包类型（closure type）**，是一个带有`operator()`的类，可以使用`std::function`和`std::bind`存储和操作lambda表达式

### lambda的新特性
C++14以后lambda表达式可以捕获表达式，参考[https://www.jianshu.com/p/d686ad9de817](https://www.jianshu.com/p/d686ad9de817)

### lambda与普通函数的区别
1. lambda函数不能有默认参数
2. lambda函数不支持可变参数
3. lambda函数的所有参数必须有参数名


遗留问题：
1. 如何理解C++中的闭包（closure）？