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
        std::cout << "value-based: " << (!(a.get() < b.get()) && !(b.get() < a.get())) << '\n';  // false, stored pointer
        std::cout << "value-based: " << (!(a < b) && !(b < a)) << '\n';  // false, stored pointer
        std::cout << "owner-based: " << (!a.owner_before(b) && !b.owner_before(a)) << '\n'; // true

        delete p;

        std::shared_ptr<int> p10(new int(5));
        std::shared_ptr<int> p11(new int(30));
        std::cout << "p10.get() = " << p10.get() << ", p11.get() = " << p11.get() << std::endl;
        std::cout << "p10.get() < p11.get() = " << (p10.get() < p11.get()) << std::endl; // false
        std::cout << "p10 < p1 = " << (p10 < p11) << std::endl; // false
        std::cout << "p10.owner_before(p11) = " << p10.owner_before(p11) << std::endl; // true
    }

    std::cout << std::endl;
}

void WeakPtr() { std::cout << std::endl; }

void UniquePtr() { std::cout << std::endl; }

int main(int argc, char *argv[]) {
    std::cout << "\n  ****** begin smart pointer ****** " << std::endl;

    std::cout << "1. shared_ptr" << std::endl;
    SharedPtr();

    // std::cout << "2. weak_ptr" << std::endl;
    // WeakPtr();

    // std::cout << "3. unique_ptr" << std::endl;
    // UniquePtr();

    std::cout << "\n  ****** end smart pointer ****** " << std::endl;

    return 0;
}
