/* ************************************************************************ */
/*																			*/
/*								ft:: STACK									*/
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

#ifndef __FT_STACK_HPP__
# define __FT_STACK_HPP__

#include "vector.hpp"
#include "iterator.hpp"


namespace ft { /* NAMESPACE FT -------------------------------------------- */

template< typename T, class Container = ft::vector<T> > // STACK --------- */
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

	// stack(): c() { __dbg_funcid(__PRETTY_FUNCTION__); } // default
	// virtual ~stack() { __dbg_funcid(__PRETTY_FUNCTION__); } // default
	explicit stack(const Container& cont = Container()): c(cont) { __dbg_funcid(__PRETTY_FUNCTION__); }
	stack(const stack& other): c(other.c) { __dbg_funcid(__PRETTY_FUNCTION__); }

	stack& operator=( const stack& other ) { c = other.c; return (*this); }

	reference top() { return (c.back()); }
	const_reference top() const { return (c.back()); }
	bool empty() const { return (c.empty()); }
	size_type size() const { return (c.size()); }

	void push( const value_type& value ) { c.push_back(value); }
	void pop() { c.pop_back(); }

	template< class __T, class __Container >
	friend bool operator==( const stack<__T,__Container>& lhs,
		const stack<__T,__Container>& rhs );

	template< class __T, class __Container >
	friend bool operator<( const ft::stack<__T,__Container>& lhs,
		const stack<__T,__Container>& rhs );

private:

	void __dbg_funcid(const char * msg) const {
		#if DBG
			std::cout << "\033[38;5;128m" << msg << "\033[0m" << std::endl; 
		#endif
		(void)msg;
	}

}; // STACK --------------------------------------------------------------- */

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

#endif // __FT_STACK_HPP__
