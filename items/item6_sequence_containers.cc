#include <iostream>
using namespace std;

/**
 * 顺序容器：
 *      vector，可变大小，支持快速随机访问，除尾部外位置元素删除和插入，效率低
 *      deque，双端队列，支持快速随机访问，尾部和头部能快速删除和插入
 *      list，双向列表，只支持顺序访问，但是在任何位置都能快速插入和删除
 *      forward_list，单向列表，只支持单向访问，任何位置都能快速插入和删除
 *      array，固定大小的数组，支持快速随机访问，但是不支持更改数组大小
 *      string，专门存储字符串，支持快速随机访问，尾部和头部插入删除速度快
 *
 *      本质上，适配器是使一事物的行为类似于另一类事物的行为的一种机制。容器适配器让一种已存在的容器类型采用另一种不同的抽象类型的工作方式实现。如queue将deque用FIFO的方式工作，stack将任何顺序容器以栈的方式工作
 *
 *      STL中，stack/queue/priority_queue是三种顺序容器适配器，不支持随机访问或顺序访问，其底层都是用deque实现的，不支持迭代器和范围for，priority_queue是在vector基础上实现的
 *
 *
 * 关联容器：
 *      set:
 *      map:
 *      multiset:
 *      multimap:
 */

/**
 * vector，动态数组
 * 初始化：列表初始化，赋值等
 * 内部原理：三个迭代器，start，finish，end_of_storage，当元素到达vector的内存空间满了后，扩充1.5-2倍
 * size/capacity:
 * reserve/resize:
 * swap/clear/shrink_to_fit: swap置换了size/capacity，clear改变size，shrink_to_fit将capacity适应到当前的size
 * pop_back/push_back
 * emplace/emplace_back
 * front/back
 * begin/cbegin/end/cend/rbegin/rend: 迭代器
 */
#include <vector>

#define PRINT_VEC_INFO(x, y) std::cout << x << " " << y << std::endl;
void TestVector() {
    std::vector<int> v1;
    v1.reserve(12);
    v1.resize(20);
    PRINT_VEC_INFO("v1 size", v1.size());
    PRINT_VEC_INFO("v1 capacity", v1.capacity());
    std::vector<int> v2(3, 10);
    v2.reserve(20);
    PRINT_VEC_INFO("v2_1 size", v2.size());
    PRINT_VEC_INFO("v2_1 capacity", v2.capacity());
    v2.shrink_to_fit();
    PRINT_VEC_INFO("v2_2 size", v2.size());
    PRINT_VEC_INFO("v2_2 capacity", v2.capacity());
    v2.clear();
    PRINT_VEC_INFO("v2_3 size", v2.size());
    PRINT_VEC_INFO("v2_3 capacity", v2.capacity());

    vector<int> v3(8, 2);
    vector<int> empty;
    v3.swap(empty);
    PRINT_VEC_INFO("v3 size", v3.size());
    PRINT_VEC_INFO("v3 capacity", v3.capacity());
    PRINT_VEC_INFO("empty size", empty.size());
    empty.pop_back();
    PRINT_VEC_INFO("empty size", empty.size());

    vector<int> v4(10, 3);
    v4[9] = 32;
    // 注意用迭代器删除vector元素时最安全的做法
    for (vector<int>::iterator it = v4.begin(); it != v4.end();) {
        if (32 == *it) {
            it = v4.erase(it);
        } else {
            ++it;
        }
    }
}

/**
 * list, 双向链表
 * push_back/push_front/emplace_back/emplace_front
 * pop_back/pop_front
 * unique
 */
#include <list>
void PrintList(const std::list<int>& t) {
    for (auto e : t) {
        cout << e << " ";
    }
    cout << endl;

    // with iterator
    cout << "use iterator print" << endl;
    for (auto it = t.begin(); it != t.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void TestList() {
    std::list<int> l1{2, 3, 3, 3};
    l1.push_back(4);
    l1.push_front(1);
    PrintList(l1);

    l1.pop_back();
    l1.pop_front();
    PrintList(l1);

    std::cout << l1.front() << ", back: " << l1.back() << std::endl;

    l1.unique();
    PrintList(l1);
}

/**
 * queue是容器适配器，给提供队列的功能，尤其是FIFO功能，其底层使用deque实现的
 *
 * 因为不支持随机访问或顺序访问队列元素，所以不支持for-range和迭代器
 *
 * size/empty/
 * front/back
 * pop/push
 * swap
 */
#include <queue>
void TestQueue() {
    std::queue<int> q;
    for (int i = 0; i < 5; ++i) {
        q.push(i * 3);
    }

    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    // 不支持for-range
    // for (auto e : q) {
    //     cout << e << " ";
    // }
    // cout << endl;
}

/**
 * priority_queue，优先队列，底层是堆，头文件queue
 * 默认是大顶堆，默认调用的比较函数对象是less，容器内的顺序既不是FIFO，也不是FILO，而是部分排序，如果想要小顶堆的话，比较函数用greater
 * empty/size/swap
 * pop/emplace/push
 * top
 */
#include <algorithm>
#include <memory>
void TestPriorityQueue() {
    // std::priority_queue<int> pq;                          // 默认大顶堆
    std::priority_queue<int, vector<int>, less<int>> pq;  // 大顶堆
    // std::priority_queue<int, vector<int>, greater<int>> pq;  // 小顶堆
    for (int i = 0; i < 5; ++i) {
        pq.emplace(i);
    }

    for (int i = 0; i < 5; ++i) {
        std::cout << pq.top() << " ";
        pq.pop();
    }

    cout << endl;

    using PairInt = pair<int, int>;
    auto cmp = [](PairInt a, PairInt b) { return a.second < b.second; };
    // priority_queue<PairInt, vector<PairInt>, greater<PairInt>> pq_pair;  // 根据第一个元素排序的小顶堆

    // priority_queue的第三个参数是【函数对象类型】，而不是仅仅是个函数对象，因此需要用类似decltype(cmp)或者function<bool(Param1,
    // Param2)>这样的方式
    priority_queue<PairInt, vector<PairInt>, decltype(cmp)> pq_pair(cmp);
    // priority_queue<PairInt, vector<PairInt>, std::function<bool(PairInt, PairInt)>> pq_pair(cmp);
    pq_pair.push({1, 1});
    pq_pair.push({2, 2});
    pq_pair.push({0, 3});
    pq_pair.push({9, 4});
    while (!pq_pair.empty()) {
        auto ele = pq_pair.top();
        cout << ele.first << " " << ele.second << endl;
        pq_pair.pop();
    }
}

/**
 * deque，双端队列
 * front/back
 * pop_back/pop_front
 * push_back/push_front/emplace_back/emplace_front/emplace
 *
 * 支持for-range，支持迭代器
 */
#include <deque>
void TestDeque() {
    std::deque<int> dq{1, 2, 3, 4, 5, 6, 7};
    std::cout << "dp.front() = " << dq.front() << ", back() = " << dq.back() << std::endl;

    std::cout << "size: " << dq.size() << ", dp.at(3): " << dq.at(3) << std::endl;

    for (auto e : dq) {
        cout << e << " ";
    }
    cout << endl;
}

/**
 * array，静态连续数组
 * std::array<int, N> arr;
 *
 * at/[]/front/back: 元素访问， data()指向内存中数组第一个元素的指针
 * fill/swap： 填充和置换array，fill(value)用value赋值给数组中的【所有】元素
 *
 * 迭代器操作
 */
#include <array>
void TestArray() {
    // std::array<int, 5> arr{1, 2, 3};
    std::array<int, 4> arr = {1, 2, 3};
    for (auto a : arr) {
        cout << a << " ";
    }
    cout << endl;

    // 用指针打印
    int* p = arr.data();  //指向第一个元素的指针
    for (int i = 0; i < 3; ++i) {
        cout << *(p + i) << " ";
    }
    cout << endl;

    cout << "arr.at(3) = " << arr.at(2) << endl;
    // cout << "arr.at(20) = " << arr.at(20) << endl;  // 运行时报错，at会进行参数范围检查

    arr.fill(10);  // arr所用元素变为10
    for (auto a : arr) {
        cout << a << " ";
    }
    cout << endl;
}

/**
 * C++11新增的，用单链表实现的，支持容器中任何位置插入和删除，不支持随机访问
 * 成员函数：构造、析构、operator=、assign、get_allocator(返回相关的分配器)
 *
 * 元素访问：front，迭代器
 * 容量：empty/max_size
 *
 * 修改：clear/resize/swap    insert_after/emplace_after/erase_after/push_front/emplace_front/pop_front
 *
 * 操作：merge/remove/remove_if/reverse/unique/sort
 */
#include <forward_list>
void TestForwardList() {
    std::forward_list<int> tmp_list{18, 25, 13, 4, 51, 16, 7, 10};
    std::forward_list<int> f_list = tmp_list;
    cout << "front: " << f_list.front() << endl;
    f_list.insert_after(f_list.begin(), 333);
    f_list.emplace_after(f_list.begin(), 222);
    f_list.emplace_front(111);  // 在容器的头部就地构造元素
    for (auto e : f_list) {
        cout << e << " ";
    }
    cout << endl;

    std::forward_list<int> f_list1;
    f_list1.assign(5, 20);  // f_list1有5个元素，每个元素都是20

    f_list.sort();
    f_list1.merge(f_list);  // merge后，f_list为空了
    cout << " after merge, f_list1.empty() = " << f_list1.empty() << ", f_list.empty() = " << f_list.empty() << endl;
    for (auto e : f_list1) {
        cout << e << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    // TestVector();

    // TestList();

    // TestQueue();
    // TestDeque();
    TestPriorityQueue();

    // TestArray();

    // TestForwardList();

    return 0;
}