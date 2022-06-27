/* ************************************************************************ */
/*																			*/
/*							ft:: UTILITY									*/
/*																			*/
/* ************************************************************************ */

/* CONTENTS ------------------------------------------------------------------
PAIR
	Member types
		first_type
		second_type
	Member attributes (public)
		first
		second
	Member functions
		(constructor)
		operator=
	Non-member functions
		make pair
		operator==,!=,<,<=,>,>=,<=>
--------------------------------------------------------------------------- */

#ifndef _LIBFT_UTILITY_H_
# define _LIBFT_UTILITY_H_

namespace ft { /* NAMESPACE FT -------------------------------------------- */


/* PAIR ----------------------------------------------------------------------
std::pair is a class template that provides a way to store two
heterogeneous objects as a single unit. A pair is a specific case of a
std::tuple with two elements. */

template<
	class T1,
	class T2
> struct pair {

	typedef T1 first_type;
	typedef T2 second_type;

	first_type first;
	second_type second;

	pair() : first(), second() 
	{}
	// {std::cout << "def constr pair" << " " << *this << std::endl;}

	pair(const T1& x, const T2& y): first(x), second(y) 
	{}
	// {std::cout << "pair constr pair" << " " << *this << std::endl;}

	template< class U1, class U2 >
	pair(const pair<U1, U2>& p) : first(p.first), second(p.second) 
	{}
	// {std::cout << "copy constr pair" << " " << *this << std::endl;}

	// pair(const pair& p) = default {} ?
	// ~pair() {} // trivial ?

	pair& operator=(const pair& other) {
		first = other.first;
		second = other.second;
		return (*this);
	}

}; // PAIR

/* make pair */
template< class T1, class T2 >
ft::pair< T1, T2 > make_pair(T1 t, T2 u) {
	// std::cout << "make pair" << std::endl; // !
	return (ft::pair< T1, T2 >(t, u));
}

// DEBUGGING / print map function
template<class T1, class T2>
std::ostream& operator<<(std::ostream& o, const typename ft::pair< T1, T2 >& pair) {
	// std::cout << " (pair<<) "; // << std::endl;		 // !
	o << "[" << pair.first << ", " << pair.second << "]";
	return o;
}

/* operator==,!=,<,<=,>,>=,<=> */

template< class T1, class T2 >
bool operator==( const typename ft::pair<T1,T2>& lhs, const typename ft::pair<T1,T2>& rhs ) {
	// std::cout << "pair== " << std::endl; // !
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template< class T1, class T2 >
bool operator!=( const typename ft::pair<T1,T2>& lhs, const typename ft::pair<T1,T2>& rhs ) {
	// std::cout << "pair!= " << std::endl; // !
	return (!(lhs == rhs));
}

template< class T1, class T2 >
bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
	return (lhs.first < rhs.first
		|| (!(rhs.first < lhs.first) && lhs.second < rhs.second));
}

template< class T1, class T2 >
bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
	return (!(rhs < lhs));
}

template< class T1, class T2 >
bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
	return (rhs < lhs);
}

template< class T1, class T2 >
bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
	return (!(lhs < rhs));
}

// ft::pair
/* ------------------------------------------------------------------------ */

} // NAMESPACE FT
#endif // _LIBFT_UTILITY_H_
