#include <iostream>
#include <string>

using namespace std;

void arrayInit(void) {
	int hand[3] = { 1, 2, 4 };
	short tile[3];
	// Error. ��ʼ��ֻ�������鶨��ʱʹ��
	//tile = { 1, 3, 4 }; 
	// Error. ���������鸳ֵ����һ������
	//hand = tile;

	// C++11 ������ʼ������
	int hand1[3]{ 1, 2, 3 };
	// �������ʼ��Ϊ0
	int hand2[4] = { 0 };
	int hand3[4]{};

	// ������խת������
	long num[3] = { 90, 20, 20.5 };
}


// cin >>��cin.get()��cin.getline()�Լ�getline�÷����𣬶Ա�ch17_2-cinUsage.cpp
// cin>>  �����ܿո������ո����
// cin.get(�ַ����������ַ���)	���տո񣬲����
// cin.get(void)	�����������еĲ���Ҫ���ַ���	
// cin.getline()ʵ���е�����������Ĭ����'\0'
// getline ����string.h��getline(cin, str)
void cString(void) {
	char a[11] = { 'a', 'b', 'c' }; // not a string
	char b[11] = { 'a', 'b', 'c', '\0' };

	char str = 'S';
	//char str = "S";  // Error. "S" is string. "S"�ַ��������ڴ�ĵ�ַ		

	// �ַ���ƴ��
	cout << "Hi, this is " "jack" << endl;
	char str1[256] = "This is" "Tom"; // û�пո�
	cout << str1 << endl;

	// ʹ��getline(ArrayName, size)
	// getline()�����з��滻�ɿո��
	char name[100];
	cout << "What is your name?" << endl;
	cin.getline(name, 20);
	cout << "Your name is " << name << endl;

	// ʹ��get()
	char name1[50];
	cout << "What is your name?" << endl;
	cin.get(name, 10);
	// ���Ӵ˾䣬name1�����������룬��Ϊget()�ᱣ�����з��������ǽ����滻�ɿո��'\0'
	cin.get();
	cin.get(name1, 10);

	// Ҳ��������ʹ��
	//cin.get(name, 10).get();
	//cin.getline(name, 10).getline(name1, 20);   //��ͬ�����ε���getline���ֱ��������name��name1
	cout << "name: " << name << endl;
	cout << "name1: " << name1 << endl;

	// ����������ֺ������е��ַ���
	cout << "Year: ";
	int year;
	cin >> year;
	cin.get();
	cout << "\nAddress: ";
	char address[50];
	cin.getline(address, 30);
	cout << "res year and address: " << year << "   add: " << address << endl;
}

void getSerial() {
	char item[20];
	char nameTmp[30];
	int num;

	//cin >> item;	// �����ܿո������ո����
	cin.get(item, 19);
	cin >> num;
	cin.get();	// ���Ӵ˾䣬nameTmp�޷����룬cin>>num�������з�����������
	cin.getline(nameTmp, 20);
	cout << "item: " << item << endl;
	cout << "num: " << num << endl;
	cout << "nameTmp: " << nameTmp << endl;
}

void plusString(void) {

	string s1 = "jkljsdfadf";
	string s2 = s1;
	cout << "s1 length is: " << s1.length() << " sizeof(s1) is " << sizeof(s1) << endl;

	// C++11 �ṩ�����������ַ���  
	wchar_t title[] = L"Chief Jack";	// ���ַ�
	char16_t name[] = u"James";
	char32_t car[] = U"Rambo jini";
	wcout << "Info: " << title << " " << name << " " << car << endl;
	wcout << title << endl;

	// R ����raw,��ӡԭʼ�ַ�  R"(string)"
	cout << R"(Who are you "king" \n ?)" << endl;
	// ��ӡ���� 
	// �� R"+* ��ʼ���� +*"����
	// R"+*(string)+*"
	cout << R"+*("Who are you ("kings"?)")+*" << endl;
}



int main0401(int argc, char *argv) {

	arrayInit();

	//cString();

	plusString();

	system("pause");

	return 0;
}