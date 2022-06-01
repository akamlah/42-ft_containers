/* ************************************************************************ */
/*																			*/
/*				ft_containers: tests_type_traits_and_utils					*/
/*																			*/
/* ************************************************************************ */

#include "testing.hpp"
#include "../utility.hpp"

// in this file:
void pair();

/* ************************************************************************ */
// UTILS:
/* ************************************************************************ */

#ifndef _TestType1__
	// #define _TestType1__ TestClass
	#define _TestType1__ int
	// #define _TestType1__ double
	// #define _TestType1__ foo<int>
#endif

#ifndef _TestType2__
	#define _TestType2__ std::string
#endif

#ifndef _TestCont__
	// #define _TestCont__ std::deque
	#define _TestCont__ std::list
	// #define _TestCont__ _NS__::vector
#endif

/* ------------------------------------------------------------------------ */

template< typename T1, typename T2 >
void print_pair(const _NS__::pair< T1, T2 > p) {
	std::cout << p.first << " | " << p.second << std::endl;
}

// CALL ALL
void tests_type_traits_and_utils() {
	std::cout << MAGENTA_B "----\t TYPE & UTIL \t----" << NC << std::endl;

	// std::cout << "IS INTEGRAL: " << std::endl;
	// std::cout << "char: " << _NS__::is_integral<char>::value << std::endl;

	pair(); std::cout << std::endl;
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

void pair() {
	std::cout << CYAN_B"----\t pair \t----" << NC << std::endl;
	_NS__::pair<_TestType1__, _TestType2__> p1;
	_NS__::pair<_TestType1__, _TestType2__> p2(
		_TestType1__(3), _TestType2__("yo"));
	_NS__::pair<_TestType1__, _TestType2__> p3(p2);
	print_pair(p1);
	print_pair(p2);
	print_pair(p3);
	_NS__::pair<_TestType1__,_TestType2__>p4
		= _NS__::make_pair(_TestType1__(4), _TestType2__("yoyo"));
	print_pair(p4);
	std::cout << (p3 < p4) << " ";
	std::cout << (p3 < p2) << " ";
	std::cout << (p3 > p4) << " ";
	std::cout << (p3 > p2) << " ";
	std::cout << (p3 == p4) << " ";
	std::cout << (p3 == p2) << " ";
	std::cout << (p3 != p4) << " ";
	std::cout << (p3 != p2) << " ";
	std::cout << (p3 <= p4) << " ";
	std::cout << (p3 <= p2) << " ";
	std::cout << (p3 >= p4) << " ";
	std::cout << (p3 >= p2) << " ";
	std::cout << std::endl; // use diff for this
}

#undef _TestType1__
#undef _TestType2__
#undef _TestCont__
// end tests stack
