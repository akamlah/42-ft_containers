/* ************************************************************************ */
/*																			*/
/*								ft:: VECTOR									*/
/*																			*/
/* ************************************************************************ */

// std::
#include <iostream>
#include <cassert>
#include <algorithm>

// ft::
#include "iterator.hpp"
#include "type_traits.hpp"

#ifndef _LIBFT_VECTOR_H_
# define _LIBFT_VECTOR_H_

#define PF __PRETTY_FUNCTION__
#ifndef DBG
# define DBG 0
#endif

#ifndef _THROWS_OUT_OF_RANGE
# define _THROWS_OUT_OF_RANGE throw(std::out_of_range)
#endif

#ifndef _THROWS_LENGTH_ERROR
# define _THROWS_LENGTH_ERROR throw(std::length_error)
#endif

#ifndef _NOEXCEPT
# define _NOEXCEPT throw()
#endif

// #ifndef vector
// #define vector vector
// #endif

/* ***************************************************************************

  +  +  +  +  +  +  +  +  +  --- CONTENTS ---  +  +  +  +  +  +  +  +  +  +  +

- TYPEDEFS -------------------------------------------------------------------

value_type              T
allocator_type          Allocator
size_type               Unsigned integer type (usually std::size_t)
difference_type	Signed  integer type (usually std::ptrdiff_t)
reference               value_type&
const_reference         const value_type&
pointer                 Allocator::pointer
const_pointer           Allocator::const_pointer
iterator                LegacyRandomAccessIterator and LegacyContiguousIterator
                        to value_type
const_iterator          LegacyRandomAccessIterator and LegacyContiguousIterator
                        to const value_type
reverse_iterator        std::reverse_iterator<iterator>
const_reverse_iterator  std::reverse_iterator<const_iterator>


- ATTRIBUTES -----------------------------------------------------------------

static allocator _allocator;
ierator start;
iterator end;

- MEMBER FUNCTIONS -----------------------------------------------------------

CONSTRUCTION
	vector();
	explicit vector( const Allocator& alloc );
	explicit vector( size_type n, const T& value = T(), \
		const Allocator& alloc = Allocator());
	template< class const_iterator >
		vector( const_iterator first, const_iterator last, \
			const Allocator& alloc = Allocator() );
	vector( const vector& other );

DESTRUCTION
	~vector();

ASSIGNMENTS
	vector& operator=( const vector& other );
	void assign( size_type n, const T& value );
	template< class const_iterator >
		void assign( const_iterator first, const_iterator last );

MODIFIERS
 -	deletion
		void clear();
		iterator erase( iterator pos );
		iterator erase( iterator first, iterator last );
		void pop_back();
 -	insertion:
		void push_back( const T& value );
		iterator insert( iterator pos, const T& value );
		void insert( iterator pos, size_type n, const T& value );
		template< class const_iterator >
			void insert( iterator pos, const_iterator first, const_iterator last );
 -	resize:
		void resize( size_type n, T value = T() );
 - 	swap:
		void swap( vector& other );

ACCESSORS
 -	allocator:
		allocator_type get_allocator() const;
 -	elements:
		reference at( size_type pos );
		const_reference at( size_type pos ) const;
		reference operator[]( size_type pos );
		const_reference operator[]( size_type pos ) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		T* data();
		const T* data() const;
 -	iterators:
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
 -	capacity:
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		void reserve( size_type new_cap ); // setter for cpacity
		size_type capacity() const;

- NON MEMBER FUNCTIONS -------------------------------------------------------

operator==,!=,<,<=,>,>=,<=>

	template< class T, class Alloc >
	bool operator==(const ft::vector<T, Alloc>& lhs, const std::vector<T>& rhs);
	template< class T, class Alloc >
	bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T>& rhs);
	template< class T, class Alloc >
	bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T>& rhs);
	template< class T, class Alloc >
	bool operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T>& rhs);
	template< class T, class Alloc >
	bool operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T>& rhs);
	template< class T, class Alloc >
	bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T>& rh );

std::swap specialization

	template< class T, class Alloc >
	void swap( std::vector<T,Alloc>& lhs,
			std::vector<T,Alloc>& rhs );

*************************************************************************** */

/*   +  +  +  +  +  +  +  --- IMPLEMENTATION ---  +  +  +  +  +  +  +  +  + */

namespace ft { /* NAMESPACE FT -------------------------------------------- */

template <typename T, class Alloc = std::allocator<T> >
class vector { /* VECTOR -------------------------------------------------- */

/* - TYPEDEFS ------------------------------------------------------------- */

public:

	typedef Alloc										allocator_type;
	typedef typename allocator_type::value_type			value_type;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef pointer										iterator;
	typedef const_pointer								const_iterator;
	typedef typename ft::reverse_iterator<iterator>	reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>
		const_reverse_iterator;

/* - ATTRIBUTES ----------------------------------------------------------- */

private: // protected: ?

	allocator_type	_allocator;
	iterator		_begin;
	iterator		_end_size;
	iterator		_end_capacity;

/* - INTERNAL FUNCTIONALITIES --------------------------------------------- */

private:

	void __resize_empty_vector(size_type new_cap) {
		pointer new_block = _allocator.allocate(new_cap);
		_allocator.deallocate(_begin, capacity());
		_begin = new_block;
		_end_size = _begin;
		_end_capacity = _begin + new_cap;
	}

	void __allocate_empty_vector(size_type new_cap) {
		_begin = _allocator.allocate(new_cap);
		_end_size = _begin;
		_end_capacity = _begin + new_cap;
	}

	size_type __calculate_new_capacity() const {
		size_type new_cap;
		size_type current_cap = capacity();
		if (empty())
			new_cap = 1;
		else if (current_cap < 128)
			new_cap = current_cap * 2;
		else
			new_cap = current_cap + current_cap / 2;
		return (new_cap);
	}

	void __resize_filled_vector(size_type new_cap) {
		pointer new_block = _allocator.allocate(new_cap);
		size_type i;
		for (i = 0; i < size(); i++) {
			_allocator.construct(new_block + i, _begin[i]);
			_allocator.destroy(_begin + i);
		}
		_allocator.deallocate(_begin, capacity());
		_begin = new_block;
		_end_size = _begin + i;
		_end_capacity = _begin + new_cap;
	}

	bool __iterator_is_in_range(iterator it) const {
		iterator curr = _begin;
		while (curr != _end_size) {
			if (curr == it)
				return (true);
			curr++;
		}
		if (it == _end_size)
			return (true);
		return (false);
	}

/* ------------------------------------------------------------------------ */
/* - CONSTRUCTION --------------------------------------------------------- */

public:

	vector() {
		__allocate_empty_vector(0);
	}

	explicit vector( const Alloc& alloc): _allocator(alloc) {
		// assert(is_same< typename allocator_type::value_type, value_type >::value);
		__allocate_empty_vector(0);
	}
	
	explicit vector(size_type n, const T& value = T(), \
		const Alloc&alloc = allocator_type()): _allocator(alloc) {
		__allocate_empty_vector(n);
		for (size_type i = 0; i < n; i++)
			_allocator.construct(_begin + i, value);
		_end_size = _begin + n;
	}

	// template< typeneme _InputIter >
	vector(const_iterator first, const_iterator last, \
		const Alloc&alloc = allocator_type()): _allocator(alloc) {
		// + enable if correct iter
		size_type range = static_cast<size_type>(last - first);
		__allocate_empty_vector(range);
		for (const_iterator it = first; it != last; it++) {
			_allocator.construct(_end_size++, *it);
		}
	}

	vector(const vector& other) {
		__allocate_empty_vector(other.size());
		for (const_iterator it = other.begin(); it != other.end(); it++) {
			_allocator.construct(_end_size++, *it);
		}
	}

/* - DESTRUCTION ---------------------------------------------------------- */

	~vector() {
		clear();
		_allocator.deallocate(_begin, capacity());
		_end_capacity = NULL;
		_end_size = NULL;
		_begin = NULL;
	}

/* ------------------------------------------------------------------------ */
/* - MEMBER FUNCTIONS ----------------------------------------------------- */

public:

/* ASSIGNMENTS */

	vector& operator=(const vector& other) {
		clear();
		if (other.capacity() != capacity())
			__resize_empty_vector(other.capacity());
		for (const_iterator it = other.begin(); it != other.end(); it++) {
			_allocator.construct(_end_size++, *it);
		}
		return (*this);
	}

	void assign(size_type n, const T& value) {
		clear();
		if (n > capacity())
			__resize_empty_vector(n);
		for (size_type i = 0; i < n; i++)
			_allocator.construct(_end_size++, value);
	}

	void assign(const_iterator first, const_iterator last) {
		clear();
		size_type range = static_cast<size_type>(last - first);
		if (range > capacity())
			__resize_empty_vector(range);
		for (const_iterator it = first; it != last; it++) {
			_allocator.construct(_end_size++, *it);
		}
	}

/* MODIFIERS */

/* ------------------------ deletion -------------------------------------- */

	void clear() {
		for (size_type i = 0; i < size(); i++) {
			_allocator.destroy(_begin + i);
		}
		_end_size = _begin;
	}

	iterator erase(iterator pos) {
		if (!__iterator_is_in_range(pos) || pos == _end_size)
			return (pos);
		iterator curr = pos;
		_allocator.destroy(curr);
		while (curr + 1 != _end_size) {
			_allocator.construct(curr, *(curr + 1));
			_allocator.destroy(++curr);
		}
		_end_size = curr;
		return (pos);
	}

	iterator erase(iterator first, iterator last) {
		iterator curr = first;
		iterator remaining = last;
		bool destroy_curr = true;
		if (!__iterator_is_in_range(first) && __iterator_is_in_range(last))
			curr = _begin;
		if (curr == last)
			return (curr);
		while (remaining != _end_size) {
			if (destroy_curr == true)
				_allocator.destroy(curr);
			_allocator.construct(curr++, *remaining);
			_allocator.destroy(remaining++);
			if (curr == last)
				destroy_curr = false;
		}
		_end_size = curr;
		if (destroy_curr == true) {
			while (curr != remaining)
				_allocator.destroy(curr++);
		}
		return (first);
	}

	void pop_back() {
		if (empty())
			return ;
		_allocator.destroy(--_end_size);
	}

/* ------------------------ insertion: ------------------------------------ */

	void push_back(const T& value) {
		if (capacity() <= size()) {
			__resize_filled_vector(__calculate_new_capacity());
		}
		_allocator.construct(_end_size, value);
		++_end_size;
	}
	
	iterator insert(iterator pos, const T& value) {
		if (pos == _end_size) {
			push_back(value);
			return (_end_size - 1);
		}
		size_type new_cap = capacity();
		if (size() == new_cap)
			new_cap = __calculate_new_capacity();
		pointer new_block = _allocator.allocate(new_cap);
		iterator new_curr = new_block;
		iterator curr = _begin;
		while (curr != _end_size) {
			if (curr == pos) {
				pos = new_curr;
				_allocator.construct(new_curr++, value);
			}
			_allocator.construct(new_curr++, *(curr++));
		}
		clear();
		_allocator.deallocate(_begin, capacity());
		_begin = new_block;
		_end_size = new_curr;
		_end_capacity = _begin + new_cap;
		return (pos);
	}

	void insert(iterator pos, size_type n, const T& value) {
		size_type new_cap = size() + n;
		if (new_cap < capacity())
			new_cap = capacity();
		if (pos == _end_size) {
			reserve(new_cap);
			for (size_type cpys = 0; cpys < n; cpys++)
				push_back(value);
			return ;
		}
		pointer new_block = _allocator.allocate(new_cap);
		iterator new_curr = new_block;
		iterator curr = _begin;
		while (curr != _end_size) {
			if (curr == pos)
				for (size_type cpys = 0; cpys < n; cpys++)
						_allocator.construct(new_curr++, value);
			_allocator.construct(new_curr++, *(curr++));
		}
		clear();
		_allocator.deallocate(_begin, capacity());
		_begin = new_block;
		_end_size = new_curr;
		_end_capacity = _begin + new_cap;
	}

	void insert(iterator pos, const_iterator first, const_iterator last) {
		size_type range = static_cast<size_type>(last - first);
		size_type new_cap = size() + range;
		if (new_cap < capacity())
			new_cap = capacity();
		if (pos == _end_size) {
			reserve(new_cap);
			for (const_iterator set = first; set != last; set++)
				push_back(*set);
			return ;
		}
		pointer new_block = _allocator.allocate(new_cap);
		iterator new_curr = new_block;
		iterator curr = _begin;
		while (curr != _end_size) {
			if (curr == pos)
				for (const_iterator set = first; set != last; set++)
					_allocator.construct(new_curr++, *set);
			_allocator.construct(new_curr++, *(curr++));
		}
		clear();
		_allocator.deallocate(_begin, capacity());
		_begin = new_block;
		_end_size = new_curr;
		_end_capacity = _begin + new_cap;
	}
	// ^^ could have done these with <algorithm> copy & copy_backward

/* ------------------------ resize: --------------------------------------- */

	void resize(size_type n, T value = T()) {
		if (n == size())
			return ;
		if (n > size()) {
			if (n > capacity())
				__resize_filled_vector(n);
			while (size() != capacity())
				_allocator.construct(_end_size++, value);
			return ;
		}
		for (size_type i = size(); i > n; i--)
			_allocator.destroy(--_end_size);
	}
 
/*  ----------------------- swap: ----------------------------------------- */

	void swap(vector& other) {
		std::swap(_end_size, other._end_size);
		std::swap(_end_capacity, other._end_capacity);
		std::swap(_begin, other._begin);
		std::swap(_allocator, other._allocator);
	}


/* ACCESSORS */

/* ------------------------ capacity: ------------------------------------- */

	bool empty() const {
		return (begin() == end());
	}

	size_type size() const {
		return (_end_size - _begin);
	}

	size_type max_size() const {
		return (_allocator.max_size());
	}

	void reserve(size_type new_cap) _THROWS_LENGTH_ERROR {
		if (new_cap > max_size())
			throw std::length_error("Invalid capacity");
		if (new_cap > capacity()) {
			__resize_filled_vector(new_cap);
		}
	}

	size_type capacity() const {
		return (_end_capacity - _begin);
	}

/* ------------------------ allocator: ------------------------------------ */

	allocator_type get_allocator() const {
		return (_allocator);
	}

/* ------------------------ elements: ------------------------------------- */

	reference at( size_type pos ) _THROWS_OUT_OF_RANGE {
		if (pos < 0 || pos >= size())
			std::__throw_out_of_range("index out of vector range");
		return (*(_begin + pos));
	}

	const_reference at( size_type pos ) const _THROWS_OUT_OF_RANGE {
		if (pos < 0 || pos >= size())
			std::__throw_out_of_range("index out of vector range");
		return (*(_begin + pos));
	}

	reference operator[]( size_type pos ) _NOEXCEPT {
		return (*(_begin + pos));
	}

	const_reference operator[]( size_type pos ) const _NOEXCEPT {
		return (*(_begin + pos));
	}

	reference front() _NOEXCEPT {
		return (*begin());
	}

	const_reference front() const _NOEXCEPT {
		return (*begin());
	}

	reference back() _NOEXCEPT {
		return (*(end() - 1));
	}
	
	const_reference back() const _NOEXCEPT {
		return (*(end() - 1));
	}

	T* data() {
		return (_begin);
	}

	const T* data() const {
		return (_begin);
	}

/* ------------------------ iterators: ------------------------------------ */

	iterator begin() _NOEXCEPT {
		return (_begin);
	}

	const_iterator begin() const _NOEXCEPT {
		return (_begin);
	}
	
	iterator end() _NOEXCEPT {
		return (_end_size);
	}

	const_iterator end() const _NOEXCEPT {
		return (_end_size);
	}

	reverse_iterator rbegin();

	const_reverse_iterator rbegin() const;

	reverse_iterator rend();

	const_reverse_iterator rend() const;


}; /* class VECTOR FT ------------------------------------------------------*/

/* - NON MEMBER FUNCTIONS ------------------------------------------------- */

/* operator==,!=,<,<=,>,>=,<=> */

	template< class T, class Alloc >
	bool operator==(const ft::vector<T, Alloc>& lhs,
		const ft::vector<T, Alloc>& rhs) {
		return (lhs.size() == rhs.size()
			&& std::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class T, class Alloc >
	bool operator!=(const ft::vector<T, Alloc>& lhs,
		const ft::vector<T, Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template< class T, class Alloc >
	bool operator<(const ft::vector<T, Alloc>& lhs,
		const ft::vector<T, Alloc>& rhs) {
		return (std::lexicographical_compare(lhs.begin(), lhs.end(),
			rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc >
	bool operator<=(const ft::vector<T, Alloc>& lhs,
		const ft::vector<T, Alloc>& rhs) {
		return (std::lexicographical_compare(lhs.begin(), lhs.end(),
			rhs.begin(), rhs.end()) || lhs == rhs);
	}

	template< class T, class Alloc >
	bool operator>(const ft::vector<T, Alloc>& lhs,
		const ft::vector<T, Alloc>& rhs) {
		return (std::lexicographical_compare(rhs.begin(), rhs.end(),
			lhs.begin(), lhs.end()) && rhs != lhs);
	}

	template< class T, class Alloc >
	bool operator>=(const ft::vector<T, Alloc>& lhs,
		const ft::vector<T, Alloc>& rhs) {
		return (std::lexicographical_compare(rhs.begin(), rhs.end(),
			lhs.begin(), lhs.end()) || rhs == lhs);
	}

// #undef vector
} /* NAMESPACE FT end ------------------------------------------------------*/

#endif
/* - end VECTOR ----------------------------------------------------------- */
