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

	display(422, 2);  // ��ʽת��


	// ת������
	cout << int(talft) << endl;
	//cout << double(wolfe) << endl;

	double tmpRes1 = talft; // ��ʽת��

	// ���ֻ����һ��ת�������������ʽת����������ת������
	// ���������ת������������ֶ�����
	//long tmpRes = wolfe;
	long tmpRes2 = double(wolfe); // ǿתΪdouble����תΪlong

	system("pause");
	return 0;
}

void display(const Stonewt& stone, int n) {
	for (int i = 0; i < n; ++i) {
		cout << "Wow! ";
		stone.show_stn();
	}
}