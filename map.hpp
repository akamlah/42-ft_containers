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
#include <iostream> // REMOVE
#include <functional>  // REMOVE ?

//TEST ONLY
#include <__tree> // REMOVE

// ft::
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "rb_tree.hpp"

namespace ft { /* NAMESPACE FT */

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// template <class TreeIterator>
// class map_iterator {
// 	typedef TreeIterator							tree_ite_type;
// 	typedef bidirectional_iterator_tag				iterator_category;
// 	typedef typename tree_ite_type::value_type		value_type; // PAIR
// 	typedef typename tree_ite_type::difference_type	difference_type;
// 	typedef typename tree_ite_type::reference		reference;
// 	typedef typename tree_ite_type::pointer			pointer;
// 	typedef typename tree_ite_type::node_pointer	node_pointer;
// private:
// 	tree_ite_type	_tree_ite;
// public:
// 	map_iterator(const tree_ite_type& tree_ite): _tree_ite(tree_ite) {}
// 	map_iterator(const map_iterator& other): _tree_ite(other._tree_ite) {}
// 	tree_ite_type get_tree_ite() const { return(_tree_ite); }
// 	map_iterator& operator=(const map_iterator& other) { _tree_ite = other._tree_ite; return(*this); }

// 	reference operator*() const { return(*_tree_ite); } // ???????????????????????????????????????????
// 	pointer operator->() const { return (std::addressof(operator*())); }

// 	map_iterator& operator++() { ++_tree_ite; return (*this); }
// 	map_iterator& operator--() { --_tree_ite; return (*this); }
// 	map_iterator operator++(int) { tree_ite_type old = _tree_ite; ++_tree_ite; return(map_iterator(old)); }
// 	map_iterator operator--(int) { tree_ite_type old = _tree_ite; --_tree_ite; return(map_iterator(old)); }
	
// 	friend bool operator==(const map_iterator& lhs, const map_iterator& rhs)
// 		{ return(lhs.get_tree_ite() == rhs.get_tree_ite()); }
// 	friend bool operator!=(const map_iterator& lhs, const map_iterator& rhs)
// 		{ return(!(lhs == rhs)); }
// };

// template <class TreeConstIterator>
// class map_const_iterator {
// 	typedef TreeConstIterator								tree_const_ite_type;
// 	typedef bidirectional_iterator_tag						iterator_category;
// 	typedef typename tree_const_ite_type::value_type		value_type; // PAIR
// 	typedef typename tree_const_ite_type::difference_type	difference_type;
// 	typedef typename tree_const_ite_type::const_reference			const_reference;
// 	typedef typename tree_const_ite_type::const_pointer			const_pointer;
// 	typedef typename tree_const_ite_type::node_pointer		node_pointer;

// 	// todo
// };

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template < /* MAP */
	class Key,
	class T,
	class Compare = std::less<Key>,
	// class Allocator = std::allocator<ft::pair<const Key, T> > >
	class Allocator = std::allocator<std::pair<const Key, T> > > // TESTING - UNCOMMENT ALSO IN TYPEDEFS
class map {

public:

	class value_compare;

	typedef Key			key_type;
	typedef T			mapped_type;
	typedef Compare		key_compare;
	typedef Allocator	allocator_type;

	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;

	// typedef typename ft::pair<const Key, T>			value_type; // TO SOLVE !
	typedef typename std::pair<const Key, T>		value_type;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef typename allocator_type::pointer		pointer;
	typedef typename allocator_type::const_pointer	const_pointer;

	typedef ft::rb_tree<value_type, value_compare, allocator_type>	tree_type;

	// typedef typename tree_type::iterator			tree_iterator;
	// typedef map_iterator<tree_iterator>				iterator;
	// typedef map_const_iterator<typename tree_type::const_iterator>	const_iterator;
	// typedef typename 						reverse_iterator
	// typedef typename 						const_reverse_iterator

/* ======================== MEMBER CLASS ================================= */

// 	/* 
// 		VALUE_COMPARE
// 		Function object that compares objects of type ft::map::value_type
// 		(key-value pairs) by comparing of the first components of the pairs
// 	*/
// 	class value_compare { // ???
// 	public:
// 		typedef bool result_type;
// 	protected:
// 		key_compare comp;

// 		value_compare(Compare c) : comp(c) {}
// 		bool operator()( const value_type& lhs, const value_type& rhs ) const {
// 			return (comp(lhs.first, rhs.first));
// 		}
// 	};

// /* ======================== ATTRIBUTES ==================================== */

// private:

// 	tree_type _tree;

// /* ------------------------------------------------------------------------ */
// /* ======================== MEMBER FUNCTIONS ============================== */
// /* ------------------------------------------------------------------------ */

// public:

// /* ------------------------ construction: --------------------------------- */

// 	map() {}

// 	explicit map(const Compare& comp, const Allocator& alloc = Allocator());

// 	template< class InputIt >
// 	map(InputIt first, InputIt last, const Compare& comp = Compare(),
// 		const Allocator& alloc = Allocator());

// 	map(const map& other);

// /* ------------------------ destruction: ---------------------------------- */

// 	~map() {}

// /* ------------------------ assignment: ---------------------------------- */

// 	map& operator=( const map& other );

// /* ======================== ACCESSORS ===================================== */

// 	bool empty() const;
// 	size_type size() const { return(_tree.size());}
// 	size_type max_size() const;

// 	allocator_type get_allocator() const;

// 	T& at( const Key& key );
// 	const T& at( const Key& key ) const;
// 	T& operator[]( const Key& key );

// 	iterator begin() { return (iterator(_tree.begin())); }
// 	const_iterator begin() const;
// 	iterator end() { return (iterator(_tree.end())); }; // ?????????????????
// 	const_iterator end() const;

// 	// reverse_iterator rbegin();
// 	// const_reverse_iterator rbegin() const;
// 	// reverse_iterator rend();
// 	// const_reverse_iterator rend() const;

// /* ======================== MODIFIERS ===================================== */

// /* ------------------------ insertion: ------------------------------------ */

// // Returns a pair consisting of an iterator to the inserted element (or to the 
// // element that prevented the insertion) and a bool denoting whether the insertion took place.
// 	// ft::pair<iterator, bool> insert( const value_type& value ) {
// 	std::pair<iterator, bool> insert( const value_type& value ) {
// 		tree_iterator x(_tree.search(value));
// 		if (x.get_node_ptr() != NULL)
// 			return(std::make_pair(iterator(x), false));
// 		return (std::make_pair(iterator(tree_iterator(_tree.insert(value))), true)); // change std::make_pair
// 	}

// 	iterator insert( iterator hint, const value_type& value );

// 	template< class InputIt >
// 	void insert( InputIt first, InputIt last );

// /* ------------------------ deletion -------------------------------------- */

// 	void clear();

// 	void erase( iterator pos );

// 	void erase( iterator first, iterator last );

// 	size_type erase( const Key& key );

// /*  ----------------------- swap: ----------------------------------------- */

// 	void swap( map& other );

// /* ======================== LOOKUP ======================================== */

// 	size_type count( const Key& key ) const;

// 	iterator find( const Key& key );

// 	const_iterator find( const Key& key ) const;

// 	ft::pair<iterator,iterator> equal_range( const Key& key );

// 	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

// 	iterator lower_bound( const Key& key );
	
// 	const_iterator lower_bound( const Key& key ) const;

// 	iterator upper_bound( const Key& key );

// 	const_iterator upper_bound( const Key& key ) const;

// /* ======================== OBSERVERS ===================================== */

// 	key_compare key_comp() const;

// 	value_compare value_comp() const;

}; /* MAP */

/* - NON MEMBER FUNCTIONS ------------------------------------------------- */
/* operator==,!=,<,<=,>,>=,<=> */

// template< class Key, class T, class Compare, class Alloc >
// bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs,
// 	const ft::map<Key,T,Compare,Alloc>& rhs);

// template< class Key, class T, class Compare, class Alloc >
// bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs,
// 	const ft::map<Key,T,Compare,Alloc>& rhs);

// template< class Key, class T, class Compare, class Alloc >
// bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs,
// 	const ft::map<Key,T,Compare,Alloc>& rhs);

// template< class Key, class T, class Compare, class Alloc >
// bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs,
// 	const ft::map<Key,T,Compare,Alloc>& rhs);

// template< class Key, class T, class Compare, class Alloc >
// bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs,
// 				const ft::map<Key,T,Compare,Alloc>& rhs);

// template< class Key, class T, class Compare, class Alloc >
// bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs,
// 	const ft::map<Key,T,Compare,Alloc>& rhs);

// + swap spec
/* - end MAP -------------------------------------------------------------- */

} /* NAMESPACE FT end ------------------------------------------------------*/
#endif // __FT_MAP_HPP_
