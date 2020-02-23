#include <iostream>
#include <climits>

using namespace std;

void typeLimits(void) {
	cout << "*** begin typeLimits ***" << endl;

	int n_int = INT_MAX;
	short n_short = SHRT_MAX;
	long n_long = LONG_MAX;
	long long n_llong = LLONG_MAX;

	cout << "sizeof(int) is " << sizeof(int) << endl;
	cout << "sizeof(short) is " << sizeof(short) << endl;
	cout << "sizeof(long) is " << sizeof(long) << endl;
	cout << "sizeof(long long) is " << sizeof(long long) << endl;

	cout << "n_int = " << n_int << endl;
	cout << "n_short = " << n_short << endl;
	cout << "n_long = " << n_long << endl;
	cout << "n_llong = " << n_llong << endl;

	// C++11 提供的更多的初始化方式
	int tmp{ 3 };
	int tmp1 = {};
	int tmp2{4};
}

void hexoct(void) {
	int a = 10;
	int b = 07;
	int c = 0x56;

	// cout 默认以十进制显示
	cout << "display in default way: " << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;

	cout << "display in different way: " << endl;
	cout << "a = " << a << endl;
	cout << oct << "b = " << b << endl;
	cout << hex << "c = " << c << endl;
}

int main0301(int argc, char* argv[]) {
	
	//typeLimits();

	hexoct();

	system("pause");
	return 0;
}