/* ************************************************************************ */
/*																			*/
/*						ft_containers: tests stack							*/
/*																			*/
/* ************************************************************************ */

#include "testing.hpp"

// in this file:
void stack_construct();

/* ************************************************************************ */
// UTILS:
/* ************************************************************************ */

// __NS__ (tested namespace) defined in testing.hpp

#ifndef __TestType__ // the data type tested
	// #define __TestType__ TestClass
	// #define __TestType__ int
	// #define __TestType__ double
	// #define __TestType__ std::string
	#define __TestType__ foo<int>
#endif

#ifndef __TestCont__ // the container tested
	#define __TestCont__ std::deque
	// #define __TestCont__ ft::vector
#endif

template< typename T, class Container>
void info(__NS__::stack<T, Container > s) {
	std::cout << "size: " << s.size() << "; ";
	std::cout << "empty?: ";
	if (s.empty())
		std::cout << "y" << "; ";
	else
		std::cout << "n" << "; ";
	if (!s.empty())
		std::cout << "top: " << s.top() << "; ";
	std::cout << std::endl;
}

/* ------------------------------------------------------------------------ */

// CALL ALL
void test_stack() {
	stack_construct(); std::cout << std::endl;
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

void stack_construct() {
	std::cout << CYAN_B"----\t stack_construct \t----" << NC << std::endl;
	__NS__::stack<__TestType__, __TestCont__<__TestType__> > s;
	info(s);
	for (unsigned int i = 0; i < 300; i++) {
		s.push(__TestType__(i + 3));
	}
	info(s);
	for (unsigned int i = 0; i < s.size(); i++) {
		s.pop();
	}
	info(s);
	__NS__::stack<__TestType__> stck;

	std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;

	stck.push(41);
	stck.push(29);
	stck.push(10);
	stck.push(42);
	std::cout << "Added some elements" << std::endl;

	std::cout << "empty: " << stck.empty() << std::endl;
	info(stck);
}

#undef __TestType__
// end tests stack
