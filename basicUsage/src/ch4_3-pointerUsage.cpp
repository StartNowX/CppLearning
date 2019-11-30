#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <array>

using namespace std;

// *******  指针解引用之前，一定要初始化为一个确定的、适当的地址  *******
void pointerUsage(void) {
	int a = 49;
	int* b = &a;
	// 和数组一样，指针都是基于其他类型的
	int* c, d;	// c是指针，d是int变量

	// C程序一般习惯 int *p
	// C++程序一般习惯	int* p
	double e = 1000.0;
	double* p = &e;
	cout << "*p: " << *p << " p: " << p << endl;
	cout << "sizeof(p) = " << sizeof(p) << endl;

	int* pt;
	// pt = 0xB8000000;  // Error. 不能将unsigned char*转换为int*
	pt = (int*)0xB8000000;

	int* pd = new int;
	*pd = 400;
	cout << "*pd: " << *pd << " pd: " << pd << endl;
	delete pd;
	// delete p;   // Error. delete不能用来删除不是new的指针，但是对空指针delete是安全的

	// 数组名的值不能修改（数组名表示地址），但指针是变量，可以修改
}


void addpointer(void) {
	double wage[] = { 100.0, 2000.0, 400000.0 };
	int stage[] = { 1, 2, 4 };

	// C++将数组名解释为第一个元素的地址
	double *pw = wage;
	int *ps = &stage[0];

	cout << "pw = " << pw << "\t" << "*pw = " << *pw << endl;
	cout << "ps = " << ps << "\t" << "*ps = " << *ps << endl;

	pw += 1;
	ps += 1;
	cout << "\t add one \t" << endl;
	cout << "pw = " << pw << "\t" << "*pw = " << *pw << endl;
	cout << "ps = " << ps << "\t" << "*ps = " << *ps << endl;

	// 指针和数组的区别
	// 1. 指针的值可以修改，而数组名是常量
	// 2. 指针应用sizeof代表指针的长度，数组应用sizeof得到的是数组的长度
	cout << "sizeof(wage) = " << sizeof(wage) << endl;
	cout << "sizeof(pw) = " << sizeof(pw) << endl;

	// 对数组名取地址，代表的是整个数组的地址，此时+1，增加的是整个数组的长度
	cout << "&stage + 1 = " << &stage + 1 << endl;
	int (*psd)[3] = &stage;	// 数组指针，不带括号，将是指针数组
	cout << "(*psd)[0] = " << (*psd)[0] << " \t " << "(*psd)[1] = " << (*psd)[1] << endl;
}

void ptrstr(void) {
	char animal[20] = "bear";
	const char* bird = "wren";	// "wren"代表字符串的地址，
	char* ps;

	cout << animal << " and " << bird << endl;

	cout << "Enter a new animal: ";
	cin >> animal;
	ps = animal;
	cout << ps << endl;

	// 若指针是char类型，cout将显示指针所指向的字符串，若想显示地址，需强制将指针转换为其他类型，如int*
	cout << "Before using strcpy(): " << endl;
	cout << animal << " at " << (int*)animal << endl;
	cout << ps << " at " << (int*)ps << endl;

	ps = new char[strlen(animal) + 1];
	strcpy(ps, animal);
	cout << "After using strcpy(): " << endl;
	cout << animal << " at " << (int*)animal << endl;
	cout << ps << " at " << (int*)ps << endl;

	delete[]ps;

	char food[20] = "vegetable";
	strncpy(food, "you are ok, sir?", 19);
	food[19] = '\0';	//加上空格符，标记字符串结尾
}

void newstru() {
	struct info {
		char name[20];
		double salary;
	};

	info* mem_salary = new info;
	cout << "Enter name: ";
	cin.get(mem_salary->name, 20);
	//cin >> mem_salary->name;  // jack brown 之类的输入会导致后续无法输入，因为“>>”输入字符串时，遇到“空格”，“TAB”，“回车”都结束
	cout << "Enter salary: ";
	cin >> (*mem_salary).salary;
	cout << "Item is: " << (mem_salary->name) << " 's salary is " << (*mem_salary).salary << endl;
}

void mixtypes(void) {
	struct antarctica_years_end {
		int year;
	};

	antarctica_years_end s01, s02, s03;
	s01.year = 1998;
	antarctica_years_end* ps = &s02;
	ps->year = 1999;
	antarctica_years_end tils[3];
	tils[0].year = 2000;
	cout << tils->year << endl;

	const antarctica_years_end* ps1[3] = { &s01, &s02, &s03 };
	cout << "ps1[0] " << ps1[0]->year << endl;
	
	const antarctica_years_end** ps2 = ps1;
	// C++ 11
	auto ps3 = ps1;
	cout << (*ps2)->year << endl;
	cout << (*(ps3 + 1))->year << endl;

}

// array和数组都存储于内存区域栈中
// vector则存储于自由区域或堆中
// 可以将一个array对象赋值给另一个array对象，而vector和数组不行
void templateUsage(void) {
	vector<double> tmpb(3);
	tmpb[0] = 10.0;
	tmpb[1] = 20.0;
	tmpb[2] = 30.0;

	vector<int> a	{1, 2, 3};	// C++ 11

	// array C++11，需提供头文件<array.h>
	array<int, 3> b;
	b[0] = 1;
	b[1] = 2;
	b[2] = 3;

	array<double, 3> dou{ 10.0, 200.0, 20 };
}

void testEx(void) {
	cout << " testEx " << endl;
	/*char actor[30];
	short betsize[100];
	float chuck[13];
	long double dipsa[64];*/

	array<char, 30> actor;
	array<short, 100> betsize;
	array<float, 13> chuck;
	array<long double, 64> dipsa;

	int pos[] = { 1, 2, 3, 4, 5 };

	cout << "Home of jolly bytes." << "is at " << (int*) "Home of jolly bytes." << endl;
}

int main0403(int argc, char* argv[]) {

	//pointerUsage();

	//addpointer();

	//ptrstr();

	//newstru();

	//mixtypes();


	//templateUsage();

	testEx();

	system("pause");
	return 0;
}