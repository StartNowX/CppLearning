#include "ch7_2_class_other_manage.h"

#include "ch7_2_class_other.h"

WindowMgr::WindowMgr(int init_screen_num) {
    std::vector<Screen> tmp_screen(init_screen_num, Screen(40, 20, 'c'));
    screens_ = tmp_screen;
    std::cout << "init screens_ size = " << screens_.size() << std::endl;
}

// return type need class name(out of slope of class WindowMgr)
WindowMgr::ScreenIndex WindowMgr::AddScreen(const Screen& scr){
    screens_.emplace_back(scr);
    return screens_.size() - 1;
}

void WindowMgr::print() const {
    if (0 == screens_.size()) {
        return;
    }
    int i{0};
    for (auto &screen : screens_) {
        // screen.display(std::cout);
        std::cout << "index: " << ++i << " " << screen.get_content(20, 10) << std::endl;
    }
}

void WindowMgr::clear(ScreenIndex i) {
    Screen &s = screens_[i];
    s.contents_ = std::string(s.height_ * s.width_, ' ');
}