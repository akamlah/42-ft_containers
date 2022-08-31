/* ************************************************************************ */
/*																			*/
/*						ft_containers: tests stack							*/
/*																			*/
/* ************************************************************************ */

#include "testing.hpp"

#include "../src/vector.hpp"
#include "../src/stack.hpp"

// in this file:
void stack_construct();
void stack_compare();

/* ************************************************************************ */
// UTILS:
/* ************************************************************************ */

// _NS__ (tested namespace) defined in testing.hpp

#ifndef _TestType__ // the data type tested
	// #define _TestType__ TestClass
	#define _TestType__ int
	// #define _TestType__ double
	// #define _TestType__ foo<int>
#endif

#ifndef _TestCont__ // the container tested
	// #define _TestCont__ std::deque
	#define _TestCont__ std::list
	// #define _TestCont__ ft::vector
#endif

template< typename T, class Container>
void info(_NS__::stack<T, Container > s) {
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
	std::cout << MAGENTA_B "----\t STACK \t----" << NC << std::endl;
	// stack_construct(); std::cout << std::endl;
	// stack_compare(); std::cout << std::endl;
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

void stack_construct() {
	std::cout << CYAN_B"----\t stack_construct \t----" << NC << std::endl;
	_NS__::stack<_TestType__, _TestCont__<_TestType__> > s;
	info(s);
	for (unsigned int i = 0; i < 300; i++) {
		s.push(_TestType__(i + 3));
	}
	info(s);
	for (unsigned int i = 0; i < s.size(); i++) {
		s.pop();
	}
	info(s);
	_NS__::stack<_TestType__> stck;

	std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;

	stck.push(41);
	stck.push(29);
	stck.push(10);
	stck.push(42);
	std::cout << "Added some elements" << std::endl;

	std::cout << "empty: " << stck.empty() << std::endl;
}

template <class T_STACK>
void	cmp(const T_STACK &lhs, const T_STACK &rhs) {
	static int i = 0;
	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

void stack_compare() {
	_TestCont__<_TestType__>	ctnr;
	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	_NS__::stack<_TestType__, _TestCont__<_TestType__> >	stck(ctnr);
	_NS__::stack<_TestType__, _TestCont__<_TestType__> >	stck2(ctnr);

	cmp(stck, stck);  // 0
	cmp(stck, stck2); // 1

	stck2.push(60);
	stck2.push(61);
	stck2.push(62);

	cmp(stck, stck2); // 2
	cmp(stck2, stck); // 3

	stck.push(42);

	cmp(stck, stck2); // 4
	cmp(stck2, stck); // 5

	stck.push(100);

	cmp(stck, stck2); // 6
	cmp(stck2, stck); // 7
	info(stck);
}

#undef _TestType__
#undef _TestCont__

// end tests stack
