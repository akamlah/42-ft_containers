#ifndef TESTCLASS_HPP
# define TESTCLASS_HPP

#include <string>
#include <iostream>
#include "ANSIpalette.h"

class TestClass { /* ------------------------------------------------------ */

public:

	TestClass();
	TestClass(const int n);
	TestClass(const TestClass& other);
	~TestClass();

	TestClass& operator++();
	TestClass& operator=(const TestClass& other);

	int getValue() const;
	int getHeapValue() const;

private:

	int _someValue;
	int* _someStuffOnHeap;

};

bool operator==(const TestClass& lhs, const TestClass& rhs);
bool operator!=(const TestClass& lhs, const TestClass& rhs);
bool operator<(const TestClass& lhs, const TestClass& rhs);
bool operator>(const TestClass& lhs, const TestClass& rhs);
bool operator<=(const TestClass& lhs, const TestClass& rhs);
bool operator>=(const TestClass& lhs, const TestClass& rhs);

std::ostream& operator<<(std::ostream& o, const TestClass& x);

#endif // TESTCLASS_HPP
