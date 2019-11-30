#include <iostream>
#include <iomanip>

using namespace std;

void printNum(void) {
	int p_num;
	cout << "Enter the number: ";
	cin >> p_num;
	cout << "Print number: " << endl;
	cout.width(15);
	cout.setf(ios_base::showbase);
	cout << dec << p_num << " " << oct << p_num << " " << hex << p_num << endl;
}

//Enter your name : Billy Gruff
//Enter your hourly wages : 12
//Enter number of hours worked : 7.5
//First format : Billy Gruff : $          12.00 : 7.5
//Second Format :   Billy Gruff : $12.00 : 7.5
void formatShow(void) {
	char name[20];
	float wage;
	float price;
	cout << "Enter your name: ";
	cin.get(name, 20);
	cout << "Enter your hourly wages: ";
	cin >> wage;
	cout << "Enter number os hours worked: ";
	cin >> price;

	cout << "First format: ";
	cout << setw(30) << name << ": $";
	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.setf(ios_base::right, ios_base::adjustfield);
	cout << setprecision(2) << setw(15) << wage << " : ";
	cout << setprecision(2) << setw(15) << price << endl;
}

// Input: I see a q
//        I see a q

void showRes(void) {
	char ch;
	int ct1 = 0;

	cout << "Begin input: ";
	// 忽略空格和换行符
	// Iseeaq
	cin >> ch;
	while (ch != 'q')
	{
		ct1++;
		cin >> ch;
	}

	cout << "\nContinue input: ";
	// cin.get();   //加上该句，cnt2=8
	// 从上一个q后开始
	// I see a q
	int ct2 = 0;
	cin.get(ch);
	while (ch != 'q')
	{
		ct2++;
		cin.get(ch);
	}

	cout << "ct1 = " << ct1 << "; ct2 = " << ct2 << "\n";
}


int main01705(int argc, char* argv[]) {

	//printNum();
	//formatShow();
	showRes();

	system("pause");
	return 0;
}