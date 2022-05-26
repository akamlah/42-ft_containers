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


#ifndef __TestType__
#define __TestType__ TestClass
// #define __TestType__ int
// #define __TestType__ double
#endif

/* ************************************************************************ */
// MAIN
/* ************************************************************************ */

/* tests in this file */
void vector_push_pop();
void vector_resize_reserve();
void vector_copies();
void vector_range_construct();
void vector_swap();
void vector_assign();
void vector_insert();
void vector_erase_range();
void vector_erase();
void vector_at();
void vector_comp_int();

int main() {

	vector_push_pop(); std::cout << std::endl;
	vector_resize_reserve(); std::cout << std::endl;
	vector_copies(); std::cout << std::endl;
	vector_range_construct(); std::cout << std::endl;
	vector_swap(); std::cout << std::endl;
	vector_assign(); std::cout << std::endl;
	vector_insert(); std::cout << std::endl;
	vector_erase_range(); std::cout << std::endl;
	vector_erase(); std::cout << std::endl;
	vector_at(); std::cout << std::endl;
	vector_comp_int(); std::cout << std::endl;

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
	ft::vector<__TestType__> v(10);
	v.pop_back();
	// info(v);
	v.push_back(__TestType__(777));
	info(v);
	v.push_back(__TestType__(888));
	info(v);
	v.push_back(__TestType__(999));
	info(v);
	v.push_back(__TestType__(111));
	info(v);
	v.push_back(__TestType__(222));
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
	// info(vct);
	// info(vct2);
	return ;
}

void vector_resize_reserve() {
	std::cout << CYAN_B"----\t vector_resize_reserve \t----" << NC << std::endl;
	ft::vector<__TestType__> v;

	v.resize(5);
	v.reserve(12);
	for (int i = 1; i < 21; i++) {
		v.push_back(__TestType__(i * 2));
	}
	info(v); // cap = 24, size 
	for (ft::vector<__TestType__>::size_type i = 0; i < v.size(); i++) {
		std::cout << "element[" << i << "] = " << v[i] << std::endl;
	}
	// try resize with count == size also
	v.resize(25);
	info(v); // cap = 24, size 
	v.resize(50);
	info(v); // cap = 50, size 50
	for (ft::vector<__TestType__>::size_type i = 1; i < v.size(); i++) {
		std::cout << "element[" << i << "] = " << v[i] << std::endl;
	}
	v.resize(5);
	info(v); // cap = 50, size 5
	for (int i = 1; i < 20; i++) {
		v.push_back(__TestType__(i * 2));
	}
	info(v); // cap 
	v.reserve(27);
	info(v); // cap =
	v.resize(5);

	std::cout << CYAN_B"----\t vector_resize_reserve TESTER \t----" << NC << std::endl;
	const int start_size = 7;
	ft::vector<int> vct(start_size, 20);
	ft::vector<int> vct2;
	ft::vector<int>::iterator it = vct.begin();

	for (int i = 2; i < start_size; ++i)
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

	vct2 = vct;
	vct.reserve(vct.capacity() + 1);
	info(vct);
	info(vct);

	vct2.resize(0);
	std::cout << "after resize 0: " << std::endl;
	info(vct);
}

void vector_copies() {
	std::cout << CYAN_B"----\t vector_copies \t----" << NC << std::endl;

	ft::vector<__TestType__> src;
	for (int i = 1; i < 21; i++) {
		src.push_back(__TestType__(i * 2));
	}
	info(src);
	for (unsigned int i = 0; i < src.size(); i++) {
		std::cout << src[i] << std::endl;
	}

	ft::vector<__TestType__> v(src);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << v[i] << std::endl;
	}
	info(v);

	ft::vector<__TestType__> v2; // test cpy to bigger
	for (int i = 1; i < 5; i++) {
		v2.push_back(__TestType__(i * 3));
	}
	info(v2);
	for (unsigned int i = 0; i < v2.size(); i++) {
		std::cout << v2[i] << std::endl;
	}
	v2 = src;
	info(v2);
	for (unsigned int i = 0; i < v2.size(); i++) {
		std::cout << v2[i] << std::endl;
	}

	// bug in std? weird stuff anyways... double free if cpy to bigger
	// ft::vector<__TestType__> v3; // test cpy to smaller
	// for (int i = 1; i < 50; i++) {
	// 	v3.push_back(__TestType__(i * 7));
	// }
	// info(v3);
	// // for (unsigned int i = 0; i < v3.size(); i++) {
	// // 	std::cout << v3[i] << std::endl;
	// // }
	// v3 = src;
	// info(v3);
	// for (unsigned int i = 0; i < v3.size(); i++) {
	// 	std::cout << v3[i] << std::endl;
	// }

}

void vector_range_construct() {
	std::cout << CYAN_B"----\t vector_range_construct \t----" << NC << std::endl;
	ft::vector<__TestType__> src;
	for (int i = 0; i < 10; i++) {
		src.push_back(__TestType__(i * 3));
	}
	for (int i = 0; i < 10; i++) {
		std::cout << src[i] << std::endl;
	}

	ft::vector<__TestType__> v(src.begin() + 2, src.begin() + 6);
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << v[i] << std::endl;
	}
}

void vector_swap() {
	std::cout << CYAN_B"----\t vector_swap \t----" << NC << std::endl;
	ft::vector<__TestType__> foo(3, 15);
	ft::vector<__TestType__> bar(5, 42);
	
	ft::vector<__TestType__>::const_iterator it_foo = foo.begin();
	ft::vector<__TestType__>::const_iterator it_bar = bar.begin();

	std::cout << "BEFORE SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	info(foo);
	std::cout << "bar contains:" << std::endl;
	info(bar);

	foo.swap(bar);

	std::cout << "AFTER SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	info(foo);
	std::cout << "bar contains:" << std::endl;
	info(bar);

	std::cout << "Iterator validity:" << std::endl;
	std::cout << (it_foo == bar.begin()) << std::endl;
	std::cout << (it_bar == foo.begin()) << std::endl;
}

void vector_assign() {
	std::cout << CYAN_B"----\t vector_assign \t----" << NC << std::endl;
	ft::vector<__TestType__> v;
	unsigned int size = 20;
	for (unsigned int i = 0; i < size; i++) {
		v.push_back(__TestType__(i * 2));
	}

	std::cout << CYAN" - \t assign n \t----" << NC << std::endl;
	// CASE 1 : n < size -> first n values get replaced by value given
	std::cout << CYAN << "n < size < capacity:" << NC << std::endl;
	v.assign(5, __TestType__(-1));
	info(v); // (cap = 32 std)
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}
	// CASE 2 : n > size < capacity -> all repaced & filled up to n
	std::cout << CYAN << "size < n < capacity:" << NC << std::endl;
	v.assign(30, __TestType__(-1));
	info(v); // (cap = 32 std)
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}
	// CASE 3 : n > size < capacity -> all repaced and cap increased
	std::cout << CYAN << "size < capacity < n:" << NC << std::endl;
	v.assign(40, __TestType__(-1));
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}

	std::cout << CYAN" - \t assign range \t----" << NC << std::endl;
	ft::vector<__TestType__> src;
	unsigned int src_size = 50;
	for (unsigned int i = 0; i < src_size; i++) {
		src.push_back(__TestType__(i * 3));
	}
	info(v); // (cap = 32 std)
	for (unsigned int i = 0; i < src.size(); i++) {
		if (i < v.size())
			std::cout << "i: " << i \
			<< " | v: " << v[i] \
			<< " | src: " << src[i] << std::endl;
		else
			std::cout << "i: " << i \
			<< " | v: " << "-" \
			<< " | src: " << src[i] << std::endl;
	}
	// CASE 1 : range span smaller than size -> size cut to span and replace
	std::cout << CYAN << "range < size" << NC << std::endl;
	v.assign(src.begin(), src.begin() + 4);
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}
	// CASE 2 : size < range < capacity -> filled up to span 
	std::cout << CYAN << "size < range < capacity" << NC << std::endl;
	v.assign(src.begin(), src.begin() + 10);
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}
	// CASE 3 : size < capacity < range -> realloc to fit & filled
	std::cout << CYAN << "size < capacity < range" << NC << std::endl;
	v.assign(src.begin(), src.begin() + 40);
	info(v);
	for (unsigned int i = 0; i < src.size(); i++) {
		if (i < v.size())
			std::cout << "i: " << i \
			<< " | v: " << v[i] \
			<< " | src: " << src[i] << std::endl;
		else
			std::cout << "i: " << i \
			<< " | v: " << "-" \
			<< " | src: " << src[i] << std::endl;
	}
}

void vector_insert() {
	std::cout << CYAN_B"----\t vector_insert \t----" << NC << std::endl;
	ft::vector<__TestType__> v;
	unsigned int size = 20;
	for (unsigned int i = 0; i < size; i++) {
		v.push_back(__TestType__(i * 2));
	}
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}
	std::cout << *(v.insert(v.begin() + 5, __TestType__(-1))) << std::endl;
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}
	// invalid ite ?
	// std::cout << *(v.insert(v.begin() - 1, __TestType__(-1))) << std::endl;
	// info(v); // (cap = 32 std)
	// for (unsigned int i = 0; i < v.size(); i++) {
	// 	std::cout << "i: " << i \
	// 	<< " | v: " << v[i] << std::endl;
	// }
	std::cout << *(v.insert(v.end(), __TestType__(-1))) << std::endl;
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}
	v.insert(v.begin() + 4, 7, __TestType__(-2));
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}
	v.insert(v.end(), 7, __TestType__(-2));
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}
	ft::vector<__TestType__> vct(10);
	ft::vector<__TestType__> vct2;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	info(vct);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	info(vct2);

	vct2.insert(vct2.end() - 2, 42);
	info(vct2);

	vct2.insert(vct2.end(), 2, 84);
	info(vct2);

	vct2.resize(4);
	info(vct2);

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	info(vct2);

	info(vct);
}

void vector_erase_range() {
	std::cout << CYAN_B"----\t vector_erase_range \t----" << NC << std::endl;
	ft::vector<__TestType__> v;
	unsigned int size = 20;
	for (unsigned int i = 0; i < size; i++) {
		v.push_back(__TestType__(i));
	}
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}

	// std erase sagfaults if end of range not in vector.
	// if starts earlier its weird, behaves as if it would sum and shift the randge:
	// 	v.erase(v.begin() - 3, v.begin() + 10);
	// ^ deletes first 13 elements
	// => not my job to check if finish < _end_size in my vector.
	// i can suppose that last is before ar at most equal to _end_size;
	
	// range = 1
	std::cout << *(v.erase(v.begin() + 2, v.begin() + 3)) << std::endl;	
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}

	// normal
	std::cout << *(v.erase(v.begin() + 2, v.begin() + 10)) << std::endl;	
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}

	// case: last == end
	std::cout << *(v.erase(v.begin() + 5, v.end())) << std::endl;	
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}

	// // case: first == begin
	std::cout << *(v.erase(v.begin(), v.begin() + 2)) << std::endl;	
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}

	// // case: iterators are same
	std::cout << *(v.erase(v.begin(), v.begin())) << std::endl;	
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}

// no comp test: IN MY OPINION OKAY BUT != STD

	// std::cout << *(v.erase(v.begin() - 3, v.begin() + 10)) << std::endl;	
	// info(v);
	// for (unsigned int i = 0; i < v.size(); i++) {
	// 	std::cout << "i: " << i \
	// 	<< " | v: " << v[i] << std::endl;
	// }
}

void vector_erase() {
	std::cout << CYAN_B"----\t vector_erase \t----" << NC << std::endl;
	ft::vector<__TestType__> v;
	unsigned int size = 20;
	for (unsigned int i = 0; i < size; i++) {
		v.push_back(__TestType__(i));
	}
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}

	// normal
	std::cout << *(v.erase(v.begin() + 2)) << std::endl;
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}

	// // case: pos == begin -> erase first
	std::cout << *(v.erase(v.begin())) << std::endl;	
	info(v);
	for (unsigned int i = 0; i < v.size(); i++) {
		std::cout << "i: " << i \
		<< " | v: " << v[i] << std::endl;
	}

// NOTEST COMP
	// case: pos < begin -> erases first two -> UNDEF
	// std::cout << *(v.erase(v.begin() - 2)) << std::endl;
	// info(v);
	// for (unsigned int i = 0; i < v.size(); i++) {
	// 	std::cout << "i: " << i \
	// 	<< " | v: " << v[i] << std::endl;
	// }
	// case: pos == end -> segfaults in std
	// std::cout << *(v.erase(v.end())) << std::endl;
	// info(v);
	// for (unsigned int i = 0; i < v.size(); i++) {
	// 	std::cout << "i: " << i \
	// 	<< " | v: " << v[i] << std::endl;
	// }
	// case: pos > end -> segfaults in std
	// std::cout << *(v.erase(v.end() + 5)) << std::endl;
	// info(v);
	// for (unsigned int i = 0; i < v.size(); i++) {
	// 	std::cout << "i: " << i \
	// 	<< " | v: " << v[i] << std::endl;
	// }
}

void vector_at() {
	std::cout << CYAN_B"----\t vector_at \t----" << NC << std::endl;
	ft::vector<__TestType__> vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct.at(): " << vct.at(i) << " | ";
		std::cout << "vct[]: " << vct[i] << std::endl;
	}
	info(vct);

	ft::vector<__TestType__> const vct_c(vct);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

	try {
		vct.at(10) = 42;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}
}

void vector_comp_int() {
	std::cout << CYAN_B"----\t vector_comp_int \t----" << NC << std::endl;
	ft::vector<int> v1;
	ft::vector<int> v2;
	ft::vector<int, std::allocator<int> > v3;
	unsigned int size = 20;
	for (unsigned int i = 0; i < size; i++) {
		v1.push_back(int(i));
	}
	for (unsigned int i = 0; i < size; i++) {
		v2.push_back(int(i));
	}
	// v3: same up to size and then different in 10 more elements
	for (unsigned int i = 0; i < size; i++) {
		v3.push_back(int(i));
	}
	for (unsigned int i = 0; i < 10; i++) {
		v3.push_back(int(i * 217));
	}

	info(v1);
	info(v2);
	info(v3);
	for (unsigned int i = 0; i < v1.size(); i++) {
		std::cout << "i: " << i \
		<< " | v1: " << v1[i] \
		<< " | v2: " << v2[i] \
		<< " | v3: " << v3[i] \
		<< std::endl;
	}
	std::cout << std::endl;
	std::cout << "v1 == v2: " << (v1 == v2) << std::endl;
	std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
	std::cout << "v1 == v1: " << (v1 == v1) << std::endl;
	std::cout << std::endl;
	std::cout << "v1 != v2: " << (v1 != v2) << std::endl;
	std::cout << "v1 != v3: " << (v1 != v3) << std::endl;
	std::cout << "v1 != v1: " << (v1 != v1) << std::endl;
	std::cout << std::endl;
	std::cout << "v1 < v2: " << (v1 < v2) << std::endl;
	std::cout << "v1 < v3: " << (v1 < v3) << std::endl;
	std::cout << "v1 < v1: " << (v1 < v1) << std::endl;
	std::cout << std::endl;
	std::cout << "v1 > v2: " << (v1 > v2) << std::endl;
	std::cout << "v1 > v3: " << (v1 > v3) << std::endl;
	std::cout << "v1 > v1: " << (v1 > v1) << std::endl;
	std::cout << std::endl;
	std::cout << "v1 <= v2: " << (v1 <= v2) << std::endl;
	std::cout << "v1 <= v3: " << (v1 <= v3) << std::endl;
	std::cout << "v1 <= v1: " << (v1 <= v1) << std::endl;
	std::cout << std::endl;
	std::cout << "v1 >= v2: " << (v1 >= v2) << std::endl;
	std::cout << "v1 >= v3: " << (v1 >= v3) << std::endl;
	std::cout << "v1 >= v1: " << (v1 >= v1) << std::endl;



}
/* ------------------------------------------------------------------------ */
// end of tests
