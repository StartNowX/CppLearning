#include <iostream>

using namespace std;

// istream��Ϊunsigned/signed char*, char* �������ַ�ָ���ṩ������>>��ȡ�����
// ��ȡ�����������룬����ָ��λ�ú󣬼��Ͽ�ֵ�ַ���ʹ֮��Ϊ�ַ���
void cinUsage(void) {
	int cN;
	cin >> cN;
	cout << "cN in dec: " << cN << endl;
	cin >> hex >> cN;   //ָ��Ϊʮ����������
	cout << "cN in hex: " << std::hex << cN << endl;
	int cT = 12;
	cout << "cT in hex: " << std::hex << cT << endl;
}

// cin��ȡ�ӷǿ��ַ���ʼ����Ŀ�����Ͳ�ƥ��ĵ�һ���ַ�֮�����������
// ��״̬
// eofbit, badbit,failbit, goodbit,
// good(): ����������ã�����true, 
// eof(), ����������ļ�ĩβ������true	bad(), fail(), rdstate(),
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


// 1. cin.get(void)��cin.get(char &)�����𣬶Ա�ch4_1-arrayInit.cpp
void otherIstream(void) {
	cout << "Enter chars: ";
	int cnt = 0;
	char ch_t;
	// ��Ա����get(char &)����������һ�������ַ��������ո��Ʊ�����з�
	// cin.get(char &)���ص���get��istream��������ã���˿��Զ�getƴ��
	/*cin.get(ch_t);
	while (ch_t != '\n') {
		cout << ch_t;
		cnt++;
		cin.get(ch_t);
	}*/

	// ��Ա����cin.get(void)��Ȼ��ȡ�հף�����ʹ�÷���ֵ���ݣ�
	// ��������Ϊ���ͣ������ܹ�����ƴ��
	char ch_tt;
	ch_tt =	cin.get();
	while (ch_tt != EOF ) {
		cout << ch_tt;
		cnt++;
		ch_tt = cin.get();
	}


	// ���� << ��ȡ����������ո�ͻ��з��������ո�ͻ��з��Ͳ��ٽ��պ�����ַ�
	/*char ch_t1;
	cin >> ch_t1;
	// ����while��������ѭ������Ϊ<<�ǻ������ո�ͻ��з���
	while (ch_t1 != '\n') {
		cout << ch_t1;
		cnt++;
		cin.get(ch_t);
	}*/

}

// ����istream�෽��
// �ַ�������getline()�� get()
// getline()���ᶪ���ֽ������get()����
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

	// ��յ�ǰ�е�ʣ���ַ�
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

// ����istream����
// read()���ӱ�׼�����ж�ȡָ���������ַ����������������ӿ�ֵ�ַ���get��getline�ᣩ������istream&
// peek()���鿴��һ�������ַ�
// gcount()�����طǸ�ʽ����ȡ������ȡ���ַ�������get��getline��read��>>��������ʽ��
// putback()�����ַ����뵽�����ַ����У���Ϊ��һ���������ĵ�һ���ַ�
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