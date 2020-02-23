#include <iostream>
#include "ch11_17_stonewt.h"

using namespace std;

void display(const Stonewt& stone, int n);

int main(int argc, char* argv[]) {
	//explicit Stonewt(double lbs) // if use this constructor, the object incognito cannt be inilialized
	//Stonewt incognito = 275; // use constructor to initialize
	Stonewt wolfe(285.7);  // same to wolfe = 285.7;
	Stonewt talft(21, 5);

	cout << "The celebrity weight: " << endl;
	//incognito.show_stn();
	cout << "The detective weight: " << endl;
	wolfe.show_stn();
	cout << "The president weight: " << endl;
	talft.show_lbs();

	display(talft, 2);

	display(422, 2);  // 隐式转换


	// 转换函数
	cout << int(talft) << endl;
	//cout << double(wolfe) << endl;

	double tmpRes1 = talft; // 隐式转换

	// 如果只声明一个转换函数，则会隐式转换，并调用转换函数
	// 若声明多个转换函数，则出现二义性
	//long tmpRes = wolfe;
	long tmpRes2 = double(wolfe); // 强转为double，再转为long

	system("pause");
	return 0;
}

void display(const Stonewt& stone, int n) {
	for (int i = 0; i < n; ++i) {
		cout << "Wow! ";
		stone.show_stn();
	}
}