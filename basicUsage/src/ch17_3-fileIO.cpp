#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>   // for exit()
#include <iomanip>

using namespace std;

// C++��ͷ�ļ�fstream�ж����˶���࣬������д���ofstream������ڶ�����ifstream��
// ��״̬��飬������if(fout.fail())������if(!fout.good())������(!fout)
// �°�C++��������fout.is_open()

// һ���ļ���ofstream/ifstream���Թ�������ļ���ʹ��Ĭ�ϵĹ��캯������ofstream/ifstream����
int main170301(int argc, char *argv[]) {

	string filename;
	cout << "Enter file name: ";
	cin >> filename;

	ofstream fout;
	fout.open(filename.c_str());
	fout << "For your eyes only!\n";
	cout << "Enter your secret number: ";
	float secretNum;
	cin >> secretNum;
	fout << "Your secret number is " << secretNum << endl;
	fout.close();


	//ifstream fin(filename.c_str());
	ifstream fin; // ʹ��Ĭ�Ϲ��캯��
	fin.open(filename.c_str());
	cout << "Here are the contens: " << endl;
	char ch;
	while (fin.get(ch)) {
		cout << ch;
	}
	cout << "Done. \n";
	fin.clear();	// ��ʱ������Ҫ��������Զ�޺�
	fin.close();

	cout << "Enter file name: ";
	cin >> filename;
	fout.open(filename.c_str());
	fout << "The second one!\n";
	cout << "Enter your secret number: ";
	cin >> secretNum;
	fout << "Your secret number is " << secretNum << endl;
	fout.close();

	fin.open(filename.c_str());
	cout << "Here are the contens: " << endl;
	while (fin.get(ch)) {
		cout << ch;
	}
	cout << "Done. \n";
	fin.close();

	system("pause");
	return 0;
}



// �ļ�ģʽ
// ios_base������һ��openmode���ͣ����ڱ�ʾģʽ����fmtflags��iostate����һ����bitmask����
// ios_base::in����ȡ��		ios_base::out(д��)		ios_base::ate(�򿪲��ƶ����ļ�β)
// ios_base::app��׷�ӣ�	ios_base::trunc���ض̣���ɾ����	ios_base::binary(������)

// ifstream open()Ĭ��ģʽ��ios_base::in
// ofstream open()Ĭ��ģʽ��ios_base::out|ios_base::trunc
// fstream�಻�ṩĬ�ϵ�ģʽֵ���������ʾָ��

//     C++ model				   Cģʽ
// ios_base::in						"r"
// ios_base::out					"w"
// ios_base::out|ios_base::trunc	"w"
// ios_base::out|ios_base::app		"a"
// ios_base::out|ios_base::out		"r+"	�ļ���д�����ļ������λ��д�룬���ļ��󡾲��᡿���ԭ�����ݣ�д��Ḳ��ԭ������
// ios_base::out|ios_base::out|ios_base::trunc		"w+"	�ļ���д�����ļ������λ��д�룬���ļ��󡾻᡿���ԭ�����ݣ�д��Ḳ��ԭ������
// c++mode|ios_base::binary			cmodeb
// c++mode|ios_base::ate			cmode

void append(void) {
	const char* file_g = "guest.txt";
	char tmp_char;
	//ifstream ifs(file_g, ios_base::in);
	ifstream ifs;
	ifs.open(file_g);
	if (ifs.is_open()) {
		cout << "Here are the current contents of " << file_g << ": " << endl;
		while (ifs.get(tmp_char)) {
			cout << tmp_char;
		}
		ifs.close();
	}

	ofstream ofs(file_g, ios_base::out | ios_base::app);
	if (!ofs.is_open()) {
		cerr << "Can't open " << file_g << " file for output.\n";
		exit(EXIT_FAILURE);
	}

	cout << "Enter guests name: " << endl;
	string name;
	while (getline(cin, name) && name.size() > 0) {
		ofs << name << endl;
	}

	while (cin.get(tmp_char) && tmp_char != '\n') {
		ofs << tmp_char;
	}
	ofs.close();


	ifs.clear();
	ifs.open(file_g);
	if (ifs.is_open()) {
		cout << "New contents of " << file_g << ": " << endl;
		while (ifs.get(tmp_char)) {
			cout << tmp_char;
		}
		ifs.close();
	}
	cout << "Done.\n";
}

// �����Ƹ�ʽ
// �ı���ʽ�����ȡ�Լ���ͬOS֮�䴫��
// �����Ƹ�ʽ�����ָ�Ϊ��ȷ����Ϊ��洢������ֵ���ڲ���ʾ�����������ұ����ٶȽϿ죬ռ�ÿռ��٣�
// ���ǲ�ͬϵͳ֮�������Ϊ�ڲ���ʾ��ͬ�����²����㴫��

inline void eatline() { while (cin.get() != '\n') continue; }
struct planet {
	char name[20];
	double population;
	double g;
};

const char* file = "./planet.dat";

void binary(void) {
	planet p1;
	cout << fixed << right;

	ifstream fin;
	fin.open(file, ios_base::in | ios_base::binary);
	if (fin.is_open()) {
		cout << "Here are current contents of " << file << " file: " << endl;
		while (fin.read((char*)&p1, sizeof(p1))) {
			cout << setw(20) << p1.name << ": " \
				<< setprecision(0) << setw(12) << p1.population \
				<< setprecision(2) << setw(6) << p1.g << endl;
		}
		fin.close();
	}

	ofstream fout;
	fout.open(file, ios_base::out | ios_base::app | ios_base::binary);
	if (!fout.is_open()) {
		cerr << "Can't open " << file << " file for output.";
		exit(0);
	}
	cout << "Enter planet name(blank line for quit): ";
	cin.get(p1.name, 20);
	while (p1.name[0] != '\0') {
		eatline();
		cout << "population: ";
		cin >> p1.population;
		cout << "\n acceleration: ";
		cin >> p1.g;
		eatline();
		fout.write((char *)&p1, sizeof(p1));
		cout << "Enter planet name(blank line for quit): ";
		cin.get(p1.name, 20);
	}
	fout.close();

	cout << "new contents: " << endl;
	fin.clear();
	fin.open(file, ios_base::in | ios_base::binary);
	if (fin.is_open()) {
		cout << "Here are current contents of " << file << " file: " << endl;
		while (fin.read((char*)&p1, sizeof(p1))) {
			cout << setw(20) << p1.name << ": " \
				<< setprecision(0) << setw(12) << p1.population \
				<< setprecision(2) << setw(6) << p1.g << endl;
		}
		fin.close();
	}
}


// seekg����ifstream, seekp����ofstream
// istream& seekg(seekoff, ios_base::seekdir):  seekoff�����ƫ��λ�ã�seekdir������ֵ
//       ios_base::beg������ļ���ʼ��ƫ�ƣ�ios_base::cur����ڵ�ǰλ�ã�ios_base::end������ļ�ĩβ
// istream& seekg(streampos)����λ�����ļ���ͷ�ض�����

// �ļ�ָ�뵱ǰ��λ�ÿ���ͨ��tellg����������������tellp������������

// cstdio�е�tmpname��ȡ��һ�޶����ļ��� char* tmpname(char* pzName)

int main1703(int argc, char *argv[]) {

	//append();

	binary();

	system("pause");
	return 0;
}