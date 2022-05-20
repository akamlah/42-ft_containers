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

/* debug */
#define PF __PRETTY_FUNCTION__
#ifndef DBG
#	define DBG 0
#endif

/*
	OPERATIONS:

	push_back(elem)		Appends a copy of elem at the end
	pop_back()			Removes the last element (does not return it)
	insert(pos,elem)	Inserts a copy of elem before iterator position 
						pos and returns the position of the new element
	insert(pos,n,elem)	Inserts n copies of elem before iterator position
						pos and returns the position of the first new element
						(or pos if there is no new element)
	insert(pos,beg,end)	Inserts a copy of all elements of the range [beg,end)
						before iterator position pos and returns the position of
						the first new element (or pos if there is no new element)
	erase(pos)			Removes the element at iterator position pos and returns
						the position of the next element
	erase(beg,end)		Removes all elements of the range [beg,end) and returns
						the position of the next element
	resize(num)			Changes the number of elements to num (if size() grows
						new elements are created by their default constructor)
	resize(num,elem)	Changes the number of elements to num (if size() grows
						new elements are copies of elem)
	clear()				Removes all elements (empties the container)

*/
namespace ft { /* NAMESPACE FT -------------------------------------------- */

	template<typename T>
	class allocator: public std::allocator<T> {
		public:
	};
template <typename T>
class vector { /* VECTOR -------------------------------------------------- */

public: /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
	/*  - * -*-* type definintions *-*- * -  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~   */

	typedef ft::allocator<T>							allocator_type;
	typedef typename allocator_type::value_type			value_type;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;

	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::const_reference	const_reference;

	typedef pointer			iterator;
	typedef const_pointer	const_iterator;
	// + reverse & const reverse

private: /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	/*  - * -*-* private attributes *-*- * -  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  */

	size_type			_size;
	size_type			_capacity;
	pointer				_data;

protected: /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	/*  - * -*-* protected attributes *-*- * -  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~*/

	allocator_type		_allocator;
	iterator			_begin;
	iterator			_end;
	iterator			_storage_end;

public: /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
	/*  - * -*-* construction *-*- * -   ~  ~ ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  */

	vector(): _size(0), _capacity(2) { __dbgLOG(PF, GREEN_2);
		_data = _allocator.allocate(_capacity);
		_begin = _data;
		_end = _data + _size;
		_storage_end = _data + (_capacity - 1);
	}

	~vector() {
		__dbgLOG(PF, BLUE);
		clear();
		_allocator.deallocate(_data, _capacity);
	}

	/*  - * -*-* accessors *-*- * -   ~  ~  ~ ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  */

	size_type		size() const { return (_size); }
	size_type 		capacity() const { return (_capacity); }
	size_type 		max_size() const { return (_allocator.max_size()); }
	bool 			empty() const { return (_size == 0); }// or begin() == end() }
	iterator 		begin() { __dbgLOG(PF, SL_YELLOW);  return (_begin); }
	const_iterator	begin() const { __dbgLOG(PF, SL_YELLOW);  return (_begin); }
	iterator 		end() { __dbgLOG(PF, SL_YELLOW);  return (_end); }
	const_iterator	end() const { __dbgLOG(PF, SL_YELLOW);  return (_end); }
	allocator_type	get_allocator() const { return (_allocator); }
	pointer			data() { return (_data); }
	const_pointer	data() const { return (_data); }
	reference		front() { return (*begin()); }
	const_reference	front() const { return (*begin()); }
	reference		back() { return (*(end() - 1)); }
	const_reference back() const { return (*(end() - 1)); }

	/*  - * -*-* insert elements *-*- * -   ~ ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  */


	void push_back(const_reference value) { __dbgLOG(PF, L_BLUE);
		if (_size >= _capacity) {
			if (_size < 128)
				__resize_capacity(_capacity * 2);
			else
				__resize_capacity(_capacity + _capacity / 2);
			_begin = _data;
		}
		_allocator.construct(_data + _size, value);
		_size++;
		_end = _data + _size;
	}

	iterator insert(iterator pos, const_reference value) {
		if (_size >= _capacity) {
			if (_size < 128)
				__resize_capacity(_capacity * 2);
			else
				__resize_capacity(_capacity + _capacity / 2);
			_begin = _data;
		}
		
	}

	/*  - * -*-* erase elements *-*- * -   ~ ~  ~  ~  ~  ~  ~  ~  ~  ~  ~   */
	/*
		Removes the last element of the container. Undefined behavior on empty
		vector. Invalidates all iteators, pointers, references to the element.
	*/
	void pop_back() {
		if (_size > 0) {
			_size--;
			_allocator.destroy(_data + _size);
		}
		_end = _data + _size;
	}
	/*
		Deconstructs all nodes in the vector and sets size to zero.
		The memory allocated stays the same, thus capacity is unchanged.
		Invalidates all iteators, pointers, references.
	*/
	void clear() {
		for (size_type i = 0; i < _size; i++) {
			_allocator.destroy(_data + i);
		}
		_size = 0;
	}

	/*  - * -*-* storage  *-*- * -   ~  ~  ~ ~  ~  ~  ~  ~  ~  ~  ~  ~  ~   */

	void reserve(size_type new_cap) {
		if (new_cap > _capacity) {
			__resize_capacity(new_cap);
			_begin = _data;
			_end = _data + _size;
		}
	}

	void swap(vector<T>& other) {
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
		std::swap(_data, other._data);
		std::swap(_begin, other._begin);
		std::swap(_end, other._end);
		std::swap(_storage_end, other._storage_end);
	}

/*
	Resizes the container to contain count elements.
	If the current size is greater than count, the container
	is reduced to its first count elements.
	If the current size is less than count:
	 1) additional default-inserted elements are appended
	 2) additional copies of value are appended.
	Vector capacity is never reduced when resizing to smaller size.
*/
	void resize( size_type count, T value = T() ) { // throws!
		if (count == _size)
			return ;
		if (count < _size) {
			for (size_type i = count; i < _size; i++)
				_allocator.destroy(_data + i);
			_size = count;
			_end = _data + _size;
			return ;
		}
		if (count > _capacity)
			__resize_capacity(count);
		while (_size < count)
			_allocator.construct(_data + _size++, value);
   		_begin = _data;
		_end = _data + _size; // apparently gets invalidated in std::vector
	}
	// use range insert/ delete maybe

	/*  - * -*-* operators *-*- * -   ~  ~  ~ ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  */

	// vector<T>& operator=(const ft::vector<T>& other) {} // return const?


	// throw out of range in std!

	reference operator[](const unsigned int i) { __dbgLOG(PF, L_BLUE_GREEN);
		if (i >= _size)
			assert(i <= _size);
		return (*(_begin + i));
	}

	const_reference operator[](const unsigned int i) const { __dbgLOG(PF, L_BLUE_GREEN);
		if (i >= _size)
			assert(i <= _size);
		return (*(_begin + i));
	}

private: /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	/*  - * -*-* private functions *-*- * -  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~   */

	/*
		copies the data to a larger memory slot and destroys the previous
		objects. Updates capacity and _storage_end pointer.
		Does not change anything in _size and related parameters, as
		begin and end pointers.
	*/
	void __resize_capacity(size_type new_cap) {
		pointer newSlot = _allocator.allocate(new_cap, _data);
		for (size_type i = 0; i < _size; i++) {
			_allocator.construct(newSlot + i, _data[i]);
			_allocator.destroy(_data + i);
		}
		_allocator.deallocate(_data, _capacity);
		_data = newSlot;
		_capacity = new_cap;
		_storage_end = _data + _capacity;
	}

	/*  - * -*-* debug *-*- * -   ~  ~  ~  ~ ~  ~  ~  ~  ~  ~  ~  ~  ~  ~   */

	void __dbgLOG(std::string msg, std::string color) const {
		#if (!STD && DBG)
		std::cout << color << msg << NC << std::endl;
		#endif
		(void)msg;
		(void)color;
	}

	public:

	void peek() const {
		std::cout << "[ PEEK ]" << " ";
		std::cout << "S " << _size << ", C " << _capacity << std::endl;
		for (size_type i = 0; i < _size; i++) {
			if (i < 10 || i > _size - 3)
				std::cout << i << ": " << _data[i] << " " << &_data[i] << std::endl;
		}
		return ;
	}

}; /* VECTOR end ---------------------------------------------------------- */

	template<typename T>
	void swap(T &a, T &b) {
		T tmp = a;
		a = b;
		b = tmp;
	}

} /* NAMESPACE FT end ------------------------------------------------------*/
