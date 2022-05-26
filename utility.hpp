/* ************************************************************************ */
/*																			*/
/*							ft:: UTILITY									*/
/*																			*/
/* ************************************************************************ */

#ifndef _LIBFT_UTILITY_H_
# define _LIBFT_UTILITY_H_

namespace ft {

/* ------------------------------------------------------------------------ */
/* CONTENTS ------------------------------------------------------------------

template< class T1, class T2 > struct pair;

	Member types
		first_type	T1
		second_type	T2

	Member objects
		first	T1
		second	T2

	Member functions
		(constructor)
			pair( const T1& x, const T2& y );
			template< class U1, class U2 > pair( const pair<U1, U2>& p );
			pair( const pair& p ) = default;
		operator=
		
	Non-member functions
		make_pair
		operator==
		operator!=
		operator<
		operator<=
		operator>
		operator>=

--------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------ */

/*   +  +  +  +  +  +  +  --- IMPLEMENTATION ---  +  +  +  +  +  +  +  +  + */

template< class T1, class T2 >
struct pair {

// typedefs

public:

	typedef T1 first_type;
	typedef T2 second_type;

// attributes

private:

	first_type first;
	second_type second;

// construction

public:

	pair( const T1& x, const T2& y );
	template< class U1, class U2 > pair( const pair<U1, U2>& p );
	pair( const pair& p ) = default;

// member functions

	pair& operator=( const pair& other );

	template< class T1, class T2 >
	ft::pair<T1,T2> make_pair( T1 t, T2 u );
	
}; // FT PAIR

/* operator==,!=,<,<=,>,>=,<=> */

template< class T1, class T2 >
bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs );

template< class T1, class T2 >
bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs );

template< class T1, class T2 >
bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs );

template< class T1, class T2 >
bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs );

template< class T1, class T2 >
bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs );

template< class T1, class T2 >
bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs );


} // NAMESPACE FT
#endif // _LIBFT_UTILITY_H_