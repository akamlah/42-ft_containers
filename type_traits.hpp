/* ************************************************************************ */
/*																			*/
/*							ft:: ITERATOR									*/
/*																			*/
/* ************************************************************************ */

#ifndef _LIBFT_TYPE_TRAITS_H_
# define _LIBFT_TYPE_TRAITS_H_

#include <type_traits>

namespace ft {
// note: std defines true_type and false_type as struct _LIBCPP_BOOL...whatever
/* ------------------------------------------------------------------------ */

/* CONTENTS ------------------------------------------------------------------

enable if

helper class ft::bool_constant
typedefs true_type, false_type
is_integral templates for every type that is integer

--------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------ */
/* ENABLE IF 
If B is true, std::enable_if has a public member typedef type, equal to T;
otherwise, there is no member typedef.
*/

template< bool B, class T = void >
struct enable_if {
};

template< class T >
struct enable_if< true, T > {
	typedef T type;
};

/* ------------------------------------------------------------------------ */
/* IS INTEGRAL
Checks whether T is an integral type. Provides the member constant value
which is equal to true, if T is the type bool, char, char8_t (since C++20),
char16_t, char32_t, wchar_t, short, int, long, long long, or any
implementation-defined extended integer types, including any signed,
unsigned, and cv-qualified variants. Otherwise, value is equal to false.
*/

/* helper class bool */
template<bool __v = true>
class bool_constant {

	private :

		static const bool _value = __v;

	public:

		typedef bool			value_type;
		typedef bool_constant	type;

		operator value_type() const { return (_value); }

};

typedef bool_constant< (true) >		true_type;
typedef bool_constant< (false) >	false_type;

template< class T > struct _libft_is_integral 				: public false_type {};
template< > struct _libft_is_integral< bool >				: public true_type {};
template< > struct _libft_is_integral< char >				: public true_type {};
template< > struct _libft_is_integral< signed char >		: public true_type {};
template< > struct _libft_is_integral< unsigned char >		: public true_type {};
template< > struct _libft_is_integral< short >				: public true_type {};
template< > struct _libft_is_integral< unsigned short >		: public true_type {};
template< > struct _libft_is_integral< int >				: public true_type {};
template< > struct _libft_is_integral< unsigned int >		: public true_type {};
template< > struct _libft_is_integral< long >				: public true_type {};
template< > struct _libft_is_integral< unsigned long >		: public true_type {};
// c++11:
// template< > struct _libft_is_integral< long long >			: public true_type {};
// template< > struct _libft_is_integral< unsigned long long >	: public true_type {};

/* ------------------------------------------------------------------------ */

} // NAMESPACE FT
#endif // _LIBFT_TYPE_TRAITS_H_
