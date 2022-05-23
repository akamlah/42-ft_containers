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
#include "TestClass.hpp"
#include <cassert>

#if STD
#define ft std
#endif

/* ************************************************************************ */
// MAIN
/* ************************************************************************ */

/* tests in this file */
void vector_push_pop();
void vector_resize_reserve();
void vector_insertions();

int main() {

	// vector_push_pop(); std::cout << std::endl;
	vector_resize_reserve(); std::cout << std::endl;
	// vector_insertions(); std::cout << std::endl;

	system("leaks test_ft_containers | tail -3");
	// system("leaks test_ft_containers");
	return (0);
}

/* ************************************************************************ */
// TESTS: UTILS
/* ************************************************************************ */

#ifndef NB_ELEMENTS
#define NB_ELEMENTS 15
#endif

// + TestClas.hpp

template<typename T>
void info(ft::vector<T>& v) {
	std::cout << "*begin: " << *v.begin() << ", ";
	std::cout << "*end - 1: " << *(v.end() - 1) << ", ";
	std::cout << "size: " << v.size() << ", ";
	std::cout << "capacity: " << v.capacity() << ", ";
	// std::cout << "max size: " << v.max_size() << ", ";
	std::cout << "front: " << v.front() << ", ";
	std::cout << "back: " << v.back() << ", ";
	std::cout << "empty?: " << v.empty() << ", ";
	std::cout << std::endl;
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

void vector_push_pop(){
	std::cout << CYAN_B"----\t vector_push_pop \t----" << NC << std::endl;
	ft::vector<TestClass> v(10);
	v.pop_back();
	// info(v);
	v.push_back(TestClass(777));
	info(v);
	v.push_back(TestClass(888));
	info(v);
	v.push_back(TestClass(999));
	info(v);
	v.push_back(TestClass(111));
	info(v);
	v.push_back(TestClass(222));
	info(v);
	std::cout << "access[3]: " << v[3] << std::endl;
	v.pop_back();
	info(v);
	v.pop_back();
	info(v);
	v.pop_back();
	info(v);
	v.pop_back();
	info(v);
	v.pop_back();
	info(v);
	v.pop_back();
	info(v);

	ft::vector<std::string> vct(8);
	ft::vector<std::string> vct2;
	ft::vector<std::string>::iterator it = vct.begin();
	// info(vct);
	// info(vct2);
	for (unsigned long int i = 0; i < vct.size(); ++i)
		it[i] = std::string((vct.size() - i), i + 65);
	std::cout << "push_back():\n" << std::endl;
	vct.push_back("One long string");
	vct2.push_back("Another long string");
	info(vct);
	info(vct2);
	vct.pop_back();
	vct2.pop_back();
	info(vct);
	info(vct2);
	return ;
}

void vector_resize_reserve() {
	std::cout << CYAN_B"----\t vector_resize_reserve \t----" << NC << std::endl;
	ft::vector<TestClass> v;

	v.resize(5);
	v.reserve(12);
	for (int i = 1; i < 21; i++) {
		v.push_back(TestClass(i * 2));
	}
	info(v); // cap = 24, size 
	for (ft::vector<TestClass>::size_type i = 0; i < v.size(); i++) {
		std::cout << "element[" << i << "] = " << v[i] << std::endl;
	}
	// try resize with count == size also
	v.resize(25);
	info(v); // cap = 24, size 
	v.resize(50);
	info(v); // cap = 50, size 50
	for (ft::vector<TestClass>::size_type i = 1; i < v.size(); i++) {
		std::cout << "element[" << i << "] = " << v[i] << std::endl;
	}
	v.resize(5);
	info(v); // cap = 50, size 5
	for (int i = 1; i < 20; i++) {
		v.push_back(TestClass(i * 2));
	}
	info(v); // cap 
	v.reserve(27);
	info(v); // cap =
	v.resize(5);

	const unsigned int start_size = 7;
	ft::vector<int> vct(start_size, 20);
	ft::vector<int> vct2;
	ft::vector<int>::iterator it = vct.begin();

	for (unsigned int i = 2; i < start_size; ++i)
		it[i] = (start_size - i) * 3;
	info(vct);

	vct.resize(10, 42);
	info(vct);

	vct.resize(18, 43);
	info(vct);
	vct.resize(10);
	info(vct);
	vct.resize(23, 44);
	info(vct);
	vct.resize(5);
	info(vct);
	vct.reserve(5);
	vct.reserve(3);
	info(vct);
	vct.resize(87);
	vct.resize(5);
	info(vct);

	// vct2 = vct;
	vct.reserve(vct.capacity() + 1);
	info(vct);
	info(vct);

	vct2.resize(0);
	info(vct);
}

void vector_insertions() {
	std::cout << CYAN_B"----\t vector_insertions \t----" << NC << std::endl;

}

/* ------------------------------------------------------------------------ */
// end of tests
