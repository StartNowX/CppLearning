#include <iostream>
#include <sstream>
#include <iomanip> // for std::setprecision

using namespace std;

// iostream: �������ն�֮���I/O
// fstream: �������ı�֮��ġ�����
// sstream: �������ַ��������ġ�����
// �ں˸�ʽ������ȡstring����ĸ�ʽ����Ϣ�򽫸�ʽ����Ϣд��string����

// sstream��������ostringstream/wostringstream(�̳���ostream/wostream)�����Ա����str()���ر���ʼ��Ϊ���������ݵ�
//        �ַ������󣬸÷������ԡ����ᡱ�ö�����Ϣ�㲻��д��ö����У�������⣬�÷��ض������ٱ��޸ģ�
void strout(void) {
	ostringstream osout;
	string filename = "I am jack.";
	float fi_num = 145.436;
	//osout.precision(2);		//std::setprecision(2)
	osout << fixed;   // ʹ�ö������������Ȼʹ�õľ��ǿ�ѧ������
	osout << filename << " and I have the secert number " << fi_num << endl;
	//osout << filename << " and I have the secert number " << std::to_string(fi_num) << endl;
	string result = osout.str();
	cout << "result: " << result;
}

void strin(void) {

	string facts = "It was a dark and stormy day, and the full moon glowed brilliantly.";
	istringstream instr(facts);	// ��string�����ʼ��instr

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