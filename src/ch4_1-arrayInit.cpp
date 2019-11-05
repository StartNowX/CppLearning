#include <iostream>
#include <string>

using namespace std;

void arrayInit(void) {
	int hand[3] = { 1, 2, 4 };
	short tile[3];
	// Error. 初始化只能在数组定义时使用
	//tile = { 1, 3, 4 }; 
	// Error. 不能用数组赋值给另一个数组
	//hand = tile;

	// C++11 新增初始化方法
	int hand1[3]{ 1, 2, 3 };
	// 将数组初始化为0
	int hand2[4] = { 0 };
	int hand3[4]{};

	// 以下缩窄转换错误
	long num[3] = { 90, 20, 20.5 };
}


// cin >>，cin.get()，cin.getline()以及getline用法区别，对比ch17_2-cinUsage.cpp
// cin>>  不接受空格，遇到空格结束
// cin.get(字符数组名，字符数)	接收空格，并输出
// cin.get(void)	舍弃输入流中的不需要的字符串	
// cin.getline()实际有第三个参数，默认是'\0'
// getline 属于string.h，getline(cin, str)
void cString(void) {
	char a[11] = { 'a', 'b', 'c' }; // not a string
	char b[11] = { 'a', 'b', 'c', '\0' };

	char str = 'S';
	//char str = "S";  // Error. "S" is string. "S"字符串所在内存的地址		

	// 字符串拼接
	cout << "Hi, this is " "jack" << endl;
	char str1[256] = "This is" "Tom"; // 没有空格
	cout << str1 << endl;

	// 使用getline(ArrayName, size)
	// getline()将换行符替换成空格符
	char name[100];
	cout << "What is your name?" << endl;
	cin.getline(name, 20);
	cout << "Your name is " << name << endl;

	// 使用get()
	char name1[50];
	cout << "What is your name?" << endl;
	cin.get(name, 10);
	// 不加此句，name1将不会有输入，因为get()会保留换行符，而不是将其替换成空格符'\0'
	cin.get();
	cin.get(name1, 10);

	// 也可以联合使用
	//cin.get(name, 10).get();
	//cin.getline(name, 10).getline(name1, 20);   //等同于两次调用getline，分别将输入放入name和name1
	cout << "name: " << name << endl;
	cout << "name1: " << name1 << endl;

	// 混合输入数字和面向行的字符串
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

	//cin >> item;	// 不接受空格，遇到空格结束
	cin.get(item, 19);
	cin >> num;
	cin.get();	// 不加此句，nameTmp无法输入，cin>>num保留换行符在输入流中
	cin.getline(nameTmp, 20);
	cout << "item: " << item << endl;
	cout << "num: " << num << endl;
	cout << "nameTmp: " << nameTmp << endl;
}

void plusString(void) {

	string s1 = "jkljsdfadf";
	string s2 = s1;
	cout << "s1 length is: " << s1.length() << " sizeof(s1) is " << sizeof(s1) << endl;

	// C++11 提供的其他类型字符串  
	wchar_t title[] = L"Chief Jack";	// 宽字符
	char16_t name[] = u"James";
	char32_t car[] = U"Rambo jini";
	wcout << "Info: " << title << " " << name << " " << car << endl;
	wcout << title << endl;

	// R 代表raw,打印原始字符  R"(string)"
	cout << R"(Who are you "king" \n ?)" << endl;
	// 打印括号 
	// 以 R"+* 开始，以 +*"结束
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