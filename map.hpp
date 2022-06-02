/* ************************************************************************ */
/*																			*/
/*								ft:: MAP									*/
/*																			*/
/* ************************************************************************ */

/* ------------------------------- CONTENTS ----------------------------------
TYPEDEFS
	key_type
	mapped_type
	key_compare
	allocator_type
	value_type //replace with ft::
	size_type // std::size_t
	difference_type // std::ptrdiff_t
	reference
	const_reference
	pointer
	const_pointer
	iterator // bidir. legacy iterator to value_type
	const_iterator
	reverse_iterator
	const_reverse_iterator
MEMBER CLASSSES
	value_compare (ft::map<Key,T,Compare,Allocator>::value_compare)
MEMBER FUNCTIONS
	map();
	explicit map(const Compare& comp, const Allocator& alloc = Allocator());
	template< class InputIt >
	map(InputIt first, InputIt last, const Compare& comp = Compare(),
		const Allocator& alloc = Allocator());
	map(const map& other);
	~map();
	map& operator=( const map& other );
	allocator_type get_allocator() const;
	T& at( const Key& key );
	const T& at( const Key& key ) const;
	T& operator[]( const Key& key );
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;
	bool empty() const;
	size_type size() const;
	size_type max_size() const;
	ft::pair<iterator, bool> insert( const value_type& value );
	iterator insert( iterator hint, const value_type& value );
	template< class InputIt >
	void insert( InputIt first, InputIt last );
	void clear();
	void erase( iterator pos );
	void erase( iterator first, iterator last );
	size_type erase( const Key& key );
	void swap( map& other );
	size_type count( const Key& key ) const;
	iterator find( const Key& key );
	const_iterator find( const Key& key ) const;
	ft::pair<iterator,iterator> equal_range( const Key& key );
	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
	iterator lower_bound( const Key& key );
	const_iterator lower_bound( const Key& key ) const;
	iterator upper_bound( const Key& key );
	const_iterator upper_bound( const Key& key ) const;
	key_compare key_comp() const;
	ft::map::value_compare value_comp() const;
NON MEMBER FUNCTIONS
	template< class Key, class T, class Compare, class Alloc >
	bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs);
--------------------------------------------------------------------------- */

#ifndef __FT_MAP_HPP_
# define __FT_MAP_HPP_

// std::
#include <iostream>
#include <functional>

// ft::
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "__tree.hpp"

/* ------------------------------------------------------------------------ */

namespace ft { /* NAMESPACE FT */

template <  /* MAP */
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {

public:

/* ======================== TYPEDEFS ====================================== */

	typedef Key			key_type;
	typedef T			mapped_type;
	typedef Compare		key_compare;
	typedef Allocator	allocator_type;

	typedef typename ft::pair<const Key, T>			value_type;
	typedef typename allocator_type::size_type			size_type; // std::size_t
	typedef typename allocator_type::difference_type	difference_type; // std::ptrdiff_t

	typedef value_type&			reference;
	typedef const value_type&	const_reference;

	typedef typename allocator_type::pointer		pointer;
	typedef typename allocator_type::const_pointer	const_pointer;

	// typedef typename 	iterator // bidir. legacy iterator to value_type
	// typedef typename 	const_iterator
	// typedef typename 	reverse_iterator
	// typedef typename 	const_reverse_iterator

/* ======================== MEMBER CLASSES ================================ */

	/*  VALUE_COMPARE
		Function object that compares objects of type ft::map::value_type
		(key-value pairs) by comparing of the first components of the pairs */
	class value_compare
		: public std::binary_function<value_type, value_type, bool> {

	public:
	
		typedef bool									result_type;
		typedef typename std::binary_function<
			value_type, value_type, bool >::value_type	first_argument_type;
		typedef typename std::binary_function<
			value_type, value_type, bool>::value_type	second_argument_type;

	protected:

		key_compare comp;

		value_compare(Compare c) : comp(c) {}

		bool operator()( const value_type& lhs, const value_type& rhs ) const {
			return (comp(lhs.first, rhs.first));
		}

	};

/* ======================== ATTRIBUTES ==================================== */

private:

	// __tree _base;

/* ------------------------------------------------------------------------ */
/* ======================== MEMBER FUNCTIONS ============================== */
/* ------------------------------------------------------------------------ */

public:

/* ------------------------ construction: --------------------------------- */

	map();

	explicit map(const Compare& comp, const Allocator& alloc = Allocator());

	template< class InputIt >
	map(InputIt first, InputIt last, const Compare& comp = Compare(),
		const Allocator& alloc = Allocator());

	map(const map& other);

/* ------------------------ destruction: ---------------------------------- */

	~map();

/* ------------------------ assignment: ---------------------------------- */

	map& operator=( const map& other );

/* ======================== ACCESSORS ===================================== */

/* ------------------------ allocator: ------------------------------------ */

	allocator_type get_allocator() const;

/* ------------------------ elements: ------------------------------------- */

	T& at( const Key& key );
	
	const T& at( const Key& key ) const;

	T& operator[]( const Key& key );

/* ------------------------ iterators: ------------------------------------ */

	// iterator begin();
	// const_iterator begin() const;
	// iterator end();
	// const_iterator end() const;
	// reverse_iterator rbegin();
	// const_reverse_iterator rbegin() const;
	// reverse_iterator rend();
	// const_reverse_iterator rend() const;

/* ------------------------ capacity: ------------------------------------- */

	bool empty() const;
	size_type size() const;
	size_type max_size() const;

/* ======================== MODIFIERS ===================================== */

/* ------------------------ insertion: ------------------------------------ */

	// ft::pair<iterator, bool> insert( const value_type& value );
	
	// iterator insert( iterator hint, const value_type& value );
	
	template< class InputIt >
	void insert( InputIt first, InputIt last );

/* ------------------------ deletion -------------------------------------- */

	void clear();

	// void erase( iterator pos );

	// void erase( iterator first, iterator last );

	size_type erase( const Key& key );

/*  ----------------------- swap: ----------------------------------------- */

	void swap( map& other );

/* ======================== LOOKUP ======================================== */

	size_type count( const Key& key ) const;

	// iterator find( const Key& key );

	// const_iterator find( const Key& key ) const;

	// ft::pair<iterator,iterator> equal_range( const Key& key );

	// ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

	// iterator lower_bound( const Key& key );
	
	// const_iterator lower_bound( const Key& key ) const;

	// iterator upper_bound( const Key& key );

	// const_iterator upper_bound( const Key& key ) const;

/* ======================== OBSERVERS ===================================== */

	key_compare key_comp() const;

	value_compare value_comp() const;

/* ======================== INTERNAL FUNCTIONALITIES ====================== */

private:

	/* debugging util. activates if flag DBG is defined */
	void __dbg_funcid(const char* msg1, const char* msg2, void* address) const {
		#if DBG
			std::cout << "\033[38;5;37m";
			std::cout << msg << " ";
			if (msg2 != NULL)
				std::cout << msg2 << " ";
			if (address != NULL)
				std::cout << address << " ";
			std::cout << "\033[0m";
			std::cout << std::endl;
		#endif
		(void)msg1; (void)msg2; (void)address;
	}

}; /* MAP */

/* - NON MEMBER FUNCTIONS ------------------------------------------------- */
/* operator==,!=,<,<=,>,>=,<=> */

template< class Key, class T, class Compare, class Alloc >
bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs,
	const ft::map<Key,T,Compare,Alloc>& rhs);

template< class Key, class T, class Compare, class Alloc >
bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs,
	const ft::map<Key,T,Compare,Alloc>& rhs);

template< class Key, class T, class Compare, class Alloc >
bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs,
	const ft::map<Key,T,Compare,Alloc>& rhs);

template< class Key, class T, class Compare, class Alloc >
bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs,
	const ft::map<Key,T,Compare,Alloc>& rhs);

template< class Key, class T, class Compare, class Alloc >
bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs);

template< class Key, class T, class Compare, class Alloc >
bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs,
	const ft::map<Key,T,Compare,Alloc>& rhs);

// + swap spec
/* - end MAP -------------------------------------------------------------- */

} /* NAMESPACE FT end ------------------------------------------------------*/
#endif // __FT_MAP_HPP_
