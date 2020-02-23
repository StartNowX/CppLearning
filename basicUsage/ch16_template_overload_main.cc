/**
 * 定义一组函数模板及非模板的重载版本
 * 该函数将返回一个给定对象的string表示
 */

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// 通用版本
template <typename T>
string debug_rep(const T& t) {
    cout << "[debug_rep] template ver1" << endl;
    ostringstream ret;
    ret << t;
    return ret.str();
}

// 指针版本
template <typename T>
string debug_rep(T* p) {
    cout << "[debug_rep] template ver2" << endl;
    ostringstream ret;
    ret << "pointer: " << p;
    if (p) {
        ret << " " << debug_rep(*p);
    } else {
        ret << " null pointer.";
    }
    return ret.str();
}

// 打印带有双引号的string
string debug_rep(const string& s) {
    cout << "[debug_rep] non-template ver1" << endl;
    return '"' + s + '"';
}

// 处理字符指针
string debug_rep(char* p) {
    cout << "[debug_rep] non-const char ver1" << endl;
    return debug_rep(string(p));
}

// 底层const重载
string debug_rep(const char* p) {
    cout << "[debug_rep] const char ver1" << endl;
    return debug_rep(string(p));
}

void TestTemplateOverload() {
    if (false) {
        string s("hi");
        // 只有template ver1版本可行，第二个版本需要的是指针
        cout << debug_rep(s) << endl;

        // template ver1和ver2两个模板都行
        // ver1中，T被推断为string*, 需要从普通指针到const指针的转换
        // ver2中，T被推断为string，匹配更为精准
        cout << debug_rep(&s) << endl;

        // template ver1和ver2两个模板都行
        // ver1中，debug_rep(const string*&), T被绑定到string*上
        // ver2中，debug_rep(const string*), T被绑定到string上
        // 两个版本都是精准匹配，绑定到ver2上，因为ver2是更特例化的版本
        const string* sp = &s;
        cout << debug_rep(sp) << endl;
    }

    if (false) {
        string s("hello");
        // 可行函数，
        // debug_rep<string>(const string&)
        // debug_rep(const string &)，非模板被选
        cout << debug_rep(s) << endl;
    }

    if (false) {
        // 三个函数皆都可行
        // debug_rep(const T&), T绑定到char[10]
        // debug_rep(T*), T绑定到const char，更特例化，被选中
        // debug_rep(const string&), 要求const char*到string的类型转换
        cout << debug_rep("hello world") << endl;
    }

    if (true) {
        // 如果没有debug_rep(const string&)的声明，将调用debug_rep<string>(const string&)
        cout << debug_rep("hello world") << endl;
    }

    return;
}


int main(int argc, char* argv[]) {
    TestTemplateOverload();

    return 0;
}