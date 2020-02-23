#define _CRT_SECURE_NO_WARNINGS

#include "ch12_1_StringBad.h"

int StringBad::num_string = 0;

StringBad::StringBad(const char* s) {
	len = strlen(s);
	str = new char[len + 1];
	std::strcpy(str, s);
	num_string++;
	std::cout << num_string << ": \" " << str << " \" object created." << std::endl;
}

StringBad::StringBad() {
	len = 4;
	str = new char[4];
	std::strcpy(str, "C++");
	num_string++;
	std::cout << num_string << ": \" " << str << " \" default object created." << std::endl;
}

StringBad::~StringBad() {
	std::cout << "\" " << str << " \" object deleted. And ";
	--num_string;
	delete [] str;
	std::cout << num_string << " left." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const StringBad& strBad) {
	os << strBad.str;
	return os;
}