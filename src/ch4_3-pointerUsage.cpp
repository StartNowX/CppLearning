#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <array>

using namespace std;

// *******  ָ�������֮ǰ��һ��Ҫ��ʼ��Ϊһ��ȷ���ġ��ʵ��ĵ�ַ  *******
void pointerUsage(void) {
	int a = 49;
	int* b = &a;
	// ������һ����ָ�붼�ǻ����������͵�
	int* c, d;	// c��ָ�룬d��int����

	// C����һ��ϰ�� int *p
	// C++����һ��ϰ��	int* p
	double e = 1000.0;
	double* p = &e;
	cout << "*p: " << *p << " p: " << p << endl;
	cout << "sizeof(p) = " << sizeof(p) << endl;

	int* pt;
	// pt = 0xB8000000;  // Error. ���ܽ�unsigned char*ת��Ϊint*
	pt = (int*)0xB8000000;

	int* pd = new int;
	*pd = 400;
	cout << "*pd: " << *pd << " pd: " << pd << endl;
	delete pd;
	// delete p;   // Error. delete��������ɾ������new��ָ�룬���ǶԿ�ָ��delete�ǰ�ȫ��

	// ��������ֵ�����޸ģ���������ʾ��ַ������ָ���Ǳ����������޸�
}


void addpointer(void) {
	double wage[] = { 100.0, 2000.0, 400000.0 };
	int stage[] = { 1, 2, 4 };

	// C++������������Ϊ��һ��Ԫ�صĵ�ַ
	double *pw = wage;
	int *ps = &stage[0];

	cout << "pw = " << pw << "\t" << "*pw = " << *pw << endl;
	cout << "ps = " << ps << "\t" << "*ps = " << *ps << endl;

	pw += 1;
	ps += 1;
	cout << "\t add one \t" << endl;
	cout << "pw = " << pw << "\t" << "*pw = " << *pw << endl;
	cout << "ps = " << ps << "\t" << "*ps = " << *ps << endl;

	// ָ������������
	// 1. ָ���ֵ�����޸ģ����������ǳ���
	// 2. ָ��Ӧ��sizeof����ָ��ĳ��ȣ�����Ӧ��sizeof�õ���������ĳ���
	cout << "sizeof(wage) = " << sizeof(wage) << endl;
	cout << "sizeof(pw) = " << sizeof(pw) << endl;

	// ��������ȡ��ַ�����������������ĵ�ַ����ʱ+1�����ӵ�����������ĳ���
	cout << "&stage + 1 = " << &stage + 1 << endl;
	int (*psd)[3] = &stage;	// ����ָ�룬�������ţ�����ָ������
	cout << "(*psd)[0] = " << (*psd)[0] << " \t " << "(*psd)[1] = " << (*psd)[1] << endl;
}

void ptrstr(void) {
	char animal[20] = "bear";
	const char* bird = "wren";	// "wren"�����ַ����ĵ�ַ��
	char* ps;

	cout << animal << " and " << bird << endl;

	cout << "Enter a new animal: ";
	cin >> animal;
	ps = animal;
	cout << ps << endl;

	// ��ָ����char���ͣ�cout����ʾָ����ָ����ַ�����������ʾ��ַ����ǿ�ƽ�ָ��ת��Ϊ�������ͣ���int*
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
	food[19] = '\0';	//���Ͽո��������ַ�����β
}

void newstru() {
	struct info {
		char name[20];
		double salary;
	};

	info* mem_salary = new info;
	cout << "Enter name: ";
	cin.get(mem_salary->name, 20);
	//cin >> mem_salary->name;  // jack brown ֮�������ᵼ�º����޷����룬��Ϊ��>>�������ַ���ʱ���������ո񡱣���TAB�������س���������
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

// array�����鶼�洢���ڴ�����ջ��
// vector��洢��������������
// ���Խ�һ��array����ֵ����һ��array���󣬶�vector�����鲻��
void templateUsage(void) {
	vector<double> tmpb(3);
	tmpb[0] = 10.0;
	tmpb[1] = 20.0;
	tmpb[2] = 30.0;

	vector<int> a	{1, 2, 3};	// C++ 11

	// array C++11�����ṩͷ�ļ�<array.h>
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