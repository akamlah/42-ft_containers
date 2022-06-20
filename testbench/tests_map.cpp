/* ************************************************************************ */
/*																			*/
/*						ft_containers: test map								*/
/*																			*/
/* ************************************************************************ */

#include "testing.hpp"
#include "../rb_tree.hpp"
//TEST ONLY

#include <map>

void tree_build();

/* ************************************************************************ */
// UTILS:
/* ************************************************************************ */

#ifndef _TestType1__
#	define _TestType1__ TestClass
// #	define _TestType1__ int
// #	define _TestType1__ double
// #	define _TestType1__ foo<int>
#endif

#ifndef _TestType2__
#	define _TestType2__ std::string
#endif

#ifndef _TestCont__
// #	define _TestCont__ std::deque
#	define _TestCont__ std::list
// #	define _TestCont__ _NS::vector
#endif

// #define __PAIR__ ft::pair
#define __PAIR__ std::pair
// #define __MAP__ std::map
#define __MAP__ ft::map
/* ------------------------------------------------------------------------ */

// CALL ALL
void test_map() {
	std::cout << MAGENTA_B "----\t MAP \t----" << NC << std::endl;
	tree_build(); std::cout << std::endl;
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

void tree_build() {
	std::cout << CYAN_B"----\t tree_build \t----" << NC << std::endl;
	ft::rb_tree	<_TestType1__> T;
	T.insert(_TestType1__(99));
	T.print_tree();
	T.insert(_TestType1__(8));
	T.print_tree();
	T.insert(_TestType1__(3));
	T.print_tree();
	T.insert(_TestType1__(128));
	T.print_tree();
	T.insert(_TestType1__(11));
	T.print_tree();
	T.insert(_TestType1__(2));
	T.print_tree();
	T.insert(_TestType1__(3785678));
	T.print_tree();
	T.insert(_TestType1__(10));
	T.print_tree();
	T.insert(_TestType1__(80));
	T.print_tree();
	T.insert(_TestType1__(111));
	T.print_tree();
	T.insert(_TestType1__(110));
	T.print_tree();
	T.insert(_TestType1__(70));
	T.print_tree();
	T.insert(_TestType1__(13));
	T.print_tree();
	T.insert(_TestType1__(67));
	T.print_tree();
	T.insert(_TestType1__(49));
	T.print_tree();
	T.insert(_TestType1__(45));
	T.print_tree();
	T.insert(_TestType1__(5476));
	T.print_tree();
	T.insert(_TestType1__(23));
	T.print_tree();
	T.insert(_TestType1__(25));
	T.print_tree();
	T.insert(_TestType1__(144));
	T.print_tree();
	T.insert(_TestType1__(143));
	T.print_tree();
	T.insert(_TestType1__(145));
	T.print_tree();
	T.insert(_TestType1__(999));
	T.print_tree();

	std::cout << "-----------------------" << std::endl;
	std::cout << "MIN: " << T.min()->value << " " << std::endl;
	std::cout << "MAX: " << T.max()->value << " " << std::endl;
	std::cout << "SEARCH 2: " << T.search(2) << " " << std::endl;
	std::cout << "SUCCESSOR 143: " << T.successor(143) << " " << T.successor(143)->value << " " << std::endl;
	std::cout << "SUCCESSOR 3785678: " << T.successor(3785678) << " " << std::endl;
	std::cout << "SUCCESSOR 99: " << T.successor(99) << " " << T.successor(99)->value << " " << std::endl;
	std::cout << "SUCCESSOR 11: " << T.successor(11) << " " << T.successor(11)->value << " " << std::endl;
	std::cout << "PREDECESSOR 11: " << T.predecessor(11) << " " << T.predecessor(11)->value << " " << std::endl;
	std::cout << "-----------------------" << std::endl;

	T.erase(11);
	T.print_tree();
	std::cout << "-----------------------" << std::endl;
	T.erase(8);
	T.print_tree();
	std::cout << "-----------------------" << std::endl;
	T.erase(111);
	T.print_tree();
	std::cout << "-----------------------" << std::endl;
	T.erase(143);
	T.print_tree();
	std::cout << "-----------------------" << std::endl;
}


// compiles:
	// std::__tree	<	_TestType1__,
	// 					__MAP__<_TestType1__, _TestType2__>::value_compare,
	// 					std::allocator<_TestType1__>
	// 				>	T(__MAP__<_TestType1__, _TestType2__>::value_compare);
#undef _TestType1__
#undef _TestType2__
#undef _TestCont__
#undef __PAIR__
#undef __MAP__
// end tests stack
