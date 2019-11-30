#include "ch12_1_StringBad.h"
#include <iostream>

using namespace std;

void calMem1(StringBad&);
void calMem2(StringBad);

int main1201(int argc, char* argv[]) {
	{
		std::cout << "Start inner block." << std::endl;
		StringBad headline1("Celery Stalks at Midnight");
		StringBad headline2("Lettuce prey.");
		StringBad sports("Golden Warrior.");

		std::cout << headline1 << std::endl;
		std::cout << headline2 << std::endl;
		std::cout << sports << std::endl;
		calMem1(headline1);
		std::cout << headline1 << std::endl;
		calMem2(headline2); // 报错，headline2以传参的形式传入，会导致调用析构函数
		//std::cout << headline2 << std::endl;

		//std::cout << "Initialize one object to another." << std::endl;
		//StringBad sailor = sports;
		//std::cout << "sailor: " << sailor << std::endl;

		//std::cout << "Assign one object to another." << std::endl;
		//StringBad knot;
		//knot = headline1;
		//std::cout << "knot: " << knot << std::endl;

		std::cout << "Exiting inner block." << std::endl;
	}
	std::cout << "End of main." << std::endl;
	system("pause");
	return 0;
}

void calMem1(StringBad& rfsb) {
	std::cout << "String pass by reference:\n";
	std::cout << "    \"" << rfsb << std::endl;
}

void calMem2(StringBad sb) {
	std::cout << "String pass by value:\n";
	std::cout << "    \"" << sb << std::endl;
}