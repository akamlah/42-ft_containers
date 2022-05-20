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
void vector_pushback_int();

int main() {

	vector_pushback_int(); std::cout << std::endl;

	system("leaks test_ft_containers | tail -3");
	return (0);
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

#ifndef NB_ELEMENTS
#define NB_ELEMENTS 15
#endif

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

/* ------------------------------------------------------------------------ */

void vector_pushback_int(){
	std::cout << CYAN_B"----\t vector_pushback_int \t----" << NC << std::endl;
	ft::vector<TestClass> v;

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

	return ;
}

/* ------------------------------------------------------------------------ */
// end of tests
