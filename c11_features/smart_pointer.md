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


### weak_ptr
`weak_ptr`对`shared_ptr`管理的对象存在非拥有性（弱）引用，在访问所引用的对象前，需要将其转为`shared_ptr`；该指针表达的是临时所有权的概念，具体参考[https://zh.cppreference.com/w/cpp/memory/weak_ptr](https://zh.cppreference.com/w/cpp/memory/weak_ptr)

1. `weak_ptr`成员函数
    * `reset`
    * `swap`
    * `expired`: 检查weak_ptr对象是否被释放了，若被释放了，则返回true
    * `lock`: 若weak_ptr没有被expired，返回weak_ptr保存的shared_ptr信息；否则返回empty的share_ptr指针；这个接口用来锁定owned pointer，防止被release
    * `owner_before`
    * `use_count`