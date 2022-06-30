/* ************************************************************************ */
/*																			*/
/*								ft:: VECTOR									*/
/*																			*/
/* ************************************************************************ */

#ifndef __FT_VECTOR_HPP_
# define __FT_VECTOR_HPP_

// std::
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator> // for std::distance

// ft::
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include "utility.hpp"

#ifndef _THROWS_OUT_OF_RANGE
# define _THROWS_OUT_OF_RANGE throw(std::out_of_range)
#endif

#ifndef _THROWS_LENGTH_ERROR
# define _THROWS_LENGTH_ERROR throw(std::length_error)
#endif

#ifndef _NOEXCEPT
# define _NOEXCEPT throw()
#endif

#ifndef __IS_INTEGRAL
# define __IS_INTEGRAL ft::is_integral
#endif

/* ------------------------------------------------------------------------ */

namespace ft { /* NAMESPACE FT*/

template < /* VECTOR */
	typename T,
	class Alloc = std::allocator<T>
> class vector {

public:

/* ======================== TYPEDEFS ====================================== */

	typedef Alloc										allocator_type;
	typedef typename allocator_type::value_type			value_type;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;

	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

	typedef pointer											iterator;
	typedef const_pointer									const_iterator;
	typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

/* ======================== ATTRIBUTES ==================================== */

private: // protected: ?

	allocator_type	_allocator;
	iterator		_begin;
	iterator		_end_size;
	iterator		_end_capacity;

/* ------------------------------------------------------------------------ */
/* ======================== MEMBER FUNCTIONS ============================== */
/* ------------------------------------------------------------------------ */

public:

/* ------------------------ construction: --------------------------------- */

	vector() { __allocate_empty_vector(0); }

	explicit vector( const Alloc& alloc): _allocator(alloc) { __allocate_empty_vector(0); }
	
	explicit vector(size_type n, const T& value = T(), \
		const Alloc&alloc = allocator_type()): _allocator(alloc) {
		__allocate_empty_vector(n);
		for (size_type i = 0; i < n; i++)
			_allocator.construct(_begin + i, value);
		_end_size = _begin + n;
	}

	template< typename InputIter>
	vector(const InputIter first, const InputIter last, const Alloc&alloc = allocator_type(),
		typename enable_if<!__IS_INTEGRAL<InputIter>::value, bool>::type* = 0) : _allocator(alloc) {
		size_type range = std::distance(first, last);
		__allocate_empty_vector(range);
		for (InputIter it = first; it != last; it++) {
			_allocator.construct(_end_size++, *it);
		}
	}

	vector(const vector& other) {
		__allocate_empty_vector(other.size());
		for (const_iterator it = other.begin(); it != other.end(); it++) {
			_allocator.construct(_end_size++, *it);
		}
	}

/* ------------------------ destruction: ---------------------------------- */

	~vector() {
		clear();
		_allocator.deallocate(_begin, capacity());
		_end_capacity = NULL;
		_end_size = NULL;
		_begin = NULL;
	}

/* ------------------------ assignment: ---------------------------------- */

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

	template< typename InputIter >
	void assign(const InputIter first, const InputIter last,
		typename enable_if<!__IS_INTEGRAL<InputIter>::value, bool>::type* = 0) {
		clear();
		size_type range = std::distance(first, last);
		if (range > capacity())
			__resize_empty_vector(range);
		for (InputIter it = first; it != last; it++) {
			_allocator.construct(_end_size++, *it);
		}
	}

/* ======================== ACCESSORS ===================================== */

/* ------------------------ capacity: ------------------------------------- */

	size_type size() const { return (_end_size - _begin); }
	size_type capacity() const { return (_end_capacity - _begin); }
	size_type max_size() const { return (_allocator.max_size()); }
	bool empty() const { return (begin() == end()); }

	void reserve(size_type new_cap) _THROWS_LENGTH_ERROR {
		if (new_cap > max_size())
			throw std::length_error("Invalid capacity");
		if (new_cap > capacity()) {
			__resize_filled_vector(new_cap);
		}
	}

/* ------------------------ allocator: ------------------------------------ */

	allocator_type get_allocator() const { return (_allocator); }

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

	reference operator[]( size_type pos ) { return (*(_begin + pos)); }
	const_reference operator[]( size_type pos ) const { return (*(_begin + pos)); }
	reference front() { return (*begin()); }
	const_reference front() const { return (*begin()); }
	reference back() { return (*(end() - 1)); }
	const_reference back() const { return (*(end() - 1)); }
	T* data() { return (_begin); }
	const T* data() const { return (_begin); }

/* ------------------------ iterators: ------------------------------------ */

	iterator begin() { return iterator(_begin); }
	const_iterator begin() const { return const_iterator(_begin); }
	iterator end() {return (_end_size); }
	const_iterator end() const { return (_end_size); }
	reverse_iterator rbegin() {return (reverse_iterator(end())); }
	const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
	reverse_iterator rend() { return (reverse_iterator(begin())); }
	const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }
	
/* ======================== MODIFIERS ===================================== */

/* ------------------------ deletion -------------------------------------- */

	void clear() {
		for (size_type i = 0; i < size(); i++) {
			_allocator.destroy(_begin + i);
		}
		_end_size = _begin;
	}

	template< typename InputIter >
	InputIter erase(InputIter pos,
		typename enable_if<!__IS_INTEGRAL<InputIter>::value, bool>::type* = 0) {
		if (!__iterator_is_in_range(pos) || pos == _end_size)
			return (pos);
		InputIter curr = pos;
		_allocator.destroy(curr);
		while (curr + 1 != _end_size) {
			_allocator.construct(curr, *(curr + 1));
			_allocator.destroy(++curr);
		}
		_end_size = curr;
		return (pos);
	}

	template< typename InputIter >
	InputIter erase(InputIter first, InputIter last,
		typename enable_if<!__IS_INTEGRAL<InputIter>::value, bool>::type* = 0) {
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

	template< typename InputIter >
	InputIter insert(InputIter pos, const T& value,
		typename enable_if<!__IS_INTEGRAL<InputIter>::value, bool>::type* = 0) {
		
		if (pos == _end_size) {
			push_back(value);
			return (_end_size - 1);
		}
		size_type new_cap = capacity();
		if (size() == new_cap)
			new_cap = __calculate_new_capacity();
		pointer new_block = _allocator.allocate(new_cap);
		InputIter new_curr = new_block;
		InputIter curr = _begin;
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

	template< typename InputIter >
	void insert(InputIter pos, size_type n, const T& value,
		typename enable_if<!__IS_INTEGRAL<InputIter>::value, bool>::type* = 0) {
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

	template< typename IterVect, typename InterCont2 >
	void insert(IterVect pos, const InterCont2 first, const InterCont2 last,
		typename enable_if<!__IS_INTEGRAL<IterVect>::value, bool>::type* = 0,
		typename enable_if<!__IS_INTEGRAL<InterCont2>::value, bool>::type* = 0) {
		size_type range = std::distance(first, last);
		size_type new_cap = size() + range;
		if (new_cap < capacity())
			new_cap = capacity();
		if (pos == _end_size) {
			reserve(new_cap);
			for (InterCont2 set = first; set != last; set++)
				push_back(*set);
			return ;
		}
		pointer new_block = _allocator.allocate(new_cap);
		IterVect new_curr = new_block;
		IterVect curr = _begin;
		while (curr != _end_size) {
			if (curr == pos)
				for (InterCont2 set = first; set != last; set++)
					_allocator.construct(new_curr++, *set);
			_allocator.construct(new_curr++, *(curr++));
		}
		clear();
		_allocator.deallocate(_begin, capacity());
		_begin = new_block;
		_end_size = new_curr;
		_end_capacity = _begin + new_cap;
	}

/* ------------------------ resize: --------------------------------------- */

	void resize(size_type n, T value = T()) {
		if (n == size())
			return ;
		if (n > size()) {
			if (n > capacity())
				__resize_filled_vector(n);
			while (size() != n)
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

/* ======================== INTERNAL FUNCTIONALITIES ====================== */

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

	template< typename InputIter >
	bool __iterator_is_in_range(InputIter it,
		typename enable_if<!__IS_INTEGRAL<InputIter>::value, bool>::type* = 0) const {
		InputIter curr = _begin;
		while (curr != _end_size) {
			if (curr == it)
				return (true);
			curr++;
		}
		if (it == _end_size)
			return (true);
		return (false);
	}

}; /* vector */

/* - NON MEMBER FUNCTIONS ------------------------------------------------- */
/* operator==,!=,<,<=,>,>=,<=> */

template< class T, class Alloc >
bool operator==(const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	return (lhs.size() == rhs.size()
		&& ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template< class T, class Alloc >
bool operator!=(const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	return (!(lhs == rhs));
}

template< class T, class Alloc >
bool operator<(const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
		rhs.begin(), rhs.end()));
}

template< class T, class Alloc >
bool operator<=(const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
		rhs.begin(), rhs.end()) || lhs == rhs);
}

template< class T, class Alloc >
bool operator>(const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	return (ft::lexicographical_compare(rhs.begin(), rhs.end(),
		lhs.begin(), lhs.end()) && rhs != lhs);
}

template< class T, class Alloc >
bool operator>=(const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	return (ft::lexicographical_compare(rhs.begin(), rhs.end(),
		lhs.begin(), lhs.end()) || rhs == lhs);
}

/* - end VECTOR ----------------------------------------------------------- */
// #undef vector

} /* NAMESPACE FT end ------------------------------------------------------*/

#endif // __FT_VECTOR_HPP_
