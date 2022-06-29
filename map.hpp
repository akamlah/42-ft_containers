/* ************************************************************************ */
/*																			*/
/*								ft:: MAP									*/
/*																			*/
/* ************************************************************************ */

#ifndef __FT_MAP_HPP_
# define __FT_MAP_HPP_

// std::
#include <iostream> // FOR DBG PRINT

// ft::
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "rb_tree.hpp"

namespace ft { /* NAMESPACE FT */

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template < /* MAP */
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
public:

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

	typedef typename ft::pair<const Key, T>				value_type;
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef Compare										key_compare;
	typedef Allocator									allocator_type;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef value_type&									reference;
	typedef const value_type&							const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

	struct value_compare {
		key_compare _c;
		value_compare(): _c() {}
		value_compare(const key_compare& c): _c(c) {}
		bool operator()( const value_type& lhs, const value_type& rhs ) const {
			return (_c(lhs.first, rhs.first));
		}
	};

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

protected:

	typedef ft::rb_tree<value_type, value_compare, allocator_type>	tree_type;
	typedef typename tree_type::iterator							tree_iterator;
	typedef typename tree_type::const_iterator						tree_const_iterator;

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

protected:

	class map_iterator {
	public:
		typedef bidirectional_iterator_tag				iterator_category;
		typedef typename tree_iterator::value_type		value_type;
		typedef typename tree_iterator::difference_type	difference_type;
		typedef typename tree_iterator::reference		reference;
		typedef typename tree_iterator::pointer			pointer;
	protected:
		tree_iterator	_tree_ite;
	public:
		map_iterator(): _tree_ite() {}
		map_iterator(const tree_iterator& tree_ite): _tree_ite(tree_ite) {}
		map_iterator(const map_iterator& other): _tree_ite(other._tree_ite) {}
		tree_iterator get_tree_ite() const { return(_tree_ite); }
		map_iterator& operator=(const map_iterator& other) { _tree_ite = other._tree_ite; return(*this); }
		reference operator*() const { return(*_tree_ite); }
		pointer operator->() const { return(&(*_tree_ite)); }
		map_iterator& operator++() { ++_tree_ite; return (*this); }
		map_iterator& operator--() { --_tree_ite; return (*this); }
		map_iterator operator++(int) { tree_iterator old = _tree_ite; ++_tree_ite; return(map_iterator(old)); }
		map_iterator operator--(int) { tree_iterator old = _tree_ite; --_tree_ite; return(map_iterator(old)); }
		friend bool operator==(const map_iterator& lhs, const map_iterator& rhs)
			{ return(lhs.get_tree_ite() == rhs.get_tree_ite()); }
		friend bool operator!=(const map_iterator& lhs, const map_iterator& rhs)
			{ return(!(lhs == rhs)); }
	};

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

public:

	typedef map_iterator	iterator;

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

protected:

	class map_const_iterator {
	public:
		typedef bidirectional_iterator_tag						iterator_category;
		typedef typename tree_const_iterator::value_type		value_type;
		typedef typename tree_const_iterator::difference_type	difference_type;
		typedef typename tree_const_iterator::reference			reference;
		typedef typename tree_const_iterator::pointer			pointer;
	protected:
		iterator	_nc_ite;
	public:
		map_const_iterator(): _nc_ite() {}
		map_const_iterator(const map_const_iterator& other): _nc_ite(other._nc_ite) {}
		map_const_iterator(const tree_const_iterator& const_tree_ite): _nc_ite(iterator(const_tree_ite.get_base_ite())) {}
		map_const_iterator(const iterator& nc_ite): _nc_ite(nc_ite) {}
		tree_const_iterator get_tree_ite() const { return(_nc_ite.get_tree_ite()); }
		map_const_iterator& operator=(const map_const_iterator& other) { _nc_ite = other._nc_ite; return(*this); }
		reference operator*() const { return((_nc_ite.get_tree_ite()).get_base_ptr()->value); }
		pointer operator->() const { return(&(*_nc_ite)); }
		map_const_iterator& operator++() { ++_nc_ite; return (*this); }
		map_const_iterator& operator--() { --_nc_ite; return (*this); }
		map_const_iterator operator++(int) { iterator old = _nc_ite; ++_nc_ite; return(map_const_iterator(old)); }
		map_const_iterator operator--(int) { iterator old = _nc_ite; --_nc_ite; return(map_const_iterator(old)); }
		friend bool operator==(const map_const_iterator& lhs, const map_const_iterator& rhs)
			{ return(lhs.get_tree_ite() == rhs.get_tree_ite()); }
		friend bool operator!=(const map_const_iterator& lhs, const map_const_iterator& rhs)
			{ return(!(lhs == rhs)); }
	};

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

public:

	typedef map_const_iterator								const_iterator;

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

public:

	map() {}

	explicit map(const Compare& comp, const Allocator& alloc = Allocator())
		: _compare(comp), _allocator(alloc) {}

	template< class InputIt >
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
		: _compare(comp), _allocator(alloc) { insert(first, last); }

	map(const map& other): _compare(other._compare), _allocator(other._allocator), _tree(other._tree) {}

	~map() {}

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

	map& operator=( const map& other ) { _tree = other._tree; return (*this); }

// accessors - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

	T& at( const Key& key ) {
		iterator x = find(key);
		if (x == end())
			throw std::out_of_range("Out of range");
		return (x->second);
	}

	const T& at( const Key& key ) const {
		const_iterator x = find(key);
		if (x == end())
			throw std::out_of_range("Out of range");
		return (x->second);
	}

	T& operator[](const Key& key) {
		iterator x = find(key);
		if (x == end())
			return (insert( ft::pair<Key, T>(key, T() ) )).first->second;
		return (x->second);
	}

	bool empty() const { return (_tree.empty()); }
	size_type size() const { return(_tree.size()); }
	size_type max_size() const { return(_tree.node_allocator().max_size()); }
	allocator_type get_allocator() const { return(_allocator); }
	key_compare key_comp() const { return(_compare._c); }
	value_compare value_comp() const { return(_compare); }

	iterator begin() { return (_tree.begin()); }
	iterator end() { return (_tree.end()); }
	const_iterator begin() const { return (_tree.begin()); }
	const_iterator end() const { return (_tree.end()); }

	reverse_iterator rbegin() {return(reverse_iterator(end())); }
	reverse_iterator rend() { return(reverse_iterator(begin())); }
	const_reverse_iterator rbegin() const { return(const_reverse_iterator(end())); }
	const_reverse_iterator rend() const { return(const_reverse_iterator(begin())); }

// modifiers - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	// Returns a pair consisting of an iterator to the inserted element (or to the 
	// element that prevented the insertion) and a bool denoting whether the insertion took place.
	ft::pair<iterator, bool> insert( const value_type& value ) {
		iterator x = find(value.first);
		if (x != end())
			return(ft::pair<iterator, bool>(x, false));
		return (ft::pair<iterator, bool>(iterator(_tree.insert(value)), true));
	}

	// Inserts value in the position as close as possible to hint.
	// Returns an iterator to the inserted element, or to the element that prevented the insertion.
	iterator insert( iterator hint, const value_type& value ) {
		iterator x = find(value.first);
		if (x != end())
			return(x);
		return (iterator(_tree.insert(value)));
		(void)hint;
	}

	// Inserts elements from range [first, last). If multiple elements in the range
	// have keys that compare equivalent, it is unspecified which element is inserted
	template< class InputIt >
	void insert( InputIt first, InputIt last ) {
		for (InputIt cont_ite = first; cont_ite != last; cont_ite++) {
			iterator x = find((*cont_ite).first);
			if (x == end())
				_tree.insert(*cont_ite);
		}
	}

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

	void clear() { if (!empty()) { _tree.clear(); } }

	// Removes the element at pos.
	void erase( iterator pos ) {
		if (pos != end())
			_tree.erase(pos.get_tree_ite());
	}

	// Removes the elements in the range [first; last), which must be a valid range in *this
	void erase( iterator first, iterator last ) {
		_tree.erase(first.get_tree_ite(), last.get_tree_ite());
	}

	// Removes the element (if one exists) with the key equivalent to key.
	// Returns the number of elements removed (0 or 1).
	size_type erase( const Key& key ) {
		iterator x = find(key);
		if (x != end()) {
			_tree.erase(x.get_tree_ite());
			return (1);
		}
		return (0);
	}

// swap - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	void swap( map& other ) { _tree.swap(other._tree); }

// lookup - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	// Returns the number of elements with key key, which is either 1 or 0 since this container
	// does not allow duplicates.
	size_type count( const Key& key ) const {
		if (find(key) != end())
			return (1);
		return (0);
	}

	// Finds an element with key equivalent to key.
	// If no such element is found, or map is empty, end() is returned.
	iterator find( const Key& key ) { //can be optimiedby not using it++ but recursive inorder-tree-walk
		if (!empty())
			for (iterator x = begin(); x != end(); x++) {
				if (x->first == key)
					return (x) ;
			}
		return (end());
	}

	const_iterator find( const Key& key ) const {
		if (!empty())
			for (const_iterator x = begin(); x != end(); x++) {
				if (x->first == key)
					return (x) ;
			}
		return (end());
	}

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

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
		while (y != end() && x->first < key) {
			++y;
			if (y->first > key)
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
		while (y != end() && x->first < key) {
			++y;
			if (y->first > key)
				return (y);
			x = y;
		}
		return (x);
	}

	iterator upper_bound( const Key& key ) {
		iterator x = begin();
		while (x != end()) {
			if (x->first > key)
				break ;
			++x;
		}
		return (x);
	}

	const_iterator upper_bound( const Key& key ) const {
		const_iterator x = begin();
		while (x != end()) {
			if (x->first > key)
				break ;
			++x;
		}
		return (x);
	}

}; /* MAP */

/* - NON MEMBER FUNCTIONS ------------------------------------------------------------------------ */
/* operator==,!=,<,<=,>,>=,<=> */

template< class Key, class T, class Compare, class Alloc >
bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs,
	const ft::map<Key,T,Compare,Alloc>& rhs)
	{ return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

template< class Key, class T, class Compare, class Alloc >
bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs,
	const ft::map<Key,T,Compare,Alloc>& rhs)
	{ return (!(lhs == rhs)); }

template< class Key, class T, class Compare, class Alloc >
bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs,
	const ft::map<Key,T,Compare,Alloc>& rhs)
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template< class Key, class T, class Compare, class Alloc >
bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs,
	const ft::map<Key,T,Compare,Alloc>& rhs)
	{ return (!(rhs < lhs)); }

template< class Key, class T, class Compare, class Alloc >
bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs)
	{ return (rhs < lhs); }

template< class Key, class T, class Compare, class Alloc >
bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs,
	const ft::map<Key,T,Compare,Alloc>& rhs)
	{ return (!(lhs < rhs)); }

// + swap spec
/* - end MAP ------------------------------------------------------------------------------------- */

} /* NAMESPACE FT end ------------------------------------------------------*/
#endif // __FT_MAP_HPP_
