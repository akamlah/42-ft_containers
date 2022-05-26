/* ************************************************************************ */
/*																			*/
/*							ft:: ITERATOR									*/
/*																			*/
/* ************************************************************************ */

#ifndef _LIBFT_TYPE_TRAITS_H_
# define _LIBFT_TYPE_TRAITS_H_

namespace ft {

// note: std defines true_type and false_type as struct _LIBCPP_BOOL...whatever

/* ------------------------------------------------------------------------ */
/* CONTENTS ------------------------------------------------------------------
enable if
is_integral
--------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------ */

template< bool B, class T = void >
struct enable_if {
};

template< class T >
struct enable_if< true, T > {
	typedef T type;
};

/* ------------------------------------------------------------------------ */

template< class T > struct _libft_is_integral : public std::false_type {};

template< > struct _libft_is_integral< bool >				: public std::true_type {};
template< > struct _libft_is_integral< char >				: public std::true_type {};
template< > struct _libft_is_integral< signed char >		: public std::true_type {};
template< > struct _libft_is_integral< unsigned char >		: public std::true_type {};
template< > struct _libft_is_integral< short >				: public std::true_type {};
template< > struct _libft_is_integral< unsigned short >		: public std::true_type {};
template< > struct _libft_is_integral< int >				: public std::true_type {};
template< > struct _libft_is_integral< unsigned int >		: public std::true_type {};
template< > struct _libft_is_integral< long >				: public std::true_type {};
template< > struct _libft_is_integral< unsigned long >		: public std::true_type {};
template< > struct _libft_is_integral< long long >			: public std::true_type {};
template< > struct _libft_is_integral< unsigned long long >	: public std::true_type {};

// CHANGE TO FT::TRUE TYPE ! ^^

} // NAMESPACE FT
#endif // _LIBFT_TYPE_TRAITS_H_