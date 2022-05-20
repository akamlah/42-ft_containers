/* ************************************************************************ */
/*																			*/
/*							ft_containers: tests							*/
/*																			*/
/* ************************************************************************ */

#include <string>
#include <iostream>
#include <vector>
#include "vector.hpp"
#include "ANSIpalette.h"
#include <cassert>

/* ------------------------------------------------------------------------ */
// "make std" defines STD=true and containers get compiled as std::*
#if STD
#define ft std
#endif

#ifndef NB_ELEMENTS
#define NB_ELEMENTS 15
#endif

/* ------------------------------------------------------------------------ */
/* tests in this file */
void vector_pushback_int();
void vector_pushback_TC();
void vector_popback();
void vector_iterators_basic();
void vector_swap_and_copies();
void vector_resize();
// +TestClass

/* ************************************************************************ */
// MAIN
/* ************************************************************************ */
void tests() {
	// vector_pushback_int(); std::cout << std::endl;
	// vector_pushback_TC(); std::cout << std::endl;
	// vector_popback(); std::cout << std::endl;
	// vector_iterators_basic(); std::cout << std::endl;
	vector_swap_and_copies(); std::cout << std::endl;
	vector_resize(); std::cout << std::endl;
}
int main() {
	tests();
	system("leaks test_ft_containers | tail -3");
	// system("leaks test_ft_containers");
	return (0);
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

void vector_pushback_int(){
	std::cout << CYAN_B"----\t vector_pushback_int \t----" << NC << std::endl;
	ft::vector<int> v;
	v.push_back(5);
	v.push_back(6);
	v.push_back(9);
	v.push_back(8);
	std::cout << "size: " << v.size() << " capacity: " << v.capacity() << std::endl;
	v.push_back(2);
	#if (!STD && DBG)
	v.peek();
	#endif
	std::cout << "size: " << v.size() << " capacity: " << v.capacity() << std::endl;
	std::cout << "element[4]: " << v[4] << std::endl;
	v[4] += 3;
	std::cout << "element[4] + 3: " << v[4] << std::endl;
	#if (!STD && DBG)
	v.peek();
	#endif
	return ;
}

/* ------------------------------------------------------------------------ */
// teast2: with test class for COPY DEBUG
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
// testclass ^^
/* ------------------------------------------------------------------------ */

void vector_pushback_TC() {
	std::cout << CYAN_B"----\t vector_pushbackTC \t----" << NC << std::endl;
	ft::vector<TestClass> v;

	// same amount of copies  ^^
		TestClass t1(7);
		std::cout << v.capacity() << std::endl;
		#if (!STD && DBG)
	
			v.peek(); 
			std::cout  << "pb"<< std::endl;
		#endif
		v.push_back(t1);
		std::cout << v.capacity() << std::endl;
		#if (!STD && DBG)
	
			v.peek();
			std::cout << "pb" << std::endl;
		#endif
		v.push_back(TestClass(2));
		std::cout << v.capacity() << std::endl;
		#if (!STD && DBG)
	
			v.peek();
			std::cout << "pb" << std::endl;
		#endif
		v.push_back(TestClass(4));
		std::cout << v.capacity() << std::endl;
		#if (!STD && DBG)
	
			v.peek();
			std::cout << "pb" << std::endl;
		#endif
		v.push_back(TestClass(5));
		std::cout << v.capacity() << std::endl;
		#if (!STD && DBG)	
			v.peek();
			std::cout << "pb" << std::endl;
		#endif
		v.push_back(TestClass(5));
		std::cout << v.capacity() << std::endl;
		#if (!STD && DBG)
	
			v.peek();
			std::cout << "pb" << std::endl;
		#endif
		v.push_back(TestClass(7));
		std::cout << v.capacity() << std::endl;
		#if (!STD && DBG)

		v.peek();
		std::cout << std::endl;
		#endif
}

/* ------------------------------------------------------------------------ */

void vector_popback(){
	std::cout << CYAN_B"----\t vector_popback \t----" << NC << std::endl;
	ft::vector<TestClass> v;

	srand(std::time(NULL));
	for (ft::vector<TestClass>::size_type i = 0; i < NB_ELEMENTS; i++) {
		v.push_back(TestClass(rand()));
	}
	#if (!STD && DBG)
		v.peek();
	#endif
	if (v.empty())
		std::cout << "empty" << std::endl;
	for (ft::vector<TestClass>::size_type i = 0; i < NB_ELEMENTS / 10; i++) {
		v.pop_back();
	}
	#if (!STD && DBG)
		v.peek();
	#endif
	v.clear();
	#if (!STD && DBG)
		v.peek();
	#endif
	if (v.empty())
		std::cout << "empty" << std::endl;
}

template<typename T>
class testvector: public std::vector<TestClass, ft::allocator<TestClass> > {
	public:
		const_iterator begin() const {
			std::cout << PF << std::endl;
			return std::vector<TestClass, ft::allocator<TestClass> >::begin();
		}
		iterator begin() {
			std::cout << PF << std::endl;
			return std::vector<TestClass, ft::allocator<TestClass> >::begin();
		}
};

void vector_iterators_basic(){
	std::cout << CYAN_B"----\t vector_iterators \t----" << NC << std::endl;
	ft::vector<TestClass> v;
	v.reserve(8);
	std::cout << v.capacity() << std::endl;

	srand(std::time(NULL));
	for (ft::vector<TestClass>::size_type i = 0; i < NB_ELEMENTS; i++) {
		// v.push_back(TestClass(rand()));
		v.push_back(i);
	}
	std::cout << "begin: " << *v.begin() << " " << std::endl;
	std::cout << "end - 1: " << *(v.end() - 1) << " " << std::endl;
	#if (!STD && DBG)
		// v.peek();
	#endif

	for (ft::vector<TestClass>::size_type i = 0; i < NB_ELEMENTS / 10; i++) {
		v.pop_back();
	}
	std::cout << "begin: " << *v.begin() << " "  << std::endl;
	std::cout << "end - 1: " << *(v.end() - 1) << " " << std::endl;
	#if (!STD && DBG)
		// v.peek();
	#endif
	ft::vector<TestClass>::const_iterator it = v.begin();
	std::cout << "c it begin: " << *it << " " << std::endl;
	std::cout << "begin: " << *v.begin() << " " << std::endl;
	std::cout << "end - 1: " << *(v.end() - 1) << " "<< std::endl;
	std::cout << *it++;
	// ^^ << v.begin() does not compile in std::vector
	#if (!STD && DBG)
		// v.peek();
	#endif
	// std::cout << "\nSTD VECTOR: " << std::endl;
	// testvector<TestClass> mirror;
	// srand(std::time(NULL));
	// for (ft::vector<TestClass>::size_type i = 0; i < NB_ELEMENTS; i++) {
	// 	mirror.push_back(TestClass(rand()));
	// }
	// std::vector<TestClass>::const_iterator mit = mirror.begin();
	// std::cout << "c it begin: " << *mit++ << " " << &mit++ << std::endl;
	std::cout << "max_size: " << v.max_size() << std::endl;
	std::cout << "front: " << v.front() << std::endl;

}

/* ------------------------------------------------------------------------ */

template<typename T>
void info(ft::vector<T>& v) {
	std::cout << *v.begin() << " ";
	std::cout << *(v.end() - 1) << " ";
	std::cout << v.size() << " ";
	std::cout << v.capacity() << " ";
	std::cout << v.max_size() << " ";
	std::cout << v.front() << " ";
	std::cout << v.back() << " ";
	std::cout << std::endl;
} // this without & gices double free -> something's wrong with my destructor.

void vector_swap_and_copies(){
	std::cout << CYAN_B"----\t vector_swap_and_copies \t----" << NC << std::endl;
	ft::vector<TestClass> v;
	ft::vector<TestClass> w;

	for (ft::vector<TestClass>::size_type i = 0; i < NB_ELEMENTS; i++) {
		v.push_back(i);
		w.push_back(i + 100);
	}
	// #if (!STD && DBG)
	// #if (!STD)
	// 	v.peek();
	// 	w.peek();
	// #endif
	info(v);
	info(w);
	v.swap(w);
	// #if (!STD && DBG)
	// #if (!STD)
	// 	v.peek();
	// 	w.peek();
	// #endif
	info(v);
	info(w);
}

/* ------------------------------------------------------------------------ */

void vector_resize(){
	std::cout << CYAN_B"----\t vector_resize \t----" << NC << std::endl;
	ft::vector<TestClass> v;

	for (ft::vector<TestClass>::size_type i = 0; i < NB_ELEMENTS; i++) {
		v.push_back(i);
	}
	info(v);
	// 	#if (!STD)
	// 	v.peek();
	// #endif

	v.resize(5);
	info(v);
	// #if (!STD && DBG)
	// 	#if (!STD)
	// 	v.peek();
	// #endif

	// for (ft::vector<TestClass>::size_type i = 0; i < NB_ELEMENTS * 2; i++) {
	// 	v.push_back(i);
	// }
	// info(v);

	v.resize(10);
	info(v);
	// #if (!STD)
	// 	v.peek();
	// #endif

	v.resize(NB_ELEMENTS, TestClass(77));
	info(v);
	// #if (!STD && DBG)
	// #if (!STD)
	// 	v.peek();
	// #endif
}