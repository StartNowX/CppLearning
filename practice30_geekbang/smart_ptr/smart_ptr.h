#pragma once

/**
 * 自定义一个智能指针，内部维护一个指针和引用计数的成员
 * 1. 构造/析构函数，构造时如果指针不为空，初始化引用计数的指针，析构时如果引用计数为空，释放内存
 * 2. 拷贝构造、移动构造
 * 3. 运算符重载
 *
 * 支持智能指针间的强制类型转换, 实现方式是将smart_ptr内部指针用C++的强制类型转换进行转换，然后封装成smart_ptr
 */

#include <utility>

#include "shared_count.h"

template <typename T>
class smart_ptr {
   public:
    // 为了支持不同模版参数的smart_ptr能够访问到彼此的私有成员
    template <typename U>
    friend class smart_ptr;

   public:
    // 默认构造函数，若ptr非空，需要初始化引用计数
    explicit smart_ptr(T* ptr = nullptr) : ptr_(ptr) {
        if (ptr) {
            shared_count_ptr_ = new shared_count();
        }
    }
    ~smart_ptr() {
        if (ptr_ && !shared_count_ptr_->reduce_count()) {
            delete ptr_;
            delete shared_count_ptr_;
        }
    }
    /**
     * 拷贝构造，模板参数类型相同时，需要增加引用计数(传参的类型的引用计数也需要增加计数)
     */
    smart_ptr(const smart_ptr& other) {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_ptr_->add_count();
            shared_count_ptr_ = other.shared_count_ptr_;
        }
    }

    /**
     * 拷贝构造，模板参数类型不同时
     */
    template <typename U>
    smart_ptr(const smart_ptr<U>& other) noexcept {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_ptr_->add_count();
            shared_count_ptr_ = other.shared_count_ptr_;
        }
    }

    /**
     * 移动构造，引用计数等于入参内部计数，且最后入参的指针为置为空
     */
    template <typename U>
    smart_ptr(smart_ptr<U>&& other) noexcept {
        ptr_ = other.ptr_;
        if (ptr_) {
            shared_count_ptr_ = other.shared_count_ptr_;
            other.ptr_ = nullptr;
        }
    }

    /**
     * 为了在类型转换时调用，支持对内部的指针对象赋值时，使用一个现有的只能指针的引用计数
     * 见dynamic_pointer_cast的实现
     */
    template <typename U>
    smart_ptr(const smart_ptr<U>& other, T* ptr) noexcept {
        ptr_ = ptr;
        if (ptr_) {
            other.shared_count_ptr_->add_count();
            shared_count_ptr_ = other.shared_count_ptr_;
        }
    }

    /**
     * 运算符重载: 赋值=, 解引用*, 成员访问->, 像普通指针一样用于布尔表达式
     * 重载赋值运算符，交换内部两个指针
     */
    smart_ptr& operator=(smart_ptr rhs) noexcept {
        rhs.swap(*this);
        return *this;
    }

    T& operator*() noexcept { return *ptr_; }
    T* operator->() noexcept { return ptr_; }
    operator bool() noexcept { return ptr_; }


    long use_count() const noexcept {
        // if (ptr_) {
        //     return shared_count_ptr_->get_count();
        // } else {
        //     return 0;
        // }
        return ptr_ ? shared_count_ptr_->get_count() : 0;  // 重载了bool类型
    }

    inline T* get() const noexcept { return ptr_; }

   private:
    void swap(smart_ptr& rhs) noexcept {
        using std::swap;
        swap(ptr_, rhs.ptr_);
        swap(shared_count_ptr_, rhs.shared_count_ptr_);
    }

   private:
    T* ptr_;                          // 内部维护一个指针
    shared_count* shared_count_ptr_;  // 内部维护一个引用计数的类
};

template <typename T>
void swap(smart_ptr<T>& lhs, smart_ptr<T>& rhs) {
    lhs.swap(rhs);
}

template <typename T, typename U>
smart_ptr<T> static_pointer_cast(const smart_ptr<U>& other) {
    T* ptr = static_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> reinterpret_pointer_cast(const smart_ptr<U>& other) {
    T* ptr = reinterpret_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> const_pointer_cast(const smart_ptr<U>& other) {
    T* ptr = const_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(const smart_ptr<U>& other) {
    T* ptr = dynamic_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}
