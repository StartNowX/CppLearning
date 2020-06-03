#pragma once

// 实现引用计数
class shared_count {
   public:
    shared_count() noexcept : count_(1) {}

    inline void add_count() noexcept { count_++; }
    inline long reduce_count() noexcept { return --count_; }
    inline long get_count() const noexcept { return count_; }

   private:
    long count_;
};