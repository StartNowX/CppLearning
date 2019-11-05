#include <iostream>
#include <vector>

using namespace std;

void print_vector(const std::vector<int>& a) {
	for (std::vector<int>::const_iterator it = a.begin(); it != a.end(); ++it) {
		printf("a element is %d\n", *it);
	}

	for (auto it = a.cbegin(); it != a.cend(); ++it) {
		std::cout << "const element is " << *it << std::endl;
	}

}

int main000_test(int argc, char* argv[]) {

	std::vector<int> a_vec(4, 1);
	print_vector(a_vec);

	long double ld = 3.1415926536;
	//int a{ ld }, b = { ld };
	int c(ld), d = ld;

	char c_array[] = "Child";
	std::cout << "c_array len = " << sizeof(c_array) / sizeof(char) << endl;

	const unsigned buf_size = 1024;
	int ia[buf_size] = {0};

	system("pause");
	return 0;
}