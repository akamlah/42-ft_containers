/* ************************************************************************ */
/*																			*/
/*						ft_containers: test map								*/
/*																			*/
/* ************************************************************************ */

#include "testing.hpp"
#include "../map.hpp"

// in this file:
void map_construct();

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
	map_construct(); std::cout << std::endl;
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

void map_construct() {
	std::cout << CYAN_B"----\t map_construct \t----" << NC << std::endl;
	_NS__::map<_TestType1__, _TestType2__> m;

}

#undef _TestType1__
#undef _TestType2__
#undef _TestCont__
// end tests stack
