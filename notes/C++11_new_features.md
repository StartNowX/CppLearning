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


## 智能指针

### shared_ptr
`shared_ptr`提供了一个有限的内存回收机制，同时能够保证多个对象共享指针；一个`shared_ptr`由如下两部分组成：
* a stored pointer，也即指针所指向的内存，可以用`*`解引用，该指针可以用`shared_ptr::get()`成员函数获得
* a owned pointer, 可以理解为指向控制块，会控制该指针的生存周期
通常，这两个指针都是同一个对象，但也有例外，如`alias shared_ptr object`

1. `shared_ptr`的创建方式
    * 构造函数：有多种构造函数的方式，注意不同构造函数引起的引用计数的变化。参见[http://www.cplusplus.com/reference/memory/shared_ptr/shared_ptr/](http://www.cplusplus.com/reference/memory/shared_ptr/shared_ptr/)
    * 构造函数的初始化方式中，注意使用alias shared_ptr的不同，主要是其`stored pointer`和`owned pointer`的不同
    * `std::make_shared`函数模版，如:
        ```C++
        std::shared_ptr<int> p_make = std::make_shared<int>(3);
        // same as the following
        std::shared_ptr<int> p_make(new int(10));
        ```
    * empty的shared_ptr（不拥有任何指针对象）和null的shared_ptr（指针不指向任何对象）是不一样的，不过两者的`use_count`都是0
    * **shared_ptr只能通过拷贝值来共享其对指针的所有权，如果两个shared_ptr都是用同一个非share_ptr指针构造的，那么，这两个shared_ptr都拥有这个指针，但是并不共享**，这会导致当某一个shared_ptr释放时，另一个shared_ptr指向的就是一个无效的地址来

2. `shared_ptr`的访问方式
    * 等同于普通指针的解引用方式，`*`或`->`

3. `shared_ptr`的赋值方式
    * 赋值操作
    * 显示调用`shared_ptr::reset`
        * 若调用`reset`时空参，则指针变为empty，不能再进行解引用，use_count变为0
        * 若调用`reset`时传参为指针时，this pointer should not be already managed by any other managed pointer.
    * `swap`成员函数或非成员函数版本的`swap`函数交换两个shared_ptr指针，其管理的对象的控制权也同步更改（不会更改对象本身的use count，即两个指针调用`use_count`时结果也换了）

4. `shared_ptr`其他成员函数
    * `get()`：获取shared_ptr的stored pointer，当shared_ptr是alias时，stored pointer和owned pointer不同
    * `swap()`
    * `reset()`
    * `use_count()`
    * `unique()`：判断shared_ptr是否和其他对象共享指针，是则返回false，不是返回true；empty的shared_ptr永远是返回false；其结果等同于`use_count()==1`
    * `owner_before`: owner-based ordering，考虑的是shared_ptr的owner pointer，区别于`<`(比较的是stored pointer，即shared_ptr::get()的结果)，该部分需要再消化一下


### unique_ptr
`unique_ptr`指针和`shared_ptr`很像，只是`unique_ptr`指针不像`shared_ptr`指针可以共享其对象，其独占自己的对象。通常一个`unique_ptr`指针对象由如下两部分组成：
* `a stored pointer`：指向指针管理的对象，同样可以通过赋值操作和`reset`函数改变，可以通过`get`和`release`进行访问
* `a stored deleter`：一个用与`a stored pointer`相同类型的指针作为参数的可调用对象，用来删除其管理的对象，可以通过赋值操作更改，同样可以通过`get_deleter`进行访问

1. `unique_ptr`的创建方式
    * `unique_ptr`的创建很像`shared_ptr`，但是没有alias的方式
    * `unique_ptr`移除了拷贝构造

2. `unique_ptr`的赋值方式
    * 解引用配合赋值操作
    * `reset`成员函数
    * `swap`成员函数

2. `unique_ptr`的成员函数
    * `reset`: 同`shared_ptr`
    * `release`: 返回`unique_ptr`中的stored pointer，即返回的是一个指针，和`unique_ptr`给定的模版参数类型一致，同时用nullptr替换该`unique_ptr`指针
    * `get`: 返回stored pointer，可以对其解引用，获得`unique_ptr`的值，但是并没有释放对其对象的所有权，注意和`release`区别
    * `get_deleter`: 返回可调用对象stored deleter，当`unique_ptr`被销毁、赋新的值或者执行`reset`时，会调用stored deleter删除其管理的对象

---
参考资料[官方链接](http://www.cplusplus.com/reference/memory/unique_ptr/)