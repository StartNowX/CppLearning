#include "ch7_2_class_other.h"

// can declared as inline here
Screen &Screen::move(pos r, pos c) {
    pos row = r * width_;
    cursor_ = row + c;
    return *this;
}

Screen &Screen::set(char c) {
    contents_[cursor_] = c;
    return *this;
}

Screen &Screen::set(pos ht, pos wd, char c) {
    contents_[ht * width_ + wd] = c;
    return *this;
}
