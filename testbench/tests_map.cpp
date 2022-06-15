/* ************************************************************************ */
/*																			*/
/*						ft_containers: test map								*/
/*																			*/
/* ************************************************************************ */

#include "testing.hpp"
#include "../map.hpp"
#include "../__rb_tree.hpp"
//TEST ONLY
#include <__tree>
#include <map>

// class map;

// in this file:
void tree_build();
void std_map_test();
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

// #define __PAIR__ ft::pair
#define __PAIR__ std::pair
#define __MAP__ std::map
/* ------------------------------------------------------------------------ */

// CALL ALL
void test_map() {
	std::cout << MAGENTA_B "----\t MAP \t----" << NC << std::endl;
	// tree_build(); std::cout << std::endl;
	// std_map_test(); std::cout << std::endl;
	map_construct(); std::cout << std::endl;
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

void tree_build() {
	std::cout << CYAN_B"----\t tree_build \t----" << NC << std::endl;
	ft::__rb_tree	<	_TestType1__,
						ft::map<_TestType1__, _TestType2__>::value_compare,
						std::allocator<_TestType1__>
					>	T;

	T.rb_insert(_TestType1__(99));
	T.rb_insert(_TestType1__(8));
	T.rb_insert(_TestType1__(3));
	T.rb_insert(_TestType1__(128));
	T.rb_insert(_TestType1__(11));
	T.rb_insert(_TestType1__(2));
	T.rb_insert(_TestType1__(3785678));
	T.rb_insert(_TestType1__(10));
	T.rb_insert(_TestType1__(80));
	T.rb_insert(_TestType1__(111));
	T.rb_insert(_TestType1__(110));
	T.rb_insert(_TestType1__(70));
	T.rb_insert(_TestType1__(13));
	T.rb_insert(_TestType1__(67));
	T.rb_insert(_TestType1__(49));
	T.rb_insert(_TestType1__(45));
	T.rb_insert(_TestType1__(5476));
	T.rb_insert(_TestType1__(23));
	T.rb_insert(_TestType1__(25));
	T.rb_insert(_TestType1__(144));
	T.rb_insert(_TestType1__(143));
	T.rb_insert(_TestType1__(145));
	T.rb_insert(_TestType1__(999));
	T.print_tree();
	std::cout << "-----------------------" << std::endl;
	std::cout << "MIN: " << T.rb_min(T._root)->value << " " << std::endl;
	std::cout << "MAX: " << T.rb_max(T._root)->value << " " << std::endl;
	std::cout << "SEARCH 2: " << T.rb_search(T._root, 2) << " " << std::endl;
	std::cout << "SUCCESSOR 143: " << T.rb_successor(143) << " " << T.rb_successor(143)->value << " " << std::endl;
	std::cout << "SUCCESSOR 3785678: " << T.rb_successor(3785678) << " " << T.rb_successor(3785678)->value << " " << std::endl;
	std::cout << "SUCCESSOR 99: " << T.rb_successor(99) << " " << T.rb_successor(99)->value << " " << std::endl;
	std::cout << "SUCCESSOR 11: " << T.rb_successor(11) << " " << T.rb_successor(11)->value << " " << std::endl;
	std::cout << "PREDECESSOR 11: " << T.rb_predecessor(11) << " " << T.rb_predecessor(11)->value << " " << std::endl;
	std::cout << "-----------------------" << std::endl;

	T.rb_delete(11);
	T.print_tree();
	std::cout << "-----------------------" << std::endl;
	T.rb_delete(8);
	T.print_tree();
	std::cout << "-----------------------" << std::endl;
	T.rb_delete(111);
	T.print_tree();
	std::cout << "-----------------------" << std::endl;
	T.rb_delete(143);
	T.print_tree();
	std::cout << "-----------------------" << std::endl;
}

template<class T1, class T2>
std::ostream& operator<<(std::ostream& o, const typename __MAP__<T1, T2>::iterator it) {
	o << "[" << it->first << ", " << it->second << "]";
	return o;
}

template<class Key, class Value>
void recursive_print_map(typename __MAP__<Key, Value>& m) {
	typename __MAP__<Key, Value>::iterator it = m.begin();
	typename __MAP__<Key, Value>::difference_type i = 0;

	std::cout << std::endl;
	while (it != m.end()) {
		std::cout << i << ":\t";
		::operator<< <Key, Value> (std::cout,it);
		std::cout << "\n";
		++it;
		++i;
	}
	std::cout << std::endl;
}

template<class Key, class Value>
void print_map(__MAP__<Key, Value>& m) {
	std::cout << "-----------------------" << std::endl;
	std::cout << "begin:\t";
	::operator<< <Key, Value> (std::cout, m.begin()); std::cout << std::endl; // like... really ??
	std::cout << "--end:\t";
	::operator<< <Key, Value> (std::cout, --m.end()); std::cout << std::endl;
	// this works but end - 1 not (in fact it is bidir, no +- difftype overload)
	std::cout << "size:\t";
	std::cout << m.size() << std::endl;
	std::cout << "-----------------------" << std::endl;
	recursive_print_map(m);
	std::cout << "-----------------------" << std::endl;
}

void std_map_test() {
	std::cout << CYAN_B"----\t std_map_test \t----" << NC << std::endl;
	__MAP__< _TestType1__, std::string > m;
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(99)		, "a" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(99)		, "a"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(8)			, "b" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(8)			, "b"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(3)			, "c" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(3)			, "c"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(128)		, "d" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(128)		, "d"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(11)		, "e" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(11)		, "e"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2)			, "f" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2)			, "f"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(3785678)	, "g" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(3785678)	, "g"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(10)		, "h" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(10)		, "h"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(80)		, "i" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(80)		, "i"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(111)		, "j" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(111)		, "j"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(110)		, "k" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(110)		, "k"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(70)		, "l" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(70)		, "l"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(13)		, "m" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(13)		, "m"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(67)		, "n" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(67)		, "n"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(49)		, "o" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(49)		, "o"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(45)		, "p" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(45)		, "p"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(5476)		, "q" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(5476)		, "q"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(23)		, "r" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(23)		, "r"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(25)		, "s" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(25)		, "s"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(144)		, "t" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(144)		, "t"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(143)		, "u" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(143)		, "u"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(145)		, "v" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(145)		, "v"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(999)		, "w" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(999)		, "w"		))	).first)->second) << "\n";

	m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(99)		, "a"		)); // just gets ignored.
	print_map(m);

}

void map_construct() {
	std::cout << CYAN_B"----\t map_construct \t----" << NC << std::endl;
	_NS__::map<_TestType1__, _TestType2__> m;
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
© 2022 GitHub, Inc.
Terms
Privacy
Security
