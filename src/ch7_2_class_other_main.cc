#include <iostream>
#include <string>

#include "ch7_2_class_other.h"


using namespace std;

int main(int argc, char* argv[]) {
    Screen screen;
    const Screen screen_const(80, 40, 'd');
    Screen temp_screen;
    char tmp_c = screen_const.get_content();
    cout << "tmp_c = " << tmp_c << std::endl;

    temp_screen.display(cout);
    screen_const.display(cout);

    temp_screen.move(5, 7).set('#');
    cout << "temp_screen(5, 7) = " << temp_screen.get_content(5, 7) << std::endl;

    screen.set(8, 4, 'e');
    cout << "screen(8, 4) = " << screen.get_content(8, 4) << std::endl;

    WindowMgr wind_mgr(3);
    wind_mgr.print();
    wind_mgr.clear(2);
    wind_mgr.print();

    return 0;
}