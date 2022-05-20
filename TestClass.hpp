#include <string>
#include <iostream>

class TestClass { /* ------------------------------------------------------ */
public:
	TestClass() {
		#if DBG
		std::cout << "\033[38;5;204m" << __PRETTY_FUNCTION__;
		std::cout << ", object: " << this;
		std::cout << ", sizeof *this: " << sizeof(*this);
		std::cout << NC << std::endl;
		#endif
		_someStuffOnHeap = new int(0);
	}
	TestClass(const int n) {
		#if DBG
		std::cout << "\033[38;5;204m" << __PRETTY_FUNCTION__ ;
		std::cout << ", object: " << this;
		std::cout << ", sizeof *this: " << sizeof(*this);
		std::cout << NC << std::endl;
		#endif
		_someValue = n;
		_someStuffOnHeap = new int(9);
	}
	TestClass(const TestClass& other): _someValue(other._someValue) {
		_someStuffOnHeap = new int(*other._someStuffOnHeap);
		#if DBG
		std::cout << "\033[38;5;204m" << __PRETTY_FUNCTION__;
		std::cout << ", object: " << this;
		std::cout << ", sizeof *this: " << sizeof(*this);
		std::cout << NC << std::endl;
		#endif
	}
	~TestClass() {
		#if DBG
		std::cout << "\033[38;5;210m" << __PRETTY_FUNCTION__ ;
		std::cout << ", object: " << this;
		std::cout << NC << std::endl;
		#endif
		delete _someStuffOnHeap;
	}
	TestClass& operator=(const TestClass& other) {
		#if DBG
		std::cout << "\033[38;5;209m" << "COPY " << __PRETTY_FUNCTION__ << std::endl;
		std::cout << "\033[38;5;209m" << " | from " << &other << " to " << this;
		std::cout << NC << std::endl;
		#endif
		_someValue = other._someValue;
		_someStuffOnHeap = other._someStuffOnHeap;
		return (*this);
	}
	int getValue() const { return (_someValue); }
	int getHeapValue() const { return (*_someStuffOnHeap); }
private:
	int _someValue;
	int* _someStuffOnHeap;
};

std::ostream& operator<<(std::ostream& o, const TestClass& x) {
	o << x.getValue();
	return (o);
}
