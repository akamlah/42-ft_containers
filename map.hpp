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
-------------------------------------------------------------------------------------------------- */

#ifndef __FT_MAP_HPP_
# define __FT_MAP_HPP_

// std::
#include <iostream> // REMOVE
// #include <functional>  // REMOVE ?

//TEST ONLY
// #include <__tree> // REMOVE
// #include <map> // REMOVE

// ft::
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "rb_tree.hpp"

namespace ft { /* NAMESPACE FT */

// template<class,class,class> class rb_tree;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template < /* MAP */
	class Key,
	class T,
	class Compare = std::less<Key>, // TODO 
	class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
// template<class, class, class > friend class rb_tree;
public:

	typedef typename ft::pair<const Key, T>				value_type; // has overload << for debugging 
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

	class value_compare {
		private:
		key_compare _c;
		public:
		value_compare(): _c() {}
		value_compare(const key_compare& c): _c(c) {}
		key_compare& get_key_compare() const { return (_c); }
		bool operator()( const value_type& lhs, const value_type& rhs ) const {
			return (_c(lhs.first, rhs.first));
		}
	};

	typedef ft::rb_tree<value_type, value_compare, allocator_type>	tree_type;
	typedef typename tree_type::iterator			tree_iterator;
	typedef typename tree_type::const_iterator		tree_const_iterator;

	class map_iterator {
	public:
		typedef bidirectional_iterator_tag				iterator_category;
		typedef typename tree_iterator::value_type		value_type;
		typedef typename tree_iterator::difference_type	difference_type;
		typedef typename tree_iterator::reference		reference;
		typedef typename tree_iterator::pointer			pointer;
	private:
		tree_iterator	_tree_ite;
	public:
		map_iterator(): _tree_ite() {}
		map_iterator(const tree_iterator& tree_ite): _tree_ite(tree_ite) {}
		map_iterator(const map_iterator& other): _tree_ite(other._tree_ite) {}
		tree_iterator get_tree_ite() const { return(_tree_ite); }
		map_iterator& operator=(const map_iterator& other) { _tree_ite = other._tree_ite; return(*this); }
		reference operator*() const { return(*_tree_ite); }
		pointer operator->() const { return(std::addressof(*_tree_ite)); }
		map_iterator& operator++() { ++_tree_ite; return (*this); 
		// std::cout << "++mapite" <<std::endl;
		}
		map_iterator& operator--() { --_tree_ite; return (*this); 
		// std::cout << "--mapite" <<std::endl;
		}
		map_iterator operator++(int) { tree_iterator old = _tree_ite; ++_tree_ite; return(map_iterator(old)); }
		map_iterator operator--(int) { tree_iterator old = _tree_ite; --_tree_ite; return(map_iterator(old)); }
		friend bool operator==(const map_iterator& lhs, const map_iterator& rhs)
			{ return(lhs.get_tree_ite() == rhs.get_tree_ite()); }
		friend bool operator!=(const map_iterator& lhs, const map_iterator& rhs)
			{ return(!(lhs == rhs)); }
	};

	typedef map_iterator	iterator;

	class map_const_iterator {
	public:
		typedef bidirectional_iterator_tag						iterator_category;
		typedef typename tree_const_iterator::value_type		value_type;
		typedef typename tree_const_iterator::difference_type	difference_type;
		typedef typename tree_const_iterator::reference			reference;
		typedef typename tree_const_iterator::pointer			pointer;
	private:
		iterator	_nc_ite;
	public:
		map_const_iterator(): _nc_ite() {}
		map_const_iterator(const map_const_iterator& other): _nc_ite(other._nc_ite) {}
		map_const_iterator(const tree_const_iterator& const_tree_ite): _nc_ite(iterator(const_tree_ite.get_base_ite())) {}
		map_const_iterator(const iterator& nc_ite): _nc_ite(nc_ite) {}
		tree_const_iterator get_tree_ite() const { return(_nc_ite.get_tree_ite()); }
		map_const_iterator& operator=(const map_const_iterator& other) { _nc_ite = other._nc_ite; return(*this); }
		reference operator*() const { return((_nc_ite.get_tree_ite()).get_base_ptr()->value); }
		pointer operator->() const { return(std::addressof(*_nc_ite)); }
		map_const_iterator& operator++() { ++_nc_ite; return (*this); }
		map_const_iterator& operator--() { --_nc_ite; return (*this); }
		map_const_iterator operator++(int) { iterator old = _nc_ite; ++_nc_ite; return(map_const_iterator(old)); }
		map_const_iterator operator--(int) { iterator old = _nc_ite; --_nc_ite; return(map_const_iterator(old)); }
		friend bool operator==(const map_const_iterator& lhs, const map_const_iterator& rhs)
			{ return(lhs.get_tree_ite() == rhs.get_tree_ite()); }
		friend bool operator!=(const map_const_iterator& lhs, const map_const_iterator& rhs)
			{ return(!(lhs == rhs)); }
	};

	typedef map_const_iterator	const_iterator;

	// typedef typename 						reverse_iterator
	// typedef typename 						const_reverse_iterator

// /* ======================== ATTRIBUTES =========================================================== */

private:
value_compare _compare;
allocator_type _allocator;

tree_type _tree;

/* ----------------------------------------------------------------------------------------------- */
/* ======================== MEMBER FUNCTIONS ===================================================== */
/* ----------------------------------------------------------------------------------------------- */

public:

void print() const { _tree.print_tree(); } // DEBUGGING - REMOVE ?

/* ------------------------ construction: -------------------------------------------------------- */

map()	//: _compare(), _tree(_compare)
{}

explicit map(const Compare& comp, const Allocator& alloc = Allocator())
	: _compare(comp), _allocator(alloc)	//, _tree(_compare, alloc)
{}

// the value type to which InputIte point mus be ft::pair, compatible with map types.
template< class InputIt >
map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
	: _compare(comp), _allocator(alloc)	//, _tree(_compare, alloc)
{
	insert(first, last);

}

map(const map& other) {
	_tree = other._tree;
}

// /* ------------------------ destruction: --------------------------------------------------------- */

~map() {}

// /* ------------------------ assignment: --------------------------------------------------------- */

map& operator=( const map& other ) {
	_tree = other._tree;
	return (*this);
}

// /* ======================== ACCESSORS ============================================================ */

bool empty() const { return (_tree.empty()); }
size_type size() const { return(_tree.size()); }
size_type max_size() const { return(_tree.node_allocator().max_size()); }
allocator_type get_allocator() const { return(_allocator); }

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
		return (insert(ft::pair<Key, T>(key, T()))).first->second; // really ? okay...
	return (x->second);
}

iterator begin() { return (_tree.begin()); }
iterator end() { return (_tree.end()); }
const_iterator begin() const { return (_tree.begin()); }
const_iterator end() const { return (_tree.end()); }

// 	// reverse_iterator rbegin();
// 	// const_reverse_iterator rbegin() const;
// 	// reverse_iterator rend();
// 	// const_reverse_iterator rend() const;

/* ======================== MODIFIERS ============================================================ */

/* ------------------------ insertion: ----------------------------------------------------------- */

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
// todo properly
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

// /* ------------------------ deletion ------------------------------------------------------------- */

void clear() { if (!empty()) { _tree.clear(); } }

// Removes the element at pos.
void erase( iterator pos ) {
	// std::cout << "MAP delete pos" << std::endl;
	if (pos != end() && pos.get_tree_ite().get_base_ptr() != _tree._NIL)
		_tree.erase(pos.get_tree_ite());
}

// Removes the elements in the range [first; last), which must be a valid range in *this
void erase( iterator first, iterator last ) {
	// std::cout << "MAP range delete" << std::endl;
	_tree.erase(first.get_tree_ite(), last.get_tree_ite());
	// for (iterator cont_ite = first; cont_ite != last; cont_ite++) {
	// 	typename tree_type::node_pointer x = cont_ite.get_tree_ite().get_base_ptr();
	// 	if (cont_ite == end() || x == _tree._NIL ) {
	// 		std::cout << "breaaaaaaaakkkkkkKKKKKKKKKKKKKKKKk aaaaaaaa !!!!!! " << std::endl;
	// 		break ;
	// 	}
	// 	if (x != _tree._NIL)
	// 	_tree.erase(x);
	// }
}

// Removes the element (if one exists) with the key equivalent to key.
// Returns the number of elements removed (0 or 1).
size_type erase( const Key& key ) {
	// std::cout << "MAP delete key - count" << std::endl;
	iterator x = find(key);
	if (x != end() && x.get_tree_ite().get_base_ptr() != _tree._NIL) {
		_tree.erase(x.get_tree_ite());
		return (1);
	}
	return (0);
}

// /*  ----------------------- swap: ---------------------------------------------------------------- */

// 	void swap( map& other );

// /* ======================== LOOKUP =============================================================== */

// Returns the number of elements with key key, which is either 1 or 0 since this container
// does not allow duplicates.
size_type count( const Key& key ) const {
	if (find(key) != end())
		return (1);
	return (0);
}

// Finds an element with key equivalent to key.
// If no such element is found, or map is empty, end() is returned.
iterator find( const Key& key ) {
	if (!empty())
		for (iterator x = begin(); x != end(); x++) {
			if (x->first == key)//&& x != iterator(tree_iterator(_tree.NIL())))
				return (x) ;
		}
	return (end());
}

const_iterator find( const Key& key ) const {
	if (!empty())
		for (const_iterator x = begin(); x != end(); x++) {
			if (x->first == key)//&& x != iterator(tree_iterator(_tree.NIL())))
				return (x) ;
		}
	return (end());
}


// ? ? ? ? ? ? ? ?? ? ? ? ? 

	// Compares the keys to key. Returns:
	// ft::pair containing a pair of iterators defining the wanted range: the first pointing
	// to the first element that is not less than key and the second pointing to the
	// first element greater than key.
	// If there are no elements not less than key, past-the-end (see end()) iterator is returned as
	// the first element. Similarly if there are no elements greater than key, past-the-end
	// iterator is returned as the second element.
	ft::pair<iterator,iterator> equal_range( const Key& key ) {
		iterator x = find(key);
		if (x != end()) {
			iterator next = x;
			++next;
			return (ft::pair<iterator, iterator>(next, next));
		}
		return (ft::pair<iterator, iterator>(x, x)); // ??????
	}

	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
		const_iterator x = find(key);
		if (x != end()) {
			const_iterator next = x;
			++next;
			return (ft::pair<const_iterator, const_iterator>(next, next));
		}
		return (ft::pair<const_iterator, const_iterator>(x, x)); // ??????
	}

	iterator lower_bound( const Key& key ) {
		iterator x = find(key);
		if (x != begin()) {
			iterator next = x;
			--next;
			return (next);
		}
		return (x); // ??????
	}
	
	const_iterator lower_bound( const Key& key ) const {
		const_iterator x = find(key);
		if (x != begin()) {
			const_iterator next = x;
			--next;
			return (next);
		}
		return (x); // ??????
	}


	iterator upper_bound( const Key& key ) {
		iterator x = find(key);
		if (x != end()) {
			iterator next = x;
			++next;
			return (next);
		}
		return (x); // ??????
	}

	const_iterator upper_bound( const Key& key ) const {
		const_iterator x = find(key);
		if (x != end()) {
			const_iterator next = x;
			++next;
			return (next);
		}
		return (x); // ??????
	}

// /* ======================== OBSERVERS ============================================================ */

key_compare key_comp() const { return(_compare.get_key_compare()); }
value_compare value_comp() const { return(_compare); }

}; /* MAP */

/* - NON MEMBER FUNCTIONS ------------------------------------------------------------------------ */
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
/* - end MAP ------------------------------------------------------------------------------------- */

} /* NAMESPACE FT end ------------------------------------------------------*/
#endif // __FT_MAP_HPP_
