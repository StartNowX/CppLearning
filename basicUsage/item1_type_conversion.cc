#include <iostream>

/**
 * 隐式类型转换
 * 普通数据类型的转换
 * 类类型的转换
 */
void ImplicitConversion(void) {
    {
        /**
         * 基础数据类型的隐式转换，不需要任何的显示声明，主要从低精度到高精度的转换，bool转为0或非0之类的
         * 对于非基本类型，如array或function可以隐式转为指针，指针支持如下的转换：
         *  1. 空指针可以转为任意类型的指针
         *  2. 任意类型的指针又都可以转为void指针
         *  3. 指针向上转换。即继承的子类指针可以在转为其可访问的基类指针，且不能改变基类const/volatile限定
         * */
        short a = 3;
        int b = a;
        std::cout << "b = " << b << std::endl;
    }

    {
        /**
         * 类中的隐式类型转换，主要有以下三种方式会导致类的隐式类型转换
         *  1. 单个参数的构造函数（只支持一次隐式转换）
         *  2. 赋值操作
         *  3. 类型转换操作
         * */
        class A {};

        class B {
           public:
            // 单个参数的构造函数，只有一次的隐式类型转换是OK的，一次以上就不行了
            B(const A& x) { std::cout << "aa" << std::endl; }
            // 赋值操作
            B& operator=(const A& x) {
                std::cout << "bb" << std::endl;
                return *this;
            }
            /**
             * 类型转换函数，其形式如下
             *  operator 类型名称() const {实现转换}
             * 即：必须是类的非静态成员函数，不能声明返回值类型，无形参
             */
            operator A() {
                std::cout << "cc" << std::endl;
                return A();
            }
        };

        {
            A foo;
            B bar = foo;  // 构造函数
            bar = foo;  // 赋值操作，bar已经构造过了，用foo对其赋值，注意和上面的初始化区分开来
            foo = bar;  // 类型转换
        }
    }
}

/**
 * explicit显示类型转换
 */

void ExplicitTypeConversion(void) {
    std::cout << "==== ExplicitTypeConversion ====" << std::endl;
    class A {};
    class B {
       public:
        //防止隐式类型转换
        explicit B(const A& x) { std::cout << "aa" << std::endl; }
        B& operator=(const A& x) {
            std::cout << "bb" << std::endl;
            return *this;
        }
        operator A() {
            std::cout << "cc" << std::endl;
            return A();
        }
    };
    {
        A foo;
        B bar(foo);
        bar = foo;
        foo = bar;

        // B bar1 = foo;  // compilier error
    }
}

/**
 * 类型强转
 * 基础类型
 * */
void TypeCastingFundamental(void) {
    std::cout << "==== TypeCastingFundamental ====" << std::endl;
    /**
     * 对于基础类型，有两种强转的方式，一个是functional的，一个是c-like的
     *
     * 但是，对于class或指针，这两种方式可以会导致运行时的错误，但是编译时是没问题的，参见上述隐式转换中指针支持的转换方式
     */
    double a = 3.145;
    int b = int(a);
    int c = (int)(a);
    std::cout << "b = " << b << ", c = " << c << std::endl;
}


void print(char* ptr) {
    std::cout << "ptr = " << ptr << std::endl;
    std::string ss = "this is non-const";
    ptr = const_cast<char*>(ss.c_str());
    std::cout << "ptr = " << ptr << std::endl;
}

/**
 * 类型强转
 *  static_cast<new type>(expression)
 *  dynamic_cast<new type>(expression)
 *  reinterpret_cast<new type>(expression)
 *  const_cast<new type>(expression)
 */
void TypeCastingSpecificalCasts(void) {
    {  // dynamic_cast
        std::cout << "==== dynamic_cast ====" << std::endl;
        class Base {
            virtual void dummy() {}
        };

        class Derived : public Base {
            int a;
        };
        /**
         * dynamic_cast<new type>(expression)
         *  1. 该类型转换只被用于类的指针或引用，目的是为了保证转换后的结果指向有效且完整的类型
         *  2. 该类型天然支持向上类型转换（子类转为基类）
         *  3. 同时也支持特定的向下类型转换（基类转为子类，只有具有多态性质的类才可以，且要转的类型是完整有效的）
         *  也即：该类型转换是类型安全的
         */
        Base* pda = new Base;
        Base* pdb = new Derived;
        Derived* pd;

        // 这里会运行时出错，因为pd是Derived类型的，而pda是Base类型，其实际运行时指向的也是Base基类，对于子类pd而言，pda是不完整的
        pd = dynamic_cast<Derived*>(pda);
        if (pd == nullptr) {
            std::cout << "error in a" << std::endl;
        }

        pd = dynamic_cast<Derived*>(pdb);
        if (pd == nullptr) {
            std::cout << "error in b" << std::endl;
        }
    }

    {
        // static_cast
        std::cout << "==== static_cast ====" << std::endl;
        class Base {};
        class Derived : public Base {};

        /**
         * static_cast类型转换支持类的指针之间的相互转化，upcast或downcast都可以，但是不会像dynamic_cast一样进行类型安全检查
         * 同时，static_cast支持所有隐式转换支持的操作
         *
         * 再者，static_cast支持如下的转换：
         *  1. 显式调用单个参数的构造函数或类型转换函数
         *  2. 转为右值引用
         *  3. 将enum class转为int，float等，反之也可以
         */
        Base* a = new Base;
        Derived* p;
        p = static_cast<Derived*>(a);  // 运行时不会有错，因为static_cast不会进行类型检查
        if (p == nullptr) {
            std::cout << "error in p" << std::endl;
        }
    }

    { /**
       * const_cast实现对一个指针类型的const属性的增加或删除，如将const指针转为non-const的形参
       *
       * 如果移除const后的指针会更改指针内容，则会产生undefined behavior
       */

        std::cout << "==== const_cast ====" << std::endl;

        const char* str = "this is const";
        print(const_cast<char*>(str));
    }


    {
        /**
         *  reinterpret_cast用于将任意类型的指针转为其他类型的指针，即便两者之间没有关联，因此不是类型安全的；同时，也支持指针和int类型之间的互转，其转换结果与平台相关
         *
         *  这个类型转换一般是用于低层代码，平时较少见到
         */
    }
}

/**
 * typeid，头文件<typeinfo>
 *
 * 用法：
 */
#include <typeinfo>
void TypeId() {
    class Base {
        virtual void a() {}
    };
    class Derived {};

    Base* pd = new Base;
    Derived* pdd = new Derived;
    std::cout << "pd type is " << typeid(pd).name() << std::endl;
    std::cout << "pdd type is " << typeid(pdd).name() << std::endl;
}


int main(int argc, char* argv[]) {
    ImplicitConversion();

    ExplicitTypeConversion();

    TypeCastingFundamental();

    TypeCastingSpecificalCasts();

    TypeId();

    return 0;
}
