#include <iostream>
#include <vector>

using namespace std;


// ģ����
// 1. vector���Խ�һ��vector��ֵ����һ��
// 2. ��ִ�еĲ�����
//	 size():  ����Ԫ����Ŀ
//   swap():  ������������������
//   begin()/end():  ����ָ���һ�������ĵ�����/��������β�ĵ�������������������ָ�룬Ҳ�����Ƕ���ִ������ָ��Ĳ�����
void vectorUsage(void) {
	vector<int> a = { 1,2,3,4,5 };
	vector<int> b = a;
	for (int i = 0; i < b.size(); i++) {
		cout << " " << b[i];
	}
	cout << endl;
}

int main1603(int argc, int *argv[]) {

	vectorUsage();

	system("pause");
	return 0;
}