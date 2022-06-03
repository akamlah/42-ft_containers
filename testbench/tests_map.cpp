/* ************************************************************************ */
/*																			*/
/*						ft_containers: test map								*/
/*																			*/
/* ************************************************************************ */

#include "testing.hpp"
#include "../map.hpp"
#include "../naive_tree.hpp"

class map;

// in this file:
void tree_build();
// void map_construct();

/* ************************************************************************ */
// UTILS:
/* ************************************************************************ */

#ifndef _TestType1__
// #	define _TestType1__ TestClass
#	define _TestType1__ int
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

/* ------------------------------------------------------------------------ */

// CALL ALL
void test_map() {
	std::cout << MAGENTA_B "----\t MAP \t----" << NC << std::endl;
	tree_build(); std::cout << std::endl;


	// map_construct(); std::cout << std::endl;
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

void tree_build() {
	std::cout << CYAN_B"----\t tree_build \t----" << NC << std::endl;
	// ft::rb_tree<_TestType1__, std::map::value_compare, std::allocator> T;
	ft::rb_tree<_TestType1__, ft::map<_TestType1__, _TestType2__>::value_compare> T;
	T.rb_insert(_TestType1__(3));
	T.print_tree();
	T.rb_insert(_TestType1__(4));
	T.print_tree();
	T.rb_insert(_TestType1__(5));
	T.print_tree();
	T.rb_insert(_TestType1__(6));
	T.print_tree();
	T.rb_insert(_TestType1__(7));
	T.print_tree();
	T.rb_insert(_TestType1__(8));
	T.print_tree();
	T.rb_insert(_TestType1__(9));
	T.print_tree();
	T.info();

	// T.rb_insert(_TestType1__(99));
	// // T.print_tree();
	// T.rb_insert(_TestType1__(8));
	// // T.print_tree();
	// T.rb_insert(_TestType1__(7));
	// // T.print_tree();
	// T.rb_insert(_TestType1__(6));
	// // T.print_tree();
	// T.rb_insert(_TestType1__(5));
	// T.print_tree();
	// T.rb_insert(_TestType1__(4));
	// // T.print_tree();
	// T.rb_insert(_TestType1__(3));
	// // T.print_tree();
	// T.info();
}










// void map_construct() {
// 	std::cout << CYAN_B"----\t map_construct \t----" << NC << std::endl;
// 	// _NS__::map<_TestType1__, _TestType2__> m;
// }


#undef _TestType1__
#undef _TestType2__
#undef _TestCont__
// end tests stack
