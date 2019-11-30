#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>   // for exit()
#include <iomanip>

using namespace std;

// C++在头文件fstream中定义了多个类，如用于写入的ofstream类和用于读出的ifstream类
// 流状态检查，可以用if(fout.fail())，或者if(!fout.good())，或者(!fout)
// 新版C++，可以用fout.is_open()

// 一个文件流ofstream/ifstream可以关联多个文件，使用默认的构造函数构造ofstream/ifstream对象
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
	ifstream fin; // 使用默认构造函数
	fin.open(filename.c_str());
	cout << "Here are the contens: " << endl;
	char ch;
	while (fin.get(ch)) {
		cout << ch;
	}
	cout << "Done. \n";
	fin.clear();	// 有时程序不需要，但是永远无害
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



// 文件模式
// ios_base定义了一个openmode类型，用于表示模式，与fmtflags和iostate类型一样，bitmask类型
// ios_base::in（读取）		ios_base::out(写入)		ios_base::ate(打开并移动到文件尾)
// ios_base::app（追加）	ios_base::trunc（截短，即删除）	ios_base::binary(二进制)

// ifstream open()默认模式是ios_base::in
// ofstream open()默认模式是ios_base::out|ios_base::trunc
// fstream类不提供默认的模式值，因此需显示指出

//     C++ model				   C模式
// ios_base::in						"r"
// ios_base::out					"w"
// ios_base::out|ios_base::trunc	"w"
// ios_base::out|ios_base::app		"a"
// ios_base::out|ios_base::out		"r+"	文件读写，在文件允许的位置写入，打开文件后【不会】清空原有内容，写入会覆盖原有内容
// ios_base::out|ios_base::out|ios_base::trunc		"w+"	文件读写，在文件允许的位置写入，打开文件后【会】清空原有内容，写入会覆盖原有内容
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

// 二进制格式
// 文本格式方便读取以及不同OS之间传送
// 二进制格式对数字更为精确，因为其存储的是数值的内部表示，不会有误差，且保存速度较快，占用空间少，
// 但是不同系统之间可能因为内部表示不同，导致不方便传输

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


// seekg用于ifstream, seekp用于ofstream
// istream& seekg(seekoff, ios_base::seekdir):  seekoff是相对偏移位置，seekdir有三个值
//       ios_base::beg相对于文件开始的偏移，ios_base::cur相对于当前位置，ios_base::end相对于文件末尾
// istream& seekg(streampos)：定位到离文件开头特定距离

// 文件指针当前的位置可以通过tellg（用于输入流）和tellp（输出流）获得

// cstdio中的tmpname获取独一无二的文件名 char* tmpname(char* pzName)

int main1703(int argc, char *argv[]) {

	//append();

	binary();

	system("pause");
	return 0;
}