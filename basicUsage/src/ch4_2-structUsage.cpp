#include <iostream>
#include <string>

using namespace std;

void structUsage(void) {
	struct info
	{
		char name[20];
		float price;
		int id;
	};
	// ��ʼ����C++����ʡ�Թؼ���struct
	info member1 = { "jack", 200.0, 10 };
	info member2{ "Mark", 1000.0, 5 };
	cout << "price: " << member1.price << " " << member2.price << endl;

	// �ṹ������
	info members[2] = {
		{"Tom", 100.0, 5},
		{"Pony", 333.3, 4}
	};
	cout << "mems: " << members[0].id << " " << members[1].id << endl;

	// λ�ֶ�
	struct messages {
		unsigned int SN : 4;  // 4 bits for SN
		unsigned int : 4;   // 4 bits unused
		bool goodIn : 1;  // 1 bit for goodIn	
		bool goodTorgle : 1;
	};
	messages me = { 15, 1, 0 };
	cout << me.SN << " " << me.goodIn << " " << me.goodTorgle << endl;
}


void unionUsage(void) {
	union one4all
	{
		int int_val ;
		long long_val;
		double double_val;
	};
	//ex1 = { 1 };

	one4all ex1;
	ex1.double_val = 32.11;
	cout << "ext double_val: " << " " << ex1.double_val << endl;

	ex1.int_val = 24;

	cout << "ex1 int_val: " << ex1.int_val << " " << ex1.double_val << endl;



}

void enumUsage(void) {
	enum colors {red = 1, green, blue = 100, yellow};
	colors cloth, shoe;
	cloth = red;
	shoe = yellow;
	// cloth = black;   // Error
	// ö�ٿ�������Ϊint�ͣ�����int�Ͳ����Զ�תΪö����
	// ++cloth;			// Error
	// shoe = red + green;		// Error
	cout << "cloth is " << cloth << endl;
	cout << "shoe is " << shoe << endl;

}

int main0402(int argc, char* argv[]) {

	//�ṹ��ʹ��
	//structUsage();

	unionUsage();

	enumUsage();

	system("pause");

	return 0;
}