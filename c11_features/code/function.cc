
#include <functional>
#include <iostream>

// std::function类模版原型，其中R为返回值类型，Args为参数，
// template< class R, class... Args >
// class function<R(Args...)>;

// std::function 的实例能存储、复制及调用任何可调用(Callable) 目标——函数、 lambda 表达式、 bind
//     表达式或其他函数对象，还有指向成员函数指针和指向数据成员指针
// 相当于函数回调，在std::function<T>中指定返回值类型和参数类型

struct Foo {
    Foo(int num) : num_(num) {}
    inline void print_add(int i) const { std::cout << num_ + i << std::endl; }
    int num_;
};

void print_num(int i) { std::cout << i << std::endl; }

struct PrintNum {
    void operator()(int i) const { std::cout << i << std::endl; }
};

void TestCase(void) {
    // 存储自由函数
    std::function<void(int)> f_display = print_num;
    f_display(5);

    // 存储lambda
    std::function<void(void)> f_lambda = []() { print_num(30); };
    f_lambda();

    // 存储bind表达式
    std::function<void(void)> f_bind = std::bind(print_num, 5232);
    f_bind();

    // 存储成员函数的调用
    std::function<void(const Foo&, int)> f_cls_add = &Foo::print_add;
    const Foo foo(1234);
    f_cls_add(foo, 3);
    f_cls_add(3452, 1);

    // 存储数据成员的调用
    std::function<int(Foo const&)> f_num = &Foo::num_;
    const Foo foo1(89);
    std::cout << "foo num is " << f_num(foo1) << std::endl;

    // 存储成员函数及对象的调用
    using std::placeholders::_1;
    std::function<void(int)> f_cls_method = std::bind(&Foo::print_add, foo, _1);
    // 10为_1所绑定
    f_cls_method(10);

    // 存储成员函数和对象指针的调用
    std::function<void(int)> f_cls_method2 = std::bind(&Foo::print_add, &foo, _1);
    // 30为_1所绑定
    f_cls_method2(30);

    // 存储函数对象的调用
    std::function<void(int)> f_cls_obj = PrintNum();
    f_cls_obj(1313455);
}

void BadCase(void) {
    // 当结果类型为引用的 std::function 从无尾随返回类型的 lambda 表达式初始化时需要留心。由于 auto 推导的起效方式，这种
    // lambda 表达式将始终返回纯右值。故而结果引用将始终绑定到生命期在 std::function::operator() 返回时结束的临时量
    std::function<const int&()> F([]() { return 32; });
    int x = F();  // 未定义行为，segmentation fault
}
int main(int argc, char* argv[]) {
    TestCase();

    BadCase();

    return 0;
}