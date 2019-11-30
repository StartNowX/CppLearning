#ifndef CH7_2_CLASS_OTHER_H_
#define CH7_2_CLASS_OTHER_H_

#include <iostream>
#include <string>

#include "ch7_2_class_other_manage.h"

class Screen {
   public:
    // need to be declared here before using it
    // typedef std::string::size_type pos;
    using pos = std::string::size_type;

   public:
    // friend class WindowMgr;
    friend void WindowMgr::clear(ScreenIndex);  // 需要#include "ch7_2_class_other_manage.h"

   public:
    Screen() = default;
    Screen(pos ht, pos wd, char c) : height_(ht), width_(wd), contents_(ht * wd, c) {}

    char get_content() const { return contents_[cursor_]; }
    inline char get_content(pos ht, pos wd) const { return contents_[ht * width_ + wd]; }

    Screen &move(pos r, pos c);
    Screen &set(char ch);
    Screen &set(pos r, pos c, char ch);
    Screen &display(std::ostream &os) {
        std::cout << "calling non-const version..." << std::endl;
        do_display(os);
        return *this;
    }
    // must return const Screen
    const Screen &display(std::ostream &os) const {
        std::cout << "calling const version..." << std::endl;
        do_display(os);
        return *this;
    }

    void some_member() const { ++access_cptr_; }

   private:
    void do_display(std::ostream &os) const { os << contents_; }

   private:
    pos cursor_ = 0;
    pos height_ = 0, width_ = 0;
    std::string contents_;
    // mutable data member
    mutable size_t access_cptr_;
};

#endif