/* ************************************************************************ */
/*																			*/
/*							ft:: ITERATOR									*/
/*																			*/
/* ************************************************************************ */

#ifndef _LIBFT_ITERATOR_H_
# define _LIBFT_ITERATOR_H_

namespace ft {

/* ------------------------------------------------------------------------ */
/* CONTENTS ------------------------------------------------------------------

* tags
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

* templates

	template< class Iter >
	struct iterator_traits;

	template< class T >
	struct iterator_traits<T*>;

	template< class T >
	struct iterator_traits<const T*>;

--------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------ */

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};

// overloas accessors for every type

/* ------------------------------------------------------------------------ */

template<class Iter>
struct iterator_traits {
	typedef typename Iter::difference_type		difference_type;
	typedef typename Iter::value_type			value_type;
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
	typedef typename Iter::iterator_category	iterator_category;
}; // ITERATOR_TRAITS

/* ------------------------------------------------------------------------ */

template<class T>
struct iterator_traits<T*> {
	typedef std::ptrdiff_t				difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
}; // ITERATOR_TRAITS<T*>

/* ------------------------------------------------------------------------ */

template<class T>
struct iterator_traits<const T*> {
	typedef std::ptrdiff_t				difference_type;
	typedef T							value_type;
	typedef const T*					pointer;
	typedef const T&					reference;
	typedef random_access_iterator_tag	iterator_category;
}; // ITERATOR_TRAITS<const T*>

/* ------------------------------------------------------------------------ */

template< typename T, class Category, class Distance = ptrdiff_t, 
	class Pointer = T*, class Reference = T& >
struct iterator {
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
}; // FT ITERATOR

/* ------------------------------------------------------------------------ */

template< typename T >
class reverse_iterator {
public:
	reverse_iterator(iterator& it); // const ?
	iterator base() const; // comverts back to normal ite
}; // FT REVERSE ITERATOR

// template <class _Iter>
// class _LIBCPP_TEMPLATE_VIS reverse_iterator
//     : public iterator<typename iterator_traits<_Iter>::iterator_category,
//                       typename iterator_traits<_Iter>::value_type,
//                       typename iterator_traits<_Iter>::difference_type,
//                       typename iterator_traits<_Iter>::pointer,
//                       typename iterator_traits<_Iter>::reference>

/* ------------------------------------------------------------------------ */

} // NAMESPACE FT

#endif // _LIBFT_ITERATOR_H_