## lambda表达式

### 声明lambda表达式
Lambda表达式的完整声明方式如下
```C++
// mutable指示符标示是否可以用来修改捕获的变量
// exception设定异常
[capture list](params list) mutable exception -> return type {function body}
```

* 每一个Lambda表达式都有一个全局唯一的类型，要精准捕捉lambda表达式到一个变量中，**只能通过auto声明的方式**

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

一般不推荐默认捕获符，同时也一般鼓励采用按值捕获的方式，除非有以下条件：
1. 需要在lambda表达式中修改这个变量并让外部观察到
2. 需要看到这个变量在外部被修改的结果
3. 这个变量的复制代价比较高

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
