/* ************************************************************************ */
/*																			*/
/*								ft:: set									*/
/*																			*/
/* ************************************************************************ */

#ifndef __FT_set_HPP_
# define __FT_set_HPP_

// std::
#include <iostream> // REMOVE

// ft::
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "rb_tree.hpp"

namespace ft { /* NAMESPACE FT */

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template< /* SET */
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
> class set {

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

public:

	typedef Key											key_type;
	typedef Key											value_type;
	typedef Compare										key_compare;
	typedef Compare										value_compare;
	typedef Allocator									allocator_type;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef value_type&									reference;
	typedef const value_type&							const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

private:

	typedef ft::rb_tree<value_type, value_compare, allocator_type>	tree_type;
	typedef typename tree_type::iterator							tree_iterator;
	typedef typename tree_type::const_iterator						tree_const_iterator;

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

public:

	typedef tree_iterator									iterator;
	typedef tree_const_iterator								const_iterator;
	typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// attributes - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

private:

	value_compare	_compare;
	allocator_type	_allocator;
	tree_type		_tree;

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 

public:
// private:
	void print() const { _tree.print_tree(); } // DEBUGGING - REMOVE

// publilc member functions - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	set() {}

	explicit set(const Compare& comp, const Allocator& alloc = Allocator())
		: _compare(comp), _allocator(alloc) {}

	template< class InputIt >
	set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
		: _compare(comp), _allocator(alloc)
		{ insert(first, last); }

	set(const set& other): _compare(other._compare), _allocator(other._allocator), _tree(other._tree) { }

	~set() {}

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

	set& operator=( const set& other ) { _tree = other._tree; return (*this); }

// accessors - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

	bool empty() const { return (_tree.empty()); }
	size_type size() const { return(_tree.size()); }
	size_type max_size() const { return(_tree.node_allocator().max_size()); }
	allocator_type get_allocator() const { return(_allocator); }
	key_compare key_comp() const { return(_compare); }
	value_compare value_comp() const { return(_compare); }

// private:
	iterator begin() { return (_tree.begin()); }
	iterator end() { return (_tree.end()); }
	const_iterator begin() const { return (_tree.begin()); }
	const_iterator end() const { return (_tree.end()); }
	reverse_iterator rbegin() {return(_tree.rbegin()); }
	reverse_iterator rend() { return(_tree.rend()); }
	const_reverse_iterator rbegin() const { return(_tree.rbegin()); }
	const_reverse_iterator rend() const { return(_tree.rend()); }
// public:

// modifiers - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	// Returns a pair consisting of an iterator to the inserted element (or to the 
	// element that prevented the insertion) and a bool denoting whether the insertion took place.
	ft::pair<iterator, bool> insert(const value_type& value) {
		iterator x = find(value);
		if (x != end())
			return(ft::pair<iterator, bool>(x, false));
		return (ft::pair<iterator, bool>(_tree.insert(value), true));
	}

	// Inserts value in the position as close as possible to hint.
	// Returns an iterator to the inserted element, or to the element that prevented the insertion.
	iterator insert(iterator hint, const value_type& value) {
		iterator x = find(value);
		if (x != end())
			return(x);
		return (_tree.insert(value));
		(void)hint;
	}

	// Inserts elements from range [first, last). If multiple elements in the range
	// have keys that compare equivalent, it is unspecified which element is inserted
	template< class InputIt >
	void insert(InputIt first, InputIt last) {
		for (InputIt cont_ite = first; cont_ite != last; cont_ite++) {
			iterator x = find(*cont_ite);
			if (x == end())
				_tree.insert(*cont_ite);
		}
	}

	void clear() { if (!empty()) { _tree.clear(); } }

	// Removes the element at pos.
	void erase( iterator pos ) {
		if (pos != end())
			_tree.erase(pos);
	}

	// Removes the elements in the range [first; last), which must be a valid range in *this
	void erase(iterator first, iterator last) {
		_tree.erase(first, last);
	}

	// Removes the element (if one exists) with the key equivalent to key.
	// Returns the number of elements removed (0 or 1).
	size_type erase(const Key& key) {
		iterator x = find(key);
		if (x != end()) {
			_tree.erase(x);
			return (1);
		}
		return (0);
	}

// swap - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	void swap( set& other ) { _tree.swap(other._tree); }

// lookup - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	// Returns the number of elements with key key, which is either 1 or 0 since this container
	// does not allow duplicates.
	size_type count( const Key& key ) const {
		if (find(key) != end())
			return (1);
		return (0);
	}

	// Finds an element with key equivalent to key.
	// If no such element is found, or set is empty, end() is returned.
	iterator find( const Key& key ) {
		if (!empty())
			for (iterator x = begin(); x != end(); x++) {
				if (*x == key)
					return (x) ;
			}
		return (end());
	}

	const_iterator find( const Key& key ) const {
		if (!empty())
			for (const_iterator x = begin(); x != end(); x++) {
				if (*x == key)
					return (x) ;
			}
		return (end());
	}

	// Returns a range containing all elements with the given key in the container.
	// The range is defined by two iterators, one pointing to the first element
	// that is not less than key and another pointing to the first element greater than key.
	ft::pair<iterator,iterator> equal_range( const Key& key ) {
		return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
	}

	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
		return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
	}

	iterator lower_bound( const Key& key ) {
		iterator x = find(key);
		if (x != end())
			return (x);
		x = begin();
		iterator y = x;
		while (y != end() && *x < key) {
			++y;
			if (*y > key)
				return (y);
			x = y;
		}
		return (x);
	}

	const_iterator lower_bound( const Key& key ) const {
		const_iterator x = find(key);
		if (x != end())
			return (x);
		x = begin();
		const_iterator y = x;
		while (y != end() && *x < key) {
			++y;
			if (*y > key)
				return (y);
			x = y;
		}
		return (x);
	}

	iterator upper_bound( const Key& key ) {
		iterator x = begin();
		while (x != end()) {
			if (*x > key)
				break ;
			++x;
		}
		return (x);
	}

	const_iterator upper_bound( const Key& key ) const {
		const_iterator x = begin();
		while (x != end()) {
			if (*x > key)
				break ;
			++x;
		}
		return (x);
	}

}; /* set */

/* - NON MEMBER FUNCTIONS ------------------------------------------------------------------------ */
/* operator==,!=,<,<=,>,>=,<=> */

template< class Key, class Compare, class Alloc >
bool operator==(const ft::set<Key,Compare,Alloc>& lhs,
	const ft::set<Key,Compare,Alloc>& rhs)
	{ return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

template< class Key, class Compare, class Alloc >
bool operator!=(const ft::set<Key,Compare,Alloc>& lhs,
	const ft::set<Key,Compare,Alloc>& rhs)
	{ return (!(lhs == rhs)); }

template< class Key, class Compare, class Alloc >
bool operator<(const ft::set<Key,Compare,Alloc>& lhs,
	const ft::set<Key,Compare,Alloc>& rhs)
	{ return (ft::lexicographical_compare (lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template< class Key, class Compare, class Alloc >
bool operator<=(const ft::set<Key,Compare,Alloc>& lhs,
	const ft::set<Key,Compare,Alloc>& rhs)
	{ return (!(rhs < lhs)); }

template< class Key, class Compare, class Alloc >
bool operator>(const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs)
	{ return (rhs < lhs); }

template< class Key, class Compare, class Alloc >
bool operator>=(const ft::set<Key,Compare,Alloc>& lhs,
	const ft::set<Key,Compare,Alloc>& rhs)
	{ return (!(lhs < rhs)); }

// + swap spec
/* - end set ------------------------------------------------------------------------------------- */

} /* NAMESPACE FT end ------------------------------------------------------*/
#endif // __FT_set_HPP_
