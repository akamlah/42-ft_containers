/* ************************************************************************ */
/*																			*/
/*							ft:: ITERATOR									*/
/*																			*/
/* ************************************************************************ */
/* ------------------------------- CONTENTS -----------------------------------------------------------

* tags
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

* traits
	template< class Iter > struct iterator_traits;
	specializations:
		template< class T > struct iterator_traits<T*>;
		template< class T > struct iterator_traits<const T*>;

* iterators
	template< typename T, class Category, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T& > struct iterator

* iterator adaptors
	template< class Iter >
	class reverse_iterator : public iterator
	<	typename iterator_traits<Iter>::iterator_category,
		typename iterator_traits<Iter>::value_type,
		typename iterator_traits<Iter>::difference_type
		typename iterator_traits<Iter>::pointer,
		typename iterator_traits<Iter>::reference >

---------------------------------------------------------------------------------------------------- */

#ifndef __FT_ITERATOR_HPP_
# define __FT_ITERATOR_HPP_

namespace ft {

/* ------------------------------------------------------------------------------------------------- */
/* TAGS */
/* ------------------------------------------------------------------------------------------------- */

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};

/* ------------------------------------------------------------------------------------------------- */
// ITERATOR TRAITS template overloads
/* ------------------------------------------------------------------------------------------------- */

template<class Iter>
struct iterator_traits {
	typedef typename Iter::difference_type		difference_type;
	typedef typename Iter::value_type			value_type;
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
	typedef typename Iter::iterator_category	iterator_category;
};

// specializations:

template<class T>
struct iterator_traits<T*> {
	typedef std::ptrdiff_t				difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template<class T>
struct iterator_traits<const T*> {
	typedef std::ptrdiff_t				difference_type;
	typedef T							value_type;
	typedef const T*					pointer;
	typedef const T&					reference;
	typedef random_access_iterator_tag	iterator_category;
};

/* ------------------------------------------------------------------------------------------------- */
// ITERATOR
/* ------------------------------------------------------------------------------------------------- */

template < class Category, typename T, class Distance = ptrdiff_t,
	class Pointer = T*, class Reference = T& >
struct iterator {
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

/* ------------------------------------------------------------------------------------------------- */
// ITERATOR ADAPTORS: reverse iterator
/* ------------------------------------------------------------------------------------------------- */

template< class Iter >
class reverse_iterator : public iterator 
		< typename iterator_traits<Iter>::iterator_category,
		typename iterator_traits<Iter>::value_type,
		typename iterator_traits<Iter>::difference_type,
		typename iterator_traits<Iter>::pointer,
		typename iterator_traits<Iter>::reference > {
public :
	typedef Iter												iterator_type;
	typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iter>::value_type			value_type;
	typedef typename iterator_traits<Iter>::difference_type		difference_type;
	typedef typename iterator_traits<Iter>::pointer				pointer;
	typedef typename iterator_traits<Iter>::reference			reference;
protected:
	iterator_type	_current;
public:
	reverse_iterator() {}
	explicit reverse_iterator( iterator_type x ): _current(x) {}
	template< class U > reverse_iterator( const reverse_iterator<U>& other ): _current(other.base()) {}
	template< class U > reverse_iterator& operator=( const reverse_iterator < U >& other )
		{ _current = other.base(); return (*this); }
	~reverse_iterator() {}

	iterator_type base() const { return (_current); }
	reference operator*() const { Iter tmp = _current; return *(--tmp); }
	pointer operator->() const { return (&(operator*())); }
	reference operator[]( difference_type n ) const { return (*(*this + n)); }
	reverse_iterator& operator++() { --_current; return (*this); }
	reverse_iterator& operator--() { ++_current; return (*this); }
	reverse_iterator operator++( int ) { reverse_iterator old = *this; --_current; return (old); }
	reverse_iterator operator--( int ) { reverse_iterator old = *this; ++_current; return (old); }
	reverse_iterator operator+( difference_type n ) const { return (reverse_iterator(_current - n)); }
	reverse_iterator operator-( difference_type n ) const { return (reverse_iterator(_current + n)); }
	reverse_iterator& operator+=( difference_type n ) { _current -= n; return (*this); }
	reverse_iterator& operator-=( difference_type n ) { _current += n; return (*this); }
}; // reverse_iterator

// reverse_iterator operator==,!=,<,<=,>,>=,<=>

template< class Iter1, class Iter2 >
bool operator==( const ft::reverse_iterator<Iter1>& lhs,
				const ft::reverse_iterator<Iter2>& rhs ) {
	return (lhs.base() == rhs.base());
}

template< class Iter1, class Iter2 >
bool operator!=( const ft::reverse_iterator< Iter1 >& lhs,
				const ft::reverse_iterator< Iter2 >& rhs ) {
	return (lhs.base() != rhs.base());
}

template< class Iter1, class Iter2 >
bool operator<( const ft::reverse_iterator<Iter1>& lhs,
				const ft::reverse_iterator<Iter2>& rhs ) {
	return (lhs.base() > rhs.base());
}

template< class Iter1, class Iter2 >
bool operator<=( const ft::reverse_iterator<Iter1>& lhs,
				const ft::reverse_iterator<Iter2>& rhs ) {
	return (lhs.base() >= rhs.base());
}

template< class Iter1, class Iter2 >
bool operator>( const ft::reverse_iterator<Iter1>& lhs,
				const ft::reverse_iterator<Iter2>& rhs ) {
	return (lhs.base() < rhs.base());
}

template< class Iter1, class Iter2 >
bool operator>=( const ft::reverse_iterator<Iter1>& lhs,
				const ft::reverse_iterator<Iter2>& rhs ) {
	return (lhs.base() <= rhs.base());
}

template< class Iter >
reverse_iterator<Iter>
	operator+( typename reverse_iterator<Iter>::difference_type n,
				const reverse_iterator<Iter>& it ) {
	return (reverse_iterator< Iter >(it.base() - n));
}

template< class Iter1, class Iter2 >
typename reverse_iterator< Iter1 >::difference_type
	operator-( const reverse_iterator< Iter1 >& lhs,
				const reverse_iterator< Iter2 >& rhs ) {
	return (rhs.base() - lhs.base());
}

/* ------------------------------------------------------------------------------------------------- */

} // NAMESPACE FT

#endif // __FT_ITERATOR_HPP_
