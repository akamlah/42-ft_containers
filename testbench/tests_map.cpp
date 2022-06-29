/* ************************************************************************ */
/*																			*/
/*						ft_containers: test map								*/
/*																			*/
/* ************************************************************************ */

#include "testing.hpp"
#if (!STD)
# include "../rb_tree.hpp"
# include "../map.hpp"
# include "../set.hpp"
#endif

//TEST ONLY
#include <map>

void map_build();
void tree_build();
void map_empty();
void map_erase();

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
	map_erase(); std::cout << std::endl;
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


	// std::cout << " !!! CLEAR !!! " << std::endl;
	// std::cout << "end_node() before: " << T.end_node() << std::endl;
	T.clear();
	// std::cout << "size: " << T.size() << std::endl;
	// std::cout << "end_node() after: " << T.end_node() << std::endl;

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
	std::cout << "------------erase root: -----------" << std::endl;
	T.erase(99);
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
	std::cout << CYAN_B"----\t map_empty \t----" << NC << std::endl;

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



#define Tt1 int
#define Tt2 std::string
#define TESTED_NAMESPACE _NS__
#define _pair __PAIR__
typedef _pair<const Tt1, Tt2> Tt3;

static int iter = 0;


template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T1, typename T2>
void	printReverse(TESTED_NAMESPACE::map<T1, T2> &mp)
{
	typename TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();
	std::cout << "printReverse:" << std::endl;
	while (it != ite) {
		it--;
		std::cout << "-> " << printPair(it, false) << std::endl;
	}
	std::cout << "_______________________________________________" << std::endl;
}

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	// std::cout << "param: " << printPair(param) << std::endl;
	mp.erase(param);
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	// std::cout << "param: " << printPair(param) << "param2: " << printPair(param2) << std::endl;
	mp.erase(param, param2);
	printSize(mp);
}

void		map_erase(void)
{
	std::cout << CYAN_B"----\t map_erase \t----" << NC << std::endl;

	std::list<Tt3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(Tt3(i, std::string((lst_size - i), i + 65)));
	TESTED_NAMESPACE::map<Tt1, Tt2> mp(lst.begin(), lst.end());
	printSize(mp);

	std::cout << "\nERASE 1" << std::endl;
	ft_erase(mp, ++mp.begin());

	std::cout << "\nERASE 2" << std::endl;
	ft_erase(mp, mp.begin());
	std::cout << "\nERASE 3" << std::endl;
	ft_erase(mp, --mp.end());

	std::cout << "\nERASE 4" << std::endl;
	mp.print();
	ft_erase(mp, mp.begin(), ++(++(++mp.begin())));
	mp.print();

	std::cout << "\nERASE 5" << std::endl;
	ft_erase(mp, --(--(--mp.end())), --mp.end());
	mp.print();

	mp[10] = "Hello";
	mp[11] = "Hi there";
	printSize(mp);
	std::cout << "\nERASE 6" << std::endl;
	mp.print();
	std::cout << "\n now erase 6" << std::endl;
	ft_erase(mp, --(--(--mp.end())), mp.end());
	mp.print();

	mp[12] = "ONE";
	mp[13] = "TWO";
	mp[14] = "THREE";
	mp[15] = "FOUR";
	printSize(mp);
	std::cout << "\nERASE 7" << std::endl;
	mp.print();
	std::cout << "\n now erase 7" << std::endl;
	ft_erase(mp, mp.begin(), mp.end());
	mp.print();

	ft::set<Tt1> set;
	(void)set;
	#include <set>
	
	std::set<Tt1> set1;
	(void)set1;
}

#undef __PAIR__
