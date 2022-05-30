#include "TestClass.hpp"

TestClass::TestClass() {
	#if DBG
	std::cout << "\033[38;5;204m" << __PRETTY_FUNCTION__;
	std::cout << ", object: " << this;
	std::cout << ", sizeof *this: " << sizeof(*this);
	std::cout << NC << std::endl;
	#endif
	_someValue = 1;
	_someStuffOnHeap = new int(77);
}
TestClass::TestClass(const int n) {
	#if DBG
	std::cout << "\033[38;5;204m" << __PRETTY_FUNCTION__ ;
	std::cout << ", object: " << this;
	std::cout << ", sizeof *this: " << sizeof(*this);
	std::cout << NC << std::endl;
	#endif
	_someValue = n;
	_someStuffOnHeap = new int(77);
}
TestClass::TestClass(const TestClass& other): _someValue(other._someValue) {
	_someStuffOnHeap = new int(77);
	#if DBG
	std::cout << "\033[38;5;204m" << __PRETTY_FUNCTION__;
	std::cout << ", object: " << this;
	std::cout << ", sizeof *this: " << sizeof(*this);
	std::cout << NC << std::endl;
	#endif
}
TestClass::~TestClass() {
	#if DBG
	std::cout << "\033[38;5;210m" << __PRETTY_FUNCTION__ ;
	std::cout << ", object: " << this;
	std::cout << NC << std::endl;
	#endif
	delete _someStuffOnHeap;
}
TestClass& TestClass::operator++() {
	#if DBG
	std::cout << "\033[38;5;210m" << __PRETTY_FUNCTION__ ;
	std::cout << ", object: " << this;
	std::cout << NC << std::endl;
	#endif
	*_someStuffOnHeap += 1;
	_someValue++;
	return (*this);
}
TestClass& TestClass::operator=(const TestClass& other) {
	#if DBG
	std::cout << "\033[38;5;209m" << "COPY " << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "\033[38;5;209m" << " | from " << &other << " to " << this;
	std::cout << NC << std::endl;
	#endif
	_someValue = other._someValue;
	return (*this);
}
int TestClass::getValue() const { return (_someValue); }
int TestClass::getHeapValue() const { return (*_someStuffOnHeap); }

std::ostream& operator<<(std::ostream& o, const TestClass& x) {
	o << x.getValue();// << "-" << x.getHeapValue();
	return (o);
}


