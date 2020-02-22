#pragma once
#ifndef STRINGBAD_H
#define STRINGBAD_H
#include <iostream>

class StringBad {
private:
	char * str;
	int len;
	static int num_string;

public:
	StringBad(const char* str);
	StringBad();
	~StringBad();

	friend std::ostream& operator<<(std::ostream& os, const StringBad& strBad);

};




#endif // STRINGBAD
