#include <iostream>
#include <sstream>
#include <iomanip> // for std::setprecision

using namespace std;

// iostream: 程序与终端之间的I/O
// fstream: 程序与文本之间的。。。
// sstream: 程序与字符串对象间的。。。
// 内核格式化：读取string对象的格式化信息或将格式化信息写入string对象

// sstream对象定义了ostringstream/wostringstream(继承自ostream/wostream)，其成员函数str()返回被初始化为缓冲区内容的
//        字符串对象，该方法可以“冻结”该对象，信息便不会写入该对象中（个人理解，该返回对象不能再被修改）
void strout(void) {
	ostringstream osout;
	string filename = "I am jack.";
	float fi_num = 145.436;
	//osout.precision(2);		//std::setprecision(2)
	osout << fixed;   // 使用定点计数法，不然使用的就是科学计数法
	osout << filename << " and I have the secert number " << fi_num << endl;
	//osout << filename << " and I have the secert number " << std::to_string(fi_num) << endl;
	string result = osout.str();
	cout << "result: " << result;
}

void strin(void) {

	string facts = "It was a dark and stormy day, and the full moon glowed brilliantly.";
	istringstream instr(facts);	// 用string对象初始化instr

	string word;
	while (instr >> word) {
		cout << word << " ";
	}
	cout << endl;
}


int main1704(int argc, char* argv[]) {
	//strout();
	strin();
	
	system("pause");
	return 0;
}