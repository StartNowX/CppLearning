#include <iostream>

using namespace std;

// istream类为unsigned/signed char*, char* 这三种字符指针提供了重载>>抽取运算符
// 抽取运算符获得输入，放至指定位置后，加上空值字符，使之成为字符串
void cinUsage(void) {
	int cN;
	cin >> cN;
	cout << "cN in dec: " << cN << endl;
	cin >> hex >> cN;   //指定为十六进制输入
	cout << "cN in hex: " << std::hex << cN << endl;
	int cT = 12;
	cout << "cT in hex: " << std::hex << cT << endl;
}

// cin读取从非空字符开始到与目标类型不匹配的第一个字符之间的所有内容
// 流状态
// eofbit, badbit,failbit, goodbit,
// good(): 如果流可以用，返回true, 
// eof(), 如果流到达文件末尾，返回true	bad(), fail(), rdstate(),
// clear(), setstate()
void checkCin(void) {
	cout << "Enter number: " << endl;
	int inputNum;
	
	long inputSum = 0;
	while (cin >> inputNum) {
		inputSum += inputNum;
	}
	cout << cin.badbit << " " << cin.goodbit << " " << cin.failbit << endl;
	cout << "Last input is " << inputNum << endl;
	cout << "Input sum is " << inputSum << endl;
}


// 1. cin.get(void)和cin.get(char &)的区别，对比ch4_1-arrayInit.cpp
void otherIstream(void) {
	cout << "Enter chars: ";
	int cnt = 0;
	char ch_t;
	// 成员函数get(char &)接收任意下一个输入字符，包括空格、制表符或换行符
	// cin.get(char &)返回调用get的istream对象的引用，因此可以对get拼接
	/*cin.get(ch_t);
	while (ch_t != '\n') {
		cout << ch_t;
		cnt++;
		cin.get(ch_t);
	}*/

	// 成员函数cin.get(void)仍然读取空白，但是使用返回值传递，
	// 返回类型为整型，不再能够进行拼接
	char ch_tt;
	ch_tt =	cin.get();
	while (ch_tt != EOF ) {
		cout << ch_tt;
		cnt++;
		ch_tt = cin.get();
	}


	// 调用 << 抽取运算会跳过空格和换行符，遇到空格和换行符就不再接收后面的字符
	/*char ch_t1;
	cin >> ch_t1;
	// 如下while会陷入死循环，因为<<是会跳过空格和换行符的
	while (ch_t1 != '\n') {
		cout << ch_t1;
		cnt++;
		cin.get(ch_t);
	}*/

}

// 其他istream类方法
// 字符串输入getline()， get()
// getline()将会丢掉分解符，而get()不会
void otherIstream1() {
	const int LIMIT = 255;
	char input_n[LIMIT];
	cout << "Enter a string for getline() processing: ";
	cin.getline(input_n, LIMIT, '#');
	cout << "Here is your input: " << endl;
	cout << input_n << "\n Done with phase 1" << endl;

	char ch_t;
	cin.get(ch_t);
	cout << "next character is " << ch_t << endl;

	// 清空当前行的剩余字符
	if (ch_t != '\n') {
		cin.ignore(LIMIT, '\n');
	}

	cout << "Enter new string for get(): ";
	cin.get(input_n, LIMIT, '#');
	cout << "Here is your input: " << endl;
	cout << input_n << "\n Done with phase 1" << endl;
	cin.get(ch_t);
	cout << "next character is " << ch_t << endl;
}

// 其他istream方法
// read()，从标准输入中读取指定数量的字符，不会在输入后添加空值字符（get和getline会），返回istream&
// peek()，查看下一个输入字符
// gcount()，返回非格式化抽取方法读取的字符数，即get，getline，read，>>会对输入格式化
// putback()，将字符插入到输入字符串中，作为下一个输入语句的第一个字符
void otherIstream2(void) {
	char ch_tn;
	while (cin.get(ch_tn)) {
		if (ch_tn != '#') {
			cout << ch_tn;
		}
		else {
			cin.putback(ch_tn);
			break;
		}
	}
	if (!cin.eof()) {
		cin.get(ch_tn);
		cout << ch_tn << " is next ch\n";
	}
	else {
		cout << "\nEnd\n";
		exit(0);
	}

	while (cin.peek() != '#') {
		cin.get(ch_tn);
		cout << endl << ch_tn;
	}

	if (!cin.eof()) {
		cin.get(ch_tn);
		cout << ch_tn << " is next ch\n";
	}
	else {
		cout << "End";
	}
}

void test_istream() {
	char nameT[20];
	cin >> nameT;
	cout << "res: " << nameT << endl;
}

int main1702(int argc, char *argv[]){
	//cinUsage();

	//checkCin();

	//otherIstream();
	//otherIstream1();
	//otherIstream2();
	test_istream();

	system("pause");
	return 0;
}