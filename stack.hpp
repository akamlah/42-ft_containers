/* ************************************************************************ */
/*								ft:: STACK									*/
/*																			*/
/*																			*/
/* ************************************************************************ */
/* ------------------------------- CONTENTS ----------------------------------
TYPEDEFS
		container_type
		value_type
		size_type
		reference
		const_reference
MEMBER FUNCTIONS
		(constructor)
		(destructor)
		operator=
	ACCESSORS
		top
		Capacity
		empty
		size
	MODIFIERS
		push
		pop
NON MEMBER FUNCTIONS
	operator==,!=,<,<=,>,>=,<=>
--------------------------------------------------------------------------- */


#ifndef _STACK_HPP__
# define _STACK_HPP__

#include "vector.hpp"
#include "iterator.hpp"

namespace ft {

template< typename T, class Container = ft::vector<T> >
class stack {

public:

	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;

protected:

	container_type c;

public:

	// stack(): c() { __dbg_funcid(); } // default
	explicit stack(const Container& cont = Container()): c(cont) { __dbg_funcid(); }
	stack(const stack& other): c(other.c) { __dbg_funcid(); }
	// virtual ~stack() { __dbg_funcid(); } // default

	stack& operator=( const stack& other ) { c = other.c; return (*this); }


	reference top() { return (c.back()); }
	const_reference top() const { return (c.back()); }
	bool empty() const { return (c.empty()); }
	size_type size() const { return (c.size()); }


	void push( const value_type& value ) { c.push_back(value); }
	void pop() { c.pop_back(); }

private:

	void __dbg_funcid() {
		#if DBG
			std::cout << "\033[38;5;228m" <<__PRETTY_FUNCTION__ << "\033[0m" << std::endl; 
		#endif
	}

}; // STACK

/* - NON MEMBER FUNCTIONS ------------------------------------------------- */
/* operator==,!=,<,<=,>,>=,<=> */

template< class T, class Container >
bool operator==( const ft::stack<T,Container>& lhs,
	const ft::stack<T,Container>& rhs ) { return (lhs.c == rhs.c); }

template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& lhs,
	const ft::stack<T,Container>& rhs ) { return (!(lhs == rhs)); }

template< class T, class Container >
bool operator<( const ft::stack<T,Container>& lhs,
	const ft::stack<T,Container>& rhs ) { return (lhs.c < rhs.c); }

template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& lhs,
	const ft::stack<T,Container>& rhs ) { return (!(rhs < lhs)); }

template< class T, class Container >
bool operator>( const ft::stack<T,Container>& lhs,
	const ft::stack<T,Container>& rhs ) { return (rhs < lhs); }

template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& lhs,
	const ft::stack<T,Container>& rhs ) { return (!(lhs < rhs)); }

} // NAMESPACE_FT

#endif // _STACK_HPP__
