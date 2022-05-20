/* ************************************************************************ */
/*																			*/
/*								ft:: VECTOR									*/
/*																			*/
/* ************************************************************************ */

#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include "ANSIpalette.h"

#define PF __PRETTY_FUNCTION__
#ifndef DBG
# define DBG 0
#endif

#ifndef _THROWS_OUT_OF_RANGE
# define _THROWS_OUT_OF_RANGE throw(std::out_of_range)
#endif

#ifndef _NOEXCEPT
# define _NOEXCEPT throw()
#endif

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
		// explicit vector( const Allocator& alloc );
		// explicit vector( size_type count, const T& value = T(), \
			const Allocator& alloc = Allocator());
	template< class InputIt >
		vector( InputIt first, InputIt last, \
			const Allocator& alloc = Allocator() );
	vector( const vector& other );

DESTRUCTION
	~vector();

ASSIGNMENTS
	vector& operator=( const vector& other );
	void assign( size_type count, const T& value );
	template< class InputIt >
		void assign( InputIt first, InputIt last );

ACCESSORS
 -	allocator:
		allocator_type get_allocator() const;
 -	elements:
		reference at( size_type pos );
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

MODIFIERS
 -	deletion
		void clear();
		iterator erase( iterator pos );
		iterator erase( iterator first, iterator last );
		void pop_back();
 -	insertion:
		void push_back( const T& value );
		iterator insert( iterator pos, const T& value );
		void insert( iterator pos, size_type count, const T& value );
		template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last );
 -	resize:
		void resize( size_type count, T value = T() );
 - 	swap:
		void swap( vector& other );


- NON MEMBER FUNCTIONS -------------------------------------------------------

operator==,!=,<,<=,>,>=,<=>

	template< class T, class Alloc >
	bool operator==( const std::vector<T,Alloc>& lhs,
					const std::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator!=( const std::vector<T,Alloc>& lhs,
					const std::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator<( const std::vector<T,Alloc>& lhs,
					const std::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator<=( const std::vector<T,Alloc>& lhs,
					const std::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator>( const std::vector<T,Alloc>& lhs,
					const std::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator>=( const std::vector<T,Alloc>& lhs,
					const std::vector<T,Alloc>& rhs );

std::swap specialization

	template< class T, class Alloc >
	void swap( std::vector<T,Alloc>& lhs,
			std::vector<T,Alloc>& rhs );

*************************************************************************** */



/*   +  +  +  +  +  +  +  --- IMPLEMENTATION ---  +  +  +  +  +  +  +  +  + */

namespace ft { /* NAMESPACE FT -------------------------------------------- */

	template<typename T>
	class allocator: public std::allocator<T> {
		public:
	};

template <typename T>
class vector { /* VECTOR -------------------------------------------------- */

/* - TYPEDEFS ------------------------------------------------------------- */

public:

	typedef ft::allocator<T>							allocator_type;
	typedef typename allocator_type::value_type			value_type;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef pointer										iterator;
	typedef const_pointer								const_iterator;

	// todo (std -> ft):
	typedef typename std::reverse_iterator<iterator>	reverse_iterator;
	typedef typename std::reverse_iterator<const_iterator>	const_reverse_iterator;


/* - ATTRIBUTES ----------------------------------------------------------- */

private: // protected: ?

	allocator_type	_allocator;
	iterator		_begin;
	iterator		_end_size;
	iterator		_end_capacity;
	pointer			_data;

/* - CONSTRUCTION --------------------------------------------------------- */
public:

	vector() _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value) {
		_build_empty_vector();
	}

	// explicit vector( const Allocator& alloc );
	// explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator());
	template< class InputIt >
	vector( InputIt first, InputIt last); //, const Allocator& alloc = Allocator() );

	vector( const vector& other );

/* - DESTRUCTION ---------------------------------------------------------- */

	~vector() {
		clear();
		_allocator.deallocate(_data, capacity());
	}

/* - INTERNAL FUNCTIONALITIES --------------------------------------------- */
private:

	void _build_empty_vector() {
		_data = _allocator.allocate(0);
		_begin = _data; // actually segfaults in std if called at beginning
		_end_size = _begin;
		_end_capacity = _begin;
	}

	void _transfer_content(pointer new_block) {
		size_type i;
		for (i = 0; i < size(); i++) {
			_allocator.construct(new_block + i, _data[i]);
			_allocator.destroy(_data + i);
		}
		_allocator.deallocate(_data, capacity());
		_data = new_block;
		_begin = _data;
		_end_size = _data + i;
	}

	void _increase_capacity() {
		size_type new_cap;
		size_type current_cap = capacity();
		if (empty())
			new_cap = 2;
		else if (current_cap < 128)
			new_cap = current_cap * 2;
		else
			new_cap = current_cap + current_cap / 2;
		pointer new_block = _allocator.allocate(new_cap);
		_transfer_content(new_block);
		_end_capacity = _data + new_cap;
	}

/* - MEMBER FUNCTIONS ----------------------------------------------------- */
public:

/* ASSIGNMENTS */

	vector& operator=( const vector& other );
	void assign( size_type count, const T& value );
	template< class InputIt >
		void assign( InputIt first, InputIt last );

/* ACCESSORS */

//  -	allocator:

	allocator_type get_allocator() const {
		return (_allocator);
	}

//  -	elements:

	reference at( size_type pos ) _THROWS_OUT_OF_RANGE {
		if (pos < 0 || pos >= size())
			std::__throw_out_of_range("index out of vector range");
	}
	reference operator[]( size_type pos ) _NOEXCEPT {
		return (*(_data + pos));
	}
	const_reference operator[]( size_type pos ) const _NOEXCEPT {
		return (*(_data + pos));
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
		return (_data);
	}
	const T* data() const {
		return (_data);
	}

//  -	iterators:

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

//  -	capacity:

	bool empty() const {
		return (begin() == end());
	}
	size_type size() const {
		return (_end_size - _begin);
	}
	size_type max_size() const {
		return (_allocator.max_size());
	}
	void reserve( size_type new_cap );
	size_type capacity() const {
		return (_end_capacity - _begin);
	}

/* MODIFIERS */

//  -	deletion

	void clear() {
		for (size_type i = 0; i < size(); i++) {
			_allocator.destroy(_data + i);
		}
		_end_size = _data;
	}

	iterator erase( iterator pos );
	iterator erase( iterator first, iterator last );
	void pop_back();

//  -	insertion:

	void push_back( const T& value ) {
		if (capacity() <= size())
			_increase_capacity();
		_allocator.construct(_end_size, value);
		_end_size++;
	}
	iterator insert( iterator pos, const T& value );
	void insert( iterator pos, size_type count, const T& value );
	template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last );

//  -	resize:

	void resize( size_type count, T value = T() );

//  - 	swap:

	void swap( vector& other );

};  /* VECTOR FT end -------------------------------------------------------*/


} /* NAMESPACE FT end ------------------------------------------------------*/
