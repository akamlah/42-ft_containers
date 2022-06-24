/* ************************************************************************ */
/*																			*/
/*						ft_containers: test map								*/
/*																			*/
/* ************************************************************************ */

#include "testing.hpp"
#include "../rb_tree.hpp"
#include "../map.hpp"
//TEST ONLY

#include <map>

// void tree_build();
// void map_build();
void std_map_test();

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

#define __PAIR__ ft::pair
// #define __PAIR__ std::pair
// #define __MAP__ std::map
#define __MAP__ ft::map
/* ------------------------------------------------------------------------ */

// CALL ALL
void test_map() {
	std::cout << MAGENTA_B "----\t MAP \t----" << NC << std::endl;
	// tree_build(); std::cout << std::endl;
	// map_build(); std::cout << std::endl;
	std_map_test(); std::cout << std::endl;
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

// void map_build() {
// 	std::cout << CYAN_B"----\t map_build \t----" << NC << std::endl;
// }

// // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template<class T1, class T2>
std::ostream& operator<<(std::ostream& o, const typename __MAP__<T1, T2>::iterator it) {
	o << "[" << it->first << ", " << it->second << "]";
	return o;
}

// template<class Key, class Value>
// void recursive_print_map(typename __MAP__<Key, Value>& m) {
// 	typename __MAP__<Key, Value>::iterator it = m.begin();
// 	typename __MAP__<Key, Value>::difference_type i = 0;

// 	std::cout << std::endl;
// 	while (it != m.end()) {
// 		std::cout << i << ":\t";
// 		::operator<< <Key, Value> (std::cout,it);
// 		std::cout << "\n";
// 		++it;
// 		++i;
// 	}
// 	std::cout << std::endl;
// }

// template<class Key, class Value>
// void print_map(__MAP__<Key, Value>& m) {
// 	std::cout << "-----------------------" << std::endl;
// 	std::cout << "begin:\t";
// 	::operator<< <Key, Value> (std::cout, m.begin()); std::cout << std::endl; // like... really ??
// 	std::cout << "--end:\t";
// 	::operator<< <Key, Value> (std::cout, --m.end()); std::cout << std::endl;
// 	// this works but end - 1 not (in fact it is bidir, no +- difftype overload)
// 	std::cout << "size:\t";
// 	std::cout << m.size() << std::endl;
// 	std::cout << "-----------------------" << std::endl;
// 	recursive_print_map(m);
// 	std::cout << "-----------------------" << std::endl;
// }

void std_map_test() {
	std::cout << CYAN_B"----\t std_map_test \t----" << NC << std::endl;
	__MAP__< _TestType1__, std::string > m;
	std::cout << m.empty() << std::endl;
	std::cout << m.size() << std::endl;

	std::cout << "-----------------------" << std::endl;
	m.print();
	// m.insert(ft::pair< _TestType1__, std::string >(	_TestType1__(99), "a" )); // 
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(99)		, "a" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(99)		, "a"		))	).first)->second) << "\n";
	m.print();
	std::cout << m.empty() << std::endl;
	std::cout << m.size() << std::endl;
	__MAP__<_TestType1__, std::string >::iterator it = m.begin();
	::operator<< <_TestType1__, std::string > (std::cout, it); std::cout << std::endl;

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
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(199)		, "a" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(199)		, "a"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(18)			, "b" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(18)			, "b"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(13)			, "c" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(13)			, "c"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2144)		, "t" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2144)		, "t"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2143)		, "u" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2143)		, "u"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2145)		, "v" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2145)		, "v"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2999)		, "w" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2999)		, "w"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2199)		, "a" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2199)		, "a"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(218)			, "b" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(218)			, "b"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(213)			, "c" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(213)			, "c"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21128)		, "d" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21128)		, "d"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2111)		, "e" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2111)		, "e"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(212)			, "f" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(212)			, "f"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(213785678)	, "g" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(213785678)	, "g"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2110)		, "h" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2110)		, "h"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2180)		, "i" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2180)		, "i"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21111)		, "j" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21111)		, "j"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21110)		, "k" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21110)		, "k"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2170)		, "l" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2170)		, "l"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2113)		, "m" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2113)		, "m"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2167)		, "n" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2167)		, "n"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2149)		, "o" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2149)		, "o"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2111)		, "j" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2111)		, "j"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2110)		, "k" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2110)		, "k"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(270)		, "l" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(270)		, "l"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(213)		, "m" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(213)		, "m"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(267)		, "n" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(267)		, "n"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(249)		, "o" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(249)		, "o"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(245)		, "p" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(245)		, "p"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(25476)		, "q" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(25476)		, "q"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2145)		, "p" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2145)		, "p"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(215476)		, "q" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(215476)		, "q"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2123)		, "r" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2123)		, "r"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2125)		, "s" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2125)		, "s"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1144)		, "t" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1144)		, "t"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1143)		, "u" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1143)		, "u"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1145)		, "v" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1145)		, "v"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1999)		, "w" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1999)		, "w"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(299)		, "a" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(299)		, "a"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(28)			, "b" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(28)			, "b"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(23)			, "c" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(23)			, "c"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2128)		, "d" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(2128)		, "d"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(211)		, "e" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(211)		, "e"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(22)			, "f" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(22)			, "f"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(23785678)	, "g" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(23785678)	, "g"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(210)		, "h" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(210)		, "h"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21144)		, "t" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21144)		, "t"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21143)		, "u" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21143)		, "u"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21145)		, "v" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21145)		, "v"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21999)		, "w" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(21999)		, "w"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1128)		, "d" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1128)		, "d"		))	).first)->second) << "\n";
	__PAIR__< _TestType1__, std::string > var1(	_TestType1__(8)			, "qwbter");
	__PAIR__< _TestType1__, std::string > var2(	_TestType1__(3)			, "qwcater");
	__PAIR__< _TestType1__, std::string > var3(	_TestType1__(128)		, "qater");
	__PAIR__< _TestType1__, std::string > var4(	_TestType1__(11)		, "weater");
	__PAIR__< _TestType1__, std::string > var5(	_TestType1__(2)			, "ter");
	__PAIR__< _TestType1__, std::string > var6(	_TestType1__(3785678)	, "ater");
	m.insert(var1);
	m.insert(var2);
	m.insert(var3);
	m.insert(var4);
	m.insert(var5);
	m.insert(var6);
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(111)		, "e" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(111)		, "e"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(12)			, "f" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(12)			, "f"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(13785678)	, "g" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(13785678)	, "g"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(110)		, "h" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(110)		, "h"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(180)		, "i" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(180)		, "i"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1111)		, "j" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1111)		, "j"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1110)		, "k" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(1110)		, "k"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(170)		, "l" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(170)		, "l"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(113)		, "m" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(113)		, "m"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(167)		, "n" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(167)		, "n"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(149)		, "o" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(149)		, "o"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(145)		, "p" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(145)		, "p"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(15476)		, "q" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(15476)		, "q"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(123)		, "r" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(123)		, "r"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(125)		, "s" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(125)		, "s"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(280)		, "i" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(280)		, "i"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(223)		, "r" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(223)		, "r"		))	).first)->second) << "\n";
	std::cout <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(225)		, "s" ))	).first)->first) << "\t" <<	( ((m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(225)		, "s"		))	).first)->second) << "\n";
	m.print();

	std::cout << "-----------------------" << std::endl;
	m.erase(_TestType1__(12));
	// m.print();
	std::cout << "-----------------------" << std::endl;
// 	m.insert(__PAIR__< _TestType1__, std::string >(	_TestType1__(99)		, "a"		)); // just gets ignored.
// 	print_map(m);
	(void)m;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void tree_build() {
	std::cout << CYAN_B"----\t tree_build \t----" << NC << std::endl;
	ft::rb_tree	<_TestType1__, std::less<_TestType1__> > T;
	T.insert(_TestType1__(99));
	// T.print_tree();
	T.insert(_TestType1__(8));
	T.print_tree();
	T.insert(_TestType1__(3));
	// T.print_tree();
	T.insert(_TestType1__(128));
	// T.print_tree();
	T.insert(_TestType1__(11));
	// T.print_tree();
	T.insert(_TestType1__(2));
	// T.print_tree();
	T.insert(_TestType1__(3785678));
	// T.print_tree();
	T.insert(_TestType1__(10));
	// T.print_tree();
	T.insert(_TestType1__(80));
	// T.print_tree();
	T.insert(_TestType1__(111));
	// T.print_tree();
	T.insert(_TestType1__(110));
	// T.print_tree();
	T.insert(_TestType1__(70));
	// T.print_tree();
	T.insert(_TestType1__(13));
	// T.print_tree();
	T.insert(_TestType1__(67));
	// T.print_tree();
	T.insert(_TestType1__(49));
	// T.print_tree();
	T.insert(_TestType1__(45));
	// T.print_tree();
	T.insert(_TestType1__(5476));
	// T.print_tree();
	T.insert(_TestType1__(23));
	// T.print_tree();
	T.insert(_TestType1__(25));
	// T.print_tree();
	T.insert(_TestType1__(144));
	// T.print_tree();
	T.insert(_TestType1__(143));
	// T.print_tree();
	T.insert(_TestType1__(145));
	// T.print_tree();
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

	std::cout << "----------- ITER ------------" << std::endl;
	ft::rb_tree	<_TestType1__, std::less<_TestType1__> >::iterator it = T.begin();
	std::cout << *it << std::endl;
	++it;
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	it--;
	std::cout << *it << std::endl;
	--it;
	std::cout << *it << std::endl;

	// // it = T.end();
	// // --it;
	// // std::cout << *it << std::endl;
	// std::cout << "-----------------------" << std::endl;
	(void)it;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


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
