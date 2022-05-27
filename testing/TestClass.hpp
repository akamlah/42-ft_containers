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
		_someValue = 1;
		_someStuffOnHeap = new int(77);
	}
	TestClass(const int n) {
		#if DBG
		std::cout << "\033[38;5;204m" << __PRETTY_FUNCTION__ ;
		std::cout << ", object: " << this;
		std::cout << ", sizeof *this: " << sizeof(*this);
		std::cout << NC << std::endl;
		#endif
		_someValue = n;
		_someStuffOnHeap = new int(77);
	}
	TestClass(const TestClass& other): _someValue(other._someValue) {
		_someStuffOnHeap = new int(77);
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
	TestClass& operator++() {
		#if DBG
		std::cout << "\033[38;5;210m" << __PRETTY_FUNCTION__ ;
		std::cout << ", object: " << this;
		std::cout << NC << std::endl;
		#endif
		*_someStuffOnHeap += 1;
		_someValue++;
		return (*this);
	}
	TestClass& operator=(const TestClass& other) {
		#if DBG
		std::cout << "\033[38;5;209m" << "COPY " << __PRETTY_FUNCTION__ << std::endl;
		std::cout << "\033[38;5;209m" << " | from " << &other << " to " << this;
		std::cout << NC << std::endl;
		#endif
		_someValue = other._someValue;
		return (*this);
	}
	int getValue() const { return (_someValue); }
	int getHeapValue() const { return (*_someStuffOnHeap); }
private:
	int _someValue;
	int* _someStuffOnHeap;
};

std::ostream& operator<<(std::ostream& o, const TestClass& x) {
	o << x.getValue();// << "-" << x.getHeapValue();
	return (o);
}


// --- Class foo
template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo
