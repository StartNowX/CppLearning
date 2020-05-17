#include <iostream>
#include <set>

using namespace std;

/**
 * set和multiset都是默认排序好的，用std::less，set是单键值，multiset是多键值
 *
 * map和multimap是键值对容器，前者是键值的元素是唯一的，后者可以是多个
 *
 * set/multiset/map/multimap都是用红黑树实现的
 *
 * unordered_set/unordered_multiset/unordered_map/unordered_multimap都是用hash-table实现的
 *
 * 常用的接口基本上都和set中的一致
 */

/**
 * 单键值
 *
 * 修改操作：
 *      insert(value): 返回一个pair，first是同类型set的迭代器，second是插入是否成功的bool值
 *      clear/swap
 *      erase(start_iterator, end_iterator)/erase(value): 支持删除一个元素或一定范围内的元素
 * 查找操作：
 *      find: 返回迭代器
 *      count: return size_t，因为set是唯一键值，所以也就是1或0
 *      equal_range: 返回一组迭代器
 *      lower_bound/upper_bound
 * 迭代器
 */
void TestSet() {
    std::set<int> s1{1, 3, 4, 5, 6, 6};
    // 输出依然只有1.2.3.4.5
    for (auto e : s1) {
        cout << e << " ";
    }
    cout << endl;

    std::pair<std::set<int>::iterator, std::set<int>::iterator> res_equal = s1.equal_range(5);
    cout << "res.first = " << *res_equal.first << ", snd: " << *res_equal.second << endl;

    std::pair<std::set<int>::iterator, bool> result = s1.insert(7);
    std::cout << "first = " << *result.first << ", second = " << result.second << std::endl;

    auto range_left = s1.begin();
    auto range_right = ++s1.begin();
    s1.erase(range_left, range_right);
    s1.erase(6);
    cout << "s1.size() = " << s1.size() << ", max_size = " << s1.max_size() << std::endl;

    auto res = s1.find(5);
    if (res != s1.end()) {
        cout << "find OK" << endl;
    } else {
        cout << "find failed." << endl;
    }
    s1.insert(7);
    cout << "number of 7 = " << s1.count(7) << endl;

    s1.clear();
    std::set<int> empty;
    s1.swap(empty);
    cout << "clear swap s1.size() = " << s1.size() << ", max_size = " << s1.max_size() << std::endl;
}

/**
 * 接口API基本上和multiset都是一致的
 */
void TestMultiSet() {
    std::multiset<int> s1{1, 3, 4, 5, 6, 6, 9, 8};
    // 输出依然只有1.2.3.4.5
    for (auto e : s1) {
        cout << e << " ";
    }
    cout << endl;

    std::pair<std::set<int>::iterator, std::set<int>::iterator> res_equal = s1.equal_range(6);
    // first首个不小于key的元素，second首个大于key的元素
    cout << "res.first = " << *res_equal.first << ", snd: " << *res_equal.second << endl;

    s1.insert(7);
    s1.insert(7);

    auto range_left = s1.begin();
    auto range_right = ++s1.begin();
    s1.erase(range_left, range_right);
    cout << "s1.size() = " << s1.size() << ", max_size = " << s1.max_size() << std::endl;
}


int main(int argc, char* argv[]) {
    // TestSet();
    TestMultiSet();

    return 0;
}