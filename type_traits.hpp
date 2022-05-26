/* ************************************************************************ */
/*																			*/
/*							ft:: ITERATOR									*/
/*																			*/
/* ************************************************************************ */

#ifndef _LIBFT_TYPE_TRAITS_H_
# define _LIBFT_TYPE_TRAITS_H_

namespace ft {

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

} // NAMESPACE FT
#endif // _LIBFT_TYPE_TRAITS_H_