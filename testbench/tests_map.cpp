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

// UTILS
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

#define PAIR _NS__::pair


template<class T1, class T2>
std::ostream& operator<<(std::ostream& o, const typename _NS__::map<T1, T2>::iterator it)
	{ o << "[" << it->first << ", " << it->second << "]"; return o; }

template<class T1, class T2>
std::ostream& operator<<(std::ostream& o, const typename _NS__::map<T1, T2>::const_iterator it)
	{ o << "[" << it->first << ", " << it->second << "]"; return o; }

template<class T1, class T2>
std::ostream& operator<<(std::ostream& o, const typename PAIR< T1, T2 >& pair)
	{ o << "[" << pair.first << ", " << pair.second << "]"; return o; }

template<class Key, class Value>
void map_info(const _NS__::map<Key, Value>& m) {
	std::cout << "----------- info ------------" << std::endl;
	std::cout << "empty?:\t";
	std::cout << m.empty() << std::endl;
	if (!m.empty()) {
		std::cout << "begin:\t";
		::operator<< <Key, Value> (std::cout, m.begin()); std::cout << std::endl;
		std::cout << "--end:\t";
		::operator<< <Key, Value> (std::cout, --m.end()); std::cout << std::endl;
	}
	std::cout << "size:\t";
	std::cout << m.size() << std::endl;
	// # if (!STD)
	// 	m.print();
	// #endif
	std::cout << std::endl;
}

// TEST FUNC CALLS
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void test_map() {
	std::cout << MAGENTA_B "----\t MAP \t----" << NC << std::endl;

	#define TT1 TestClass
	#define TT2 std::string

	size_t N = 10000;
	std::list<PAIR<TT1, TT2> > list;
	srand(23057756);
	size_t i = 0;
	for ( ; i < N; i++) {
		PAIR<TT1, TT2> pair(rand() % N, std::to_string(rand()));
		list.push_back(pair);
		// std::cout << pair << std::endl;
	}

	std::list<PAIR<TT1, TT2> >::iterator half_list = --list.end();

	// default constructor
	_NS__::map<TT1, TT2> m1;

	// range constructor
	_NS__::map<TT1, TT2> m2(list.begin(), list.end());
	std::cout << "m1 "; map_info(m1);
	std::cout << "m2 "; map_info(m2);

	// copy assignment
	m1 = m2;
	std::cout << "m1 "; map_info(m1);
	std::cout << "m2 "; map_info(m2);

	// cpy constructor (& const)
	_NS__::map<TT1, TT2> const m3(m1);
	std::cout << "m2 "; map_info(m3);

	for ( ; i < N * 5; i++) {
		PAIR<TT1, TT2> pair(i, std::to_string(i));
		list.push_back(pair);
		// std::cout << pair << std::endl;
	}

	// range insert on top
	m2.insert(half_list, list.end());
	std::cout << "m2 "; map_info(m2);

	// find & ite nc
	_NS__::map<TT1, TT2>::iterator it = m2.find(N);
	std::cout << *(--(++((it++)--))) << std::endl;
	std::cout << *(--(m2.end())) << std::endl;
	std::cout << *((m2.begin())) << std::endl;
	// find & ite const
	_NS__::map<TT1, TT2>::const_iterator itc = m2.find(N);
	std::cout << *(--(++((itc++)--))) << std::endl;
	std::cout << *(--(m2.end())) << std::endl;
	std::cout << *((m2.begin())) << std::endl;
	
	// stress clear & insert & erase & op[]
	for (size_t j = 0; j < 20; j++) {
		m2.clear();
		std::cout << "m2 "; map_info(m2);
		if (j % 2)
			m2.insert(half_list, list.end());
		else
			m2.insert(list.begin(), list.end());
		std::cout << "m2 "; map_info(m2);
		m2.insert(PAIR<TT1, TT2>(rand() % 20, std::to_string(rand())));
		std::cout << "m2 "; map_info(m2);
		m2.insert(PAIR<TT1, TT2>(rand() % 23, std::to_string(rand())));
		std::cout << "m2 "; map_info(m2);
		std::cout << m2[TT1(N * 10)] << std::endl;
		m2 [TT1(N * 10)] = std::to_string(rand());
		std::cout << "m2 "; map_info(m2);
		std::cout << m2[TT1 (N * 10)] << std::endl;
		m2.erase(j * 17);
		std::cout << "m2 "; map_info(m2);
		it = m2.begin();
		for (size_t k = j; k - j < (N ); k++)
			++it;
		m2.erase(m2.begin(), it);
		std::cout << "m2 "; map_info(m2);
		m2.insert(list.begin(), list.end());
		std::cout << "m2 "; map_info(m2);
		m2.erase(m2.find(N), m2.end());
		std::cout << "m2 "; map_info(m2);
	}

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

#undef TT1
#undef TT2
#undef _TestCont__
#undef PAIR
