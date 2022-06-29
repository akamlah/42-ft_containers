/* ************************************************************************ */
/*																			*/
/*							ft:: UTILITY									*/
/*																			*/
/* ************************************************************************ */

/* CONTENTS ------------------------------------------------------------------

template< class T1, class T2 >
struct pair;

template< class T1, class T2 >
ft::pair< T1, T2 > make_pair(T1 t, T2 u);

--------------------------------------------------------------------------- */

#ifndef _LIBFT_UTILITY_H_
# define _LIBFT_UTILITY_H_

namespace ft { /* NAMESPACE FT -------------------------------------------- */

/* 
	PAIR
	std::pair is a class template that provides a way to store two
	heterogeneous objects as a single unit. A pair is a specific case of a
	std::tuple with two elements.
*/
template< class T1, class T2 >
struct pair {
	typedef T1 first_type;
	typedef T2 second_type;

	first_type first;
	second_type second;

	pair() : first(), second() {}
	pair(const T1& x, const T2& y): first(x), second(y) {}
	template< class U1, class U2 >
	pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

	pair& operator=(const pair& other) {
		first = other.first;
		second = other.second;
		return (*this);
	}
};

/* operator==,!=,<,<=,>,>=,<=> */

template< class T1, class T2 >
bool operator==( const typename ft::pair<T1,T2>& lhs, const typename ft::pair<T1,T2>& rhs )
	{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

template< class T1, class T2 >
bool operator!=( const typename ft::pair<T1,T2>& lhs, const typename ft::pair<T1,T2>& rhs )
	{ return (!(lhs == rhs)); }

template< class T1, class T2 >
bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{ return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

template< class T1, class T2 >
bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{ return (!(rhs < lhs)); }

template< class T1, class T2 >
bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{ return (rhs < lhs); }

template< class T1, class T2 >
bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{ return (!(lhs < rhs)); }

// DEBUGGING / print map function
template<class T1, class T2>
std::ostream& operator<<(std::ostream& o, const typename ft::pair< T1, T2 >& pair)
	{ o << "[" << pair.first << ", " << pair.second << "]"; return o; }

/* ft::pair ---------------------------------------------------------------- */

/* make pair */

template< class T1, class T2 >
ft::pair< T1, T2 > make_pair(T1 t, T2 u) { return (ft::pair< T1, T2 >(t, u)); }

} // NAMESPACE FT

#endif // _LIBFT_UTILITY_H_
