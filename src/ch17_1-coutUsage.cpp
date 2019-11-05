#include <iostream>
#include <string>

using namespace std;

void flushBuffer(void) {
	cout << "Enter the num: ";
	float num;
	cin >> num;

	// ���Ʒ� endl��flush����ˢ�»�����������endl����뻻�з�
	// ���Ʒ� flushҲ�Ǻ���
	cout << "Good bye." << endl;
	cout << "R.I.P to JinYong." << flush;
	flush(cout);

	int input[] = { 2,3,4,5,6,7,8,9,0,10,10,12 };
	for (int i = 0; i < sizeof(input) / sizeof(int); i++) {
		cout << input[i] << " ";
	}
}


void setf(void) {
	int temperature = 63;
	cout.setf(ios_base::showpos);  // ��ʾ�����ţ���������Ϊ10ʱ
	cout << "The tempature is: " << temperature << endl;

	cout << "In hex: " << std::hex << temperature << endl;
	cout.setf(ios_base::uppercase);
	cout.setf(ios_base::showbase);	// ��ʾǰ׺
	cout << "New format is " << temperature << endl;

	cout << "How " << true << "! oops.....How ";
	cout.setf(ios_base::boolalpha);
	cout << true << endl;
	cout.unsetf(ios_base::boolalpha);
	cout << "Remove boolalpha: ";
	cout << true << endl;


	cout << "The alignment: ";
	cout.setf(ios_base::right, ios_base::adjustfield);
	cout.width(6);
	cout.fill('0');
	cout << std::dec << temperature << endl;
	cout << "align in left: ";
	cout.setf(ios_base::left, ios_base::adjustfield);
	cout << std::dec << temperature << endl;

	cout << "scientific format: ";
	float sciTmp = 3203203.2322323;
	cout.precision(2);
	cout.setf(ios_base::scientific, ios_base::floatfield);
	cout << sciTmp << endl;

	cout << "Fixed mode: ";
	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout << sciTmp << endl;
	cout.unsetf(ios_base::floatfield);
	cout << "Default mode: " << sciTmp << endl;
}

// #include <iomanip>
// setw()    ���ÿ��
// setfill()   ���������ַ�
// setprecision()    ���þ���


int main1701(int argc, char* argv[]) {
	//string str;
	//getline(cin, str);
	//cout << str << endl;

	//flushBuffer();

	setf();

	system("Pause");
	return 0;
}