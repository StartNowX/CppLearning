#include <iostream>
#include <string>
#include <utility>

using namespace std;

/**
 * 头文件utility
 *      pair: 结构体模板，用于一个单元存储两个相异对象
 *          make_pair:
 *          swap/get
 *          std::tuple_size<std::pair>()/std::tuple_element<std::pair>()
 *
 * 头文件<tuple>
 *      tuple: 是std::pair的推广
 *          make_tuple:
 *          std::tuple_size<T>/std::tuple_element<T>
 *
 * 头文件<tuple>
 *      tie: 对tuple对象进行拆解，见TestTie
 *          ignore
 */

#include <tuple>
#include <typeinfo>
void TestPair() {
    std::pair<std::string, int> one_pair{"abc", 1};
    std::cout << "one_pair: " << one_pair.first << ", snd: " << one_pair.second << std::endl;
    cout << std::tuple_size<std::pair<std::string, int>>() << endl;  // 输出2
    std::tuple_element<0, std::pair<std::string, int>>::type first = std::get<0>(one_pair);
    std::tuple_element<1, std::pair<std::string, int>>::type snd = std::get<1>(one_pair);
    cout << "fst: " << first << ", snd = " << snd << endl;
    cout << "fst type: " << typeid(first).name() << ", snd type: " << typeid(snd).name() << endl;

    std::pair<std::string, std::string> pair2 = std::make_pair<std::string, std::string>("abcd", "is");
    std::cout << "pair2: " << pair2.first << ", snd: " << pair2.second << std::endl;

    auto tmp_tuple1 = std::make_tuple("abc", "is", 4, "cnt");
    cout << "size: " << std::tuple_size<decltype(tmp_tuple1)>::value << endl;  // 输出4
}

#include <map>
#include <set>
void TestTie() {
    std::tuple<std::string, std::string, int, double> a_tuple{"abc", "ef", 1, 2.0};

    std::string s1, s2;
    int i_a;
    double d_b;
    std::tie(s1, s2, i_a, d_b) = a_tuple;
    // auto [s1, s2, i_a, d_b] = a_tuple; // C++17
    cout << "s1: " << s1 << ", s2: " << s2 << ", i_a: " << i_a << ", d_b: " << d_b << endl;
    i_a = 4;
    std::tuple_element<2, std::tuple<std::string, std::string, int, double>>::type third = std::get<2>(a_tuple);
    cout << "3rd = " << third << endl;  // 还是1

    std::string s11;
    int aaa;
    std::tie(s11, ignore, aaa, ignore) = a_tuple;
    cout << "s11: " << s11 << ", aaa: " << aaa << endl;


    std::map<string, int> mmp;
    multimap<string, int>::iterator lower, upper;
    std::tie(lower, upper) = mmp.equal_range("four");

    // // C++17
    // auto [lower, upper] = mmp.equal_range("four");

    // // C++17
    // int a[2] = {1, 2};
    // auto [x, y] = a;
}

int main(int argc, char* argv[]) {
    // TestPair();

    TestTie();

    return 0;
}