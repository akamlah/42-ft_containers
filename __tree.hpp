/* ************************************************************************ */
/*																			*/
/*								ft:: MAP									*/
/*																			*/
/* ************************************************************************ */
/* ------------------------------- CONTENTS ----------------------------------
--------------------------------------------------------------------------- */

#ifndef _FT_TREE_HPP_
# define _FT_TREE_HPP_

namespace ft { /* NAMESPACE FT */







/* ------------------------------------------------------------------------ */
// ITERATORS
/* ------------------------------------------------------------------------ */
// template <class _Tp>
// struct _tree_key_value_types { }; // ?
// template <class _Tp, class NodePtr, class _DiffType>
// class _LIBCPP_TEMPLATE_VIS _tree_iterator
// { };
// template <class _Tp, class NodePtr, class _DiffType>
// class _LIBCPP_TEMPLATE_VIS _tree_const_iterator
// { };








/* ------------------------------------------------------------------------ */
// NODES
/* ------------------------------------------------------------------------ */

template <class _Tp, class _Allocator = std::allocator<_Tp> >
class Node {

public:

	typedef _Allocator allocator_type;
	typedef typename allocator_type::value_type value_type;
	typedef Node* node_pointer;
	typedef Node& node_reference;
	typedef bool color_type;

private:

	node_pointer		_p;
	node_pointer		_right;
	node_pointer		_left;
	value_type			_key;
	color_type			_color;

public:

	Node(): _p(NULL), _right(NULL), _left(NULL), _key(), _color(red()) {}

	Node(node_pointer p, node_pointer right, node_pointer left, \
		value_type key, color_type color) : _p(p), _right(right), 
		_left(left), _key(key), _color(color) {}

	Node(const Node& other) : _p(other._p), _right(other._right),
		_left(other._left), _key(other._key), _color(other._color) {}

	~Node() {};

	static color_type red() { return 1; }
	static color_type black() { return 0; } // provisory

// member functions:

// ROTATIONS:
	// right rotate node:
	// 	lc's parent becomes old node's parent
	// 	lc becomes new parent
	// 	lc'c lc becomes node's rc
	// left rotate node -> reverse => test thees by trying to see if lrot + rrot == 0 rot
}; // Node






/* ------------------------------------------------------------------------ */
// TREE
/* ------------------------------------------------------------------------ */
/*
	red-black binary tree datastructure
	properties:
	0. binary-search-tree property (subtreeL <= x <= subtreeR)
	1-4 rb tree
	+ object node
*/
template <class _Tp, class _Allocator = std::allocator<_Tp> > // + class _Compare
class _tree
{

/* ======================== TYPEDEFS ====================================== */

	typedef _Allocator 									allocator_type;
	typedef typename allocator_type::value_type			value_type;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef Node<_Tp, allocator_type> node_type;
	typedef typename node_type::node_pointer node_pointer; // ? 
	// + iterators

/* ======================== ATTRIBUTES ==================================== */

private:

	node_pointer _root;
	node_pointer _nil;
	allocator_type _allocator;

public:

/* ------------------------------------------------------------------------ */
/* ======================== MEMBER FUNCTIONS ============================== */
/* ------------------------------------------------------------------------ */

	_tree() {
		_allocator
		_nil = new node_type();
	}
// node_pointer _newnode();

// maintainance:
// insert(node)
// delete(node)
// transplant(node1, node2)

// queries:
// min(subtree_rootnode)
// max(subtree_rootnode)
// successor(node)
// predecessor(node)
// search(subtree_rootnode, key)

/* ------------------------ construction: --------------------------------- */

/* ------------------------ destruction: ---------------------------------- */

/* ------------------------ assignment: ---------------------------------- */

/* ======================== ACCESSORS ===================================== */

/* ------------------------ allocator: ------------------------------------ */

/* ------------------------ elements: ------------------------------------- */

/* ------------------------ iterators: ------------------------------------ */

/* ------------------------ capacity: ------------------------------------- */

/* ======================== MODIFIERS ===================================== */

/* ------------------------ insertion: ------------------------------------ */

/* ------------------------ deletion -------------------------------------- */

/*  ----------------------- swap: ----------------------------------------- */

/* ======================== LOOKUP ======================================== */

/* ======================== OBSERVERS ===================================== */

/* ======================== INTERNAL FUNCTIONALITIES ====================== */

}; /* _TREE */

/* - NON MEMBER FUNCTIONS ------------------------------------------------- */
/* operator==,!=,<,<=,>,>=,<=> */

/* - end TREE ------------------------------------------------------------- */

} /* NAMESPACE FT end ------------------------------------------------------*/

#endif // _FT_TREE_HPP_

#undef RED
#undef BLACK
