/* ************************************************************************ */
/*																			*/
/*						ft_containers: test map								*/
/*																			*/
/* ************************************************************************ */

#include "testing.hpp"
#if (!STD)
# include "../rb_tree.hpp"
# include "../map.hpp"
#endif

//TEST ONLY
#include <map>

void map_build();
void tree_build();
void map_empty();

/* ************************************************************************ */
// UTILS:
/* ************************************************************************ */

#ifndef _TestType1__
// #	define _TestType1__ TestClass
#	define _TestType1__ char
// #	define _TestType1__ int
// #	define _TestType1__ double
// #	define _TestType1__ foo<int>
#endif

#ifndef _TestType2__
// #	define _TestType2__ std::string
#	define _TestType2__ int
#endif

#ifndef _TestCont__
// #	define _TestCont__ std::deque
#	define _TestCont__ std::list
// #	define _TestCont__ _NS::vector
#endif

#define __PAIR__ _NS__::pair
// #define __PAIR__ ft::pair
// #define __PAIR__ std::pair

/* ------------------------------------------------------------------------ */

// CALL ALL
void test_map() {
	std::cout << MAGENTA_B "----\t MAP \t----" << NC << std::endl;
	tree_build(); std::cout << std::endl;

	map_build(); std::cout << std::endl;
	map_empty(); std::cout << std::endl;
}

/* ************************************************************************ */
// TESTS
/* ************************************************************************ */

template<class T1, class T2>
std::ostream& operator<<(std::ostream& o, const typename _NS__::map<T1, T2>::iterator it) {
	o << "[" << it->first << ", " << it->second << "]";
	return o;
}

template<class Key, class Value>
void map_info(_NS__::map<Key, Value>& m) {
	std::cout << "----------- info ------------" << std::endl;

	std::cout << "empty?:\t";
	std::cout << m.empty() << std::endl;
	if (!m.empty()) {
		std::cout << "begin:\t";
		::operator<< <Key, Value> (std::cout, m.begin()); std::cout << std::endl; // like... really ??
		std::cout << "--end:\t";
		::operator<< <Key, Value> (std::cout, --m.end()); std::cout << std::endl;
	}
	std::cout << "size:\t";
	std::cout << m.size() << std::endl;

	# if (!STD)
		m.print();
	#endif

	std::cout << "-----------------------------" << std::endl;
}

void map_build() {
	std::cout << CYAN_B"----\t map_build \t----" << NC << std::endl;


	std::list<__PAIR__<const _TestType1__, _TestType2__> > lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(__PAIR__<const _TestType1__, _TestType2__>('a' + i, lst_size - i));

	_NS__::map<_TestType1__, _TestType2__> mp(lst.begin(), lst.end()), mp2;
	_NS__::map<_TestType1__, _TestType2__>::iterator it;

	lst.clear();
	map_info(mp);

	std::cout << " cpy" << std::endl;
	map_info(mp2);
	mp2 = mp;
	map_info(mp2);

	std::cout << " for loop " << std::endl;
	it = mp.begin();
	for (unsigned long int i = 3; i < mp.size(); ++i)
		it++->second = i * 7;

	map_info(mp);
	map_info(mp2);

	std::cout << " mp2 clear" << std::endl;
	mp2.clear();
	map_info(mp2);
	map_info(mp2);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#if (!STD)
#undef _TestType1__
#define _TestType1__ TestClass

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

	it = T.end();
	--it;
	std::cout << *it << std::endl;
	--it;
	std::cout << *it << std::endl;
	std::cout << "-----------------------" << std::endl;


	std::cout << " !!! CLEAR !!! " << std::endl;
	std::cout << "end_node() before: " << T.end_node() << std::endl;
	T.clear();
	std::cout << "size: " << T.size() << std::endl;
	std::cout << "end_node() after: " << T.end_node() << std::endl;

	std::cout << "-----------------------" << std::endl;
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
	it = T.begin();
	std::cout << *it << std::endl;
	++it;
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	it--;
	std::cout << *it << std::endl;
	--it;
	std::cout << *it << std::endl;

	it = T.end();
	--it;
	std::cout << *it << std::endl;
	--it;
	std::cout << *it << std::endl;
	std::cout << "-----------------------" << std::endl;
	(void)it;
}
#endif

#undef _TestType1__
#undef _TestType2__
#undef _TestCont__
// end tests map


#define _TestType1__ char
#define _TestType2__ int
typedef __PAIR__<const _TestType1__, _TestType2__> T3;

template <class T>
void	is_empty(T const &mp)
{
	std::cout << "is_empty: " << mp.empty() << std::endl;
}

void		map_empty(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3('a' + i, lst_size - i));

	
	_NS__::map<_TestType1__, _TestType2__> mp(lst.begin(), lst.end()), mp2;
	
	_NS__::map<_TestType1__, _TestType2__>::iterator it;

	lst.clear();
	is_empty(mp);
	// printSize(mp);

	is_empty(mp2);
	mp2 = mp;
	is_empty(mp2);

	it = mp.begin();
	for (unsigned long int i = 3; i < mp.size(); ++i)
		it++->second = i * 7;

	// printSize(mp);
	// printSize(mp2);

	mp2.clear();
	is_empty(mp2);
	// printSize(mp2);
}
#undef __PAIR__
