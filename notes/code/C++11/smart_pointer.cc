#include <iostream>
#include <memory>


void SharedPtr() {
    // create shared_ptr
    {
        // default construct
        std::shared_ptr<int> p1;
        std::shared_ptr<int> p2(nullptr);

        // construct from pointer
        std::shared_ptr<int> p3(new int);
        // construct from pointer + deleter
        // the object also take ownership of deleter
        std::shared_ptr<int> p4(new int, std::default_delete<int>());
        // construct from pointer + deleter + allocator
        // same as p4, but any memory needed for internal use is allocated by alloc
        std::shared_ptr<int> p5(new int, [](int *p) { delete p; }, std::allocator<int>());
        // copy constructor
        // if x is not empty, share the ownership, increase use_count
        std::shared_ptr<int> p6(p5);
        // move constructor, p6 become an empty object
        std::shared_ptr<int> p7(std::move(p6));
        // move from other types of managed pointer
        std::shared_ptr<int> p8(std::unique_ptr<int>(new int));

        // aliasing constructor
        // the stored pointer and the owned pointer point to different objects here.
        struct C {
            int *data;
        };
        std::shared_ptr<C> obj(new C);
        // p9不拥有obj->data的控制权,
        std::shared_ptr<int> p9(obj, obj->data);
        delete obj->data;

        std::cout << "p1.use_count() = " << p1.use_count() << std::endl;  // 0
        std::cout << "p1.use_count() = " << p2.use_count() << std::endl;  // 0
        std::cout << "p3.use_count() = " << p3.use_count() << std::endl;  // 1
        std::cout << "p4.use_count() = " << p4.use_count() << std::endl;  // 1
        std::cout << "p5.use_count() = " << p5.use_count() << std::endl;  // 1, when p6 define, change to 2
        std::cout << "p6.use_count() = " << p6.use_count()
                  << std::endl;  // 2, share with p5, when p7 define, change to 0
        std::cout << "p7.use_count() = " << p7.use_count() << std::endl;    // 2,
        std::cout << "p8.use_count() = " << p8.use_count() << std::endl;    // 1,
        std::cout << "obj.use_count() = " << obj.use_count() << std::endl;  // 1, when p9 define, change to 2
        std::cout << "p9.use_count() = " << p9.use_count() << std::endl;    // 2,
    }

    // make_shared
    {
        std::shared_ptr<int> p_make = std::make_shared<int>(3);
        // same as the following
        // std::shared_ptr<int> p_make(new int(10));
        std::cout << "p_make = " << *p_make << ", p_make.use_count() = " << p_make.use_count() << std::endl;
    }

    // change shared_ptr
    {
        std::shared_ptr<int> sha_ja;
        std::shared_ptr<int> sha_ma(new int(10));
        std::shared_ptr<int> sha_tm;

        // copy
        sha_ja = sha_ma;
        std::cout << "*sha_ja = " << (*sha_ja) << ", sha_ja.use_count() = " << sha_ja.use_count() << std::endl;

        // move
        sha_tm = std::make_shared<int>(10);
        std::cout << "*sha_tm = " << (*sha_tm) << ", sha_tm.use_count() = " << sha_tm.use_count() << std::endl;

        // reset
        // become empty, can't be dereference
        sha_ja.reset();
        std::cout << "sha_ja.use_count() = " << sha_ja.use_count() << std::endl;
        // std::cout << "*sha_tm = " << (*sha_tm) << ", sha_tm.use_count() = " << sha_tm.use_count() << std::endl;

        sha_ja.reset(new int(20));
        std::cout << "sha_ja.use_count() = " << sha_ja.use_count() << ", *sha_ja = " << *sha_ja << std::endl;

        std::shared_ptr<int> sha_wn;
        std::shared_ptr<int> sha_mn(new int(20));
        sha_wn = sha_mn;
        std::cout << "*sha_wn = " << (*sha_wn) << ", sha_wn.use_count() = " << sha_wn.use_count()
                  << ", sha_mn.use_count() = " << sha_mn.use_count() << std::endl;

        std::shared_ptr<int> sha_swap(new int(4));
        // sha_swap.swap(sha_wn);
        std::swap(sha_swap, sha_wn);
        std::cout << "*sha_swap = " << (*sha_swap) << ", sha_swap.use_count() = " << sha_swap.use_count() << std::endl;
        std::cout << "*sha_wn = " << (*sha_wn) << ", sha_wn.use_count() = " << sha_wn.use_count() << std::endl;
    }

    // member function
    {
        std::shared_ptr<double> mm(new double(34.57));
        double *mm_ptr = mm.get();
        std::cout << "*mm = " << *mm << ", *mm_ptr = " << *mm_ptr << ", *mm.get() = " << *mm.get() << std::endl;
        std::cout << "mm.get() = " << mm.get() << std::endl;
    }

    {
        std::shared_ptr<float> uni_tmp1;
        std::shared_ptr<float> uni_tmp2(new float(3.14));
        std::cout << "uniq: \n" << std::boolalpha;
        std::cout << "1: " << uni_tmp1.unique() << std::endl;  // false, empty
        std::cout << "1: " << uni_tmp2.unique() << std::endl;  // true

        uni_tmp1 = uni_tmp2;
        std::cout << "1: " << uni_tmp1.unique() << std::endl;  // false
        std::cout << "1: " << uni_tmp2.unique() << std::endl;  // false

        uni_tmp1 = nullptr;
        std::cout << "1: " << uni_tmp1.unique() << std::endl;  // false
        std::cout << "1: " << uni_tmp2.unique() << std::endl;  // true, uni_tmp1置为空了
    }

    {
        int *p = new int(10);

        std::shared_ptr<int> a(new int(20));
        std::shared_ptr<int> b(a, p);  // alias constructor

        std::cout << "*a = " << *a << ", *b = " << *b << std::endl;  // 20 10
        std::cout << "a.get() = " << a.get() << ", b.get() = " << b.get() << std::endl;
        std::cout << "comparing a and b...\n" << std::boolalpha;
        std::cout << "value-based: " << (!(a.get() < b.get()) && !(b.get() < a.get()))
                  << '\n';                                                                   // false, stored pointer
        std::cout << "value-based: " << (!(a < b) && !(b < a)) << '\n';                      // false, stored pointer
        std::cout << "owner-based: " << (!a.owner_before(b) && !b.owner_before(a)) << '\n';  // true

        delete p;

        std::shared_ptr<int> p10(new int(5));
        std::shared_ptr<int> p11(new int(30));
        std::cout << "p10.get() = " << p10.get() << ", p11.get() = " << p11.get() << std::endl;
        std::cout << "p10.get() < p11.get() = " << (p10.get() < p11.get()) << std::endl;  // false
        std::cout << "p10 < p1 = " << (p10 < p11) << std::endl;                           // false
        std::cout << "p10.owner_before(p11) = " << p10.owner_before(p11) << std::endl;    // true
    }

    std::cout << std::endl;
}

void WeakPtr() { std::cout << std::endl; }


class StateDeleter {
   public:
    StateDeleter() : count_(0) {}
    template <typename T>
    void operator()(T *p) {
        std::cout << "[deleted #" << ++count_ << "]" << std::endl;
        delete p;
    }

   private:
    int count_;
};

void UniquePtr() {
    // initialize
    {
        std::default_delete<int> ud;
        std::unique_ptr<int> u1;
        std::unique_ptr<int> u2(nullptr);
        std::unique_ptr<int> u3(new int);
        std::unique_ptr<int> u4(new int(3), ud);
        std::unique_ptr<int> u5(new int(3), std::default_delete<int>());
        std::unique_ptr<int> u6(std::move(u5));
        std::unique_ptr<int> u7(std::move(u6));
        // std::unique_ptr<int> u8(std::auto_ptr<int>(new int)); // auto_ptr is deprecated
        // std::unique_ptr<int> u9 = u1; // error, unique_ptr delete copy construction

        std::cout << "u1: " << (u1 ? "not null" : "null") << std::endl;  // null
        std::cout << "u2: " << (u2 ? "not null" : "null") << std::endl;  // null
        std::cout << "u3: " << (u3 ? "not null" : "null") << std::endl;  // not null
        std::cout << "u4: " << (u4 ? "not null" : "null") << std::endl;  // not null
        std::cout << "u5: " << (u5 ? "not null" : "null") << std::endl;  // not null, when u6, null
        std::cout << "u6: " << (u6 ? "not null" : "null") << std::endl;  // not null, when u7, null
        std::cout << "u7: " << (u7 ? "not null" : "null") << std::endl;  // not null
        // std::cout << "u8: " << (u8 ? "not null" : "null") << std::endl; // not null
    }

    // assign
    {
        // reset
        std::unique_ptr<int> u1;
        std::unique_ptr<int> u2(new int);
        std::cout << "u2: " << (u2 ? "not null" : "null") << std::endl;  // not null
        u2.reset();
        std::cout << "u2: " << (u2 ? "not null" : "null") << std::endl;  // null

        u2.reset(new int(2));
        std::cout << "u2: " << (u2 ? "not null" : "null") << std::endl;  // not null

        // release
        std::unique_ptr<int> u3(new int(3));
        if (u3) {
            std::cout << "*u3 = " << *u3 << std::endl;
        } else {
            std::cout << "u3 is null." << std::endl;
        }

        int *tmp = u3.release();  // return value and reset u3 with nullptr
        if (u3) {
            std::cout << "*u3 = " << *u3 << std::endl;
        } else {
            std::cout << "u3 is null." << std::endl;
            std::cout << "*tmp = " << *tmp << std::endl;
        }
        delete tmp;

        // swap
        std::unique_ptr<int> u4;
        // std::unique_ptr<int> u4(new int(2));
        std::unique_ptr<int> u5(new int(5));
        u5.swap(u4);
        if (u5) {
            std::cout << "*u5 = " << *u5 << std::endl;
        }
        if (u4) {
            std::cout << "*u4 = " << *u4 << std::endl;
        }
    }

    // get()
    {
        std::unique_ptr<int> u1(new int(10));
        auto *auto_u1 = u1.get();
        std::cout << "*auto_u1 = " << *auto_u1 << ", *u1 = " << *u1 << std::endl;

        // 区分get()和release()，get()只是返回其stored
        // pointer，但不释放对其对象的所有权，即调用get()后，原始unique_ptr仍不为空，且返回值不能用于构造其他管理指针
        // release()则会释放对其对象的所有权
    }

    // get_deleter
    {
        // default deleter
        std::unique_ptr<int> u1;

        // alpha/beta use independent copies of the deleter
        std::unique_ptr<int, StateDeleter> alpha(new int);
        std::unique_ptr<int, StateDeleter> beta(new int, alpha.get_deleter());
        // if stop here, alpha/beta will call their deconstructor function, print:
        // [deleted #1]
        // [deleted #1]

        StateDeleter del;
        // deleter type is reference, thus gamma/delta share the deleter "del"
        std::unique_ptr<int, StateDeleter &> gamma(new int, del);
        std::unique_ptr<int, StateDeleter &> delta(new int, gamma.get_deleter());

        std::cout << "calling reset alpha...";
        alpha.reset(new int);
        std::cout << "calling reset beta...";
        beta.reset(new int);
        std::cout << "calling reset gamma...";
        gamma.reset(new int);
        std::cout << "calling reset delta...";
        delta.reset(new int);
        // if stop here, alpha/beta will also call their deconstructor function, print:
        // calling reset alpha...[deleted #1]
        // calling reset beta...[deleted #1]
        // calling reset gamma...[deleted #1]
        // calling reset delta...[deleted #2] // 注意这里+1，因为delta和gamma共享deleter
        // [deleted #3]
        // [deleted #4]
        // [deleted #2]
        // [deleted #2]

        std::cout << "calling gamma/delta deleter...";
        gamma.get_deleter()(new int);

        // a brand new deleter for alpha
        alpha.get_deleter() = StateDeleter();
    }

    {
        std::cout << "shared deleter " << std::endl;
        std::shared_ptr<int> sp1(new int(5), StateDeleter());
        sp1 = std::make_shared<int>(3); // 同样会调用自定义的deleter
    }

    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    std::cout << "\n  ****** begin smart pointer ****** " << std::endl;

    // std::cout << "1. shared_ptr" << std::endl;
    // SharedPtr();

    // std::cout << "2. weak_ptr" << std::endl;
    // WeakPtr();

    std::cout << "3. unique_ptr" << std::endl;
    UniquePtr();

    std::cout << "\n  ****** end smart pointer ****** " << std::endl;

    return 0;
}
