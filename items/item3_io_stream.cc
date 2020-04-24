/**
 * iostream: 定义了用于读写流的基本类型， 类型：istream/wistream, ostream/wostream, iostream/wiostream
 * fstream: 定义了读写命名文件的基本类型，类型：ifstream/wifstream, ofstream/wofstream, fstream/wfstream
 * sstream：定义了读写内存string对象的类型, 类型：istringstream/wistringstream, ostringstream/wostringstream,
 *          stringstream/wstringstream
 *
 * fstream/sstream继承自iostream，对应的读写流继承自iostream的读写流
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * 管理缓冲区
 * 缓冲区一般有：全缓冲（填满才会执行，如磁盘的读写）、行缓冲（遇到换行符执行IO操作，如cin、cout）、无缓冲（如stderr）
 *
 * 刷新缓冲区的操作：
 *  1. endl
 *  2. flush
 *  3. 缓冲区满
 *  4. 关闭文件
 *  注意：程序异常终止时，不会刷新缓冲区
 */
#include <fstream>
void TestIoStream() {
    // IO对象不能拷贝和赋值，因此对IO拷贝时必须要以引用的方式传参或返回
    std::ofstream ofs1, ofs2;
    // ofs1 = ofs2;  // error

    std::string word;
    while ((cin >> word)) {
        // std::cout << word;
        cout << word << endl;
    }
}


/**
 * 文件IO读写，fstream（ifstream，ofstream）
 * 构造函数：fstream, fstream(filename), fstream(filename, mode)
 *
 * 打开文件时可能会失败，所以一般需要对open的结果进行判断，是否打开成功，也可以调用is_open()成员函数
 *
 * seekg/tellg: 用于ifstream
 * seekp/tellp: 用于ofstream
 *
 * seekg/seekp: 读、写指针的位置
 * seekg(offset)
 * seekg(offset, position): position可以为ios::beg, ios::end, ios::cur
 *
 * tellg/tellp: 返回当前读、写指针的位置，类型为streampos
 */
void TestFileIoStream() {
    if (true) {
        std::ofstream ofs1;
        ofs1.open("./file1.txt");  // 默认是ofstream::out
        std::ofstream ofs2("./file2.txt");

        // 写数据
        std::string str1 = "this1 is test";
        ofs2.write(str1.c_str(), str1.length());
        ofs2 << endl;

        ofs2 << "this11 is new test" << endl;

        ofs1.close();
        ofs2.close();

        std::ofstream ofs3("./file3.txt", std::ofstream::out);  // 指定为写
        std::fstream fs3("./file3_1.txt", std::ofstream::out | std::ofstream::binary);
        ofs3.close();
        fs3.close();

        // ofstream::app 写文件时才会定位到文件末尾
        std::ofstream ofs3_1("./file2.txt", std::ofstream::app);
        ofs3_1 << "this111 is another test" << endl;
        ofs3_1.close();

        std::string str2;
        std::ifstream ifs1("./file2.txt", std::ifstream::app);
        ifs1 >> str2;
        std::cout << "str2 = " << str2 << endl;  // 打印的是前面的this
        ifs1.close();

        std::string str3;
        // fstream::ate打开文件时就被定位到文件末尾了
        std::ifstream ifs2("./file2.txt", std::ifstream::ate);
        ifs2 >> str3;
        std::cout << "str3 = " << str3 << endl;  // 打印为空
        ifs2.close();
    }


    if (false) {
        std::string str1;
        std::ifstream ifs("./file2.txt");
        ifs.seekg(3);
        ifs >> str1;
        std::cout << "str1 = " << str1 << std::endl;

        ifs.seekg(3, ios::cur);  // ios::beg, ios::end, ios::cur
        str1.clear();
        ifs >> str1;
        std::cout << "str1 = " << str1 << std::endl;

        streampos begin = ifs.tellg();
        ifs.seekg(0, ios::end);
        streampos end = ifs.tellg();
        std::cout << "size is " << (end - begin) << std::endl;

        ifs.close();
    }

    if (true) {
        std::string str1;
        std::ofstream ofs("./file2.txt");
        streampos begin = ofs.tellp();

        ofs << "this is a new test";
        ofs.seekp(0, ios::end);
        streampos end = ofs.tellp();
        std::cout << "size - 4 = " << end - begin << std::endl;

        ofs.close();
    }
}


/**
 * 内存字符串读写，sstream(istringstream, ostringstream)
 *
 * 能够实现字符串和数字之间的转换，以及格式化字符串
 */
#include <iomanip>
#include <sstream>
#include <typeinfo>
void TestStringToStream() {
    istringstream iss("this is 007 file");
    std::string tmp_str;
    while (iss >> tmp_str) {
        std::cout << tmp_str << std::endl;
    }

    istringstream iss1("700");
    double i;
    iss1 >> i;
    std::cout << "i = " << i << ", type(i) = " << typeid(i).name() << std::endl;


    ostringstream oss;
    oss << "this is another 007....";
    // 数字转字符串，或者用std::to_string()
    oss << 300;
    std::cout << "oss: " << oss.str() << std::endl;

    // 格式化字符串
    ostringstream oss1;

    oss1 << showbase << hex << 256;
    std::cout << "oss1 = " << oss1.str() << std::endl;

    ostringstream oss2;
    double a = 123.44;
    oss2 << fixed << setprecision(5) << a;
    std::cout << "oss2 = " << oss2.str() << std::endl;
}

int main(int argc, char* argv[]) {
    // TestIoStream();

    // TestFileIoStream();

    TestStringToStream();

    return 0;
}