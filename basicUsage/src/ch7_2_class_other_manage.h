#ifndef CH7_2_CLASS_OTHER_MANAGE_H_
#define CH7_2_CLASS_OTHER_MANAGE_H_

#include <iostream>
#include <string>
#include <vector>

class Screen;

class WindowMgr {
   public:
    using ScreenIndex = std::vector<Screen>::size_type;

   public:
    WindowMgr() = default;
    WindowMgr(int num);
    WindowMgr(int num, std::string name);
    WindowMgr(std::string name) : WindowMgr(0, name) {};

    ScreenIndex AddScreen(const Screen&);
    void print() const;
    void clear(ScreenIndex);

   private:
    //    WindowWgr此时仅仅有Screen的前向声明，并不知道该类的内部数据
    // std::vector<Screen> screens_{Screen(24, 80, ' ')};
    std::vector<Screen> screens_;
};

#endif