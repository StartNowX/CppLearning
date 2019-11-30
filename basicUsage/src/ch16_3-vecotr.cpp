#include <iostream>
#include <vector>

using namespace std;


// 模板类
// 1. vector可以将一个vector赋值给另一个
// 2. 可执行的操作：
//	 size():  返回元素数目
//   swap():  交换两个容器的内容
//   begin()/end():  返回指向第一个容器的迭代器/超过容器尾的迭代器（迭代器可以是指针，也可以是对其执行类似指针的操作）
void vectorUsage(void) {
	vector<int> a = { 1,2,3,4,5 };
	vector<int> b = a;
	for (int i = 0; i < b.size(); i++) {
		cout << " " << b[i];
	}
	cout << endl;
}

int main1603(int argc, int *argv[]) {

	vectorUsage();

	system("pause");
	return 0;
}