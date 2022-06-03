/* ************************************************************************ */
/*																			*/
/*								ft:: MAP									*/
/*																			*/
/* ************************************************************************ */
/* ------------------------------- CONTENTS ----------------------------------
--------------------------------------------------------------------------- */

#ifndef _FT_NAIVE_TREE_HPP_
# define _FT_NAIVE_TREE_HPP_

#define DBG_ME 1

namespace ft { /* NAMESPACE FT */

template < /* RB TREE */
	class Value,
	class Compare
> class rb_tree {

/* ======================== MEMBER TYPES & CLASSES ========================= */

public:

	typedef Value value_type;
	typedef Compare compare_type;

	enum color_type {red, black};

	class rb_tree_node {
	public:
		rb_tree_node* p;
		rb_tree_node* left;
		rb_tree_node* right;
		value_type value;
		color_type color;

		typedef void (rb_tree<Value, Compare>::rb_tree_node::*const_void_function_pointer) () const;

		// used only to initalize nil, all the other nodes will have empty 
		// links pointing to T.nil and not NULL
		rb_tree_node(): p(NULL), left(NULL), right(NULL), color(black) {
			#if DBG_ME
				std::cout << "\033[38;5;64m";
				// std::cout << __PRETTY_FUNCTION__ << "\n\t";
				std::cout << "NODE constructor\n\t";
				std::cout << "p:" << p << " l:" << left << " r" << right << " val:" \
				<< value << " col:" << color << "\033[0m" << std::endl;
			#endif
		}

		void print_value() const {
			std::cout << value << std::endl;
		}


	};

	typedef typename std::allocator<rb_tree_node>			node_allocator_type;
	typedef typename node_allocator_type::pointer			node_pointer;
	typedef typename node_allocator_type::size_type			size_type;
	typedef typename node_allocator_type::difference_type	difference_type;

	typedef typename std::allocator<Value>					value_allocator_type;
	typedef typename value_allocator_type::pointer			pointer;
	typedef typename value_allocator_type::reference		reference;
	typedef typename value_allocator_type::const_reference	const_reference;

/* ======================== ATTRIBUTES ==================================== */


private: // (protected ?)

	node_pointer _root; // make pvt with accessor

	static node_allocator_type _node_allocator;
	static value_allocator_type _value_allocator;

	static node_pointer _nil; // object or on heap?
	// static rb_tree_node _nil;

	node_pointer _leftmost; // for linear time begin()
	node_pointer _rightmost; // for linear time in set functions (?) & empty()


/* ------------------------------------------------------------------------ */
/* ======================== MEMBER FUNCTIONS ============================== */
/* ------------------------------------------------------------------------ */

public:

/* ------------------------ construction: --------------------------------- */

	rb_tree(): _root(_nil), _leftmost(_nil), _rightmost(_nil) {
		#if DBG_ME
			std::cout << "\033[38;5;29m";
			// std::cout << __PRETTY_FUNCTION__ << "\n\t";
			std::cout << "RB TREE constructor\n\t";
			std::cout << "\033[0m" << std::endl;
			std::cout << "test _nil: " << _nil->color << std::endl;
		#endif
	}

	rb_tree(const rb_tree& other);
	rb_tree& operator=(const rb_tree& other);

/* ------------------------ destruction: ---------------------------------- */
	
	~rb_tree() {
		// destroy & free all nodes (and values?)
		
		_node_allocator.destroy(_nil); //  nil is static. is this a double
		//free if i have more than one instance of tree?
		_node_allocator.deallocate(_nil, 1);
	}

/* ======================== ACCESSORS ===================================== */

	bool empty() const {
		return (_root == _nil);
	}

/* ======================== QUERIES ======================================= */

	node_pointer rb_max(node_pointer subtree_root) const ;
	node_pointer rb_min(node_pointer subtree_root) const ;

/* ======================== MODIFIERS ===================================== */

/* ------------------------ insertion: ------------------------------------ */

	void rb_insert(const_reference value) {
		node_pointer node = __allocate_rb_node(value);
		__rb_insert_node(node);
	}


/* ======================== INTERNAL FUNCTIONALITIES ====================== */
private:

// * * *

	node_pointer __allocate_rb_node(const_reference value) const {
		node_pointer node = _node_allocator.allocate(1);
		_node_allocator.construct(node, rb_tree_node());

		// node->value = _value_allocator.allocate(1);
		_value_allocator.construct(&node->value, value);
		// node->value = value;

		node->p = _nil;
		node->left = _nil;
		node->right = _nil;

		#if DBG_ME
			std::cout << "\033[38;5;64m";
			// std::cout << __PRETTY_FUNCTION__ << "\n\t";
			std::cout << "__allocate_rb_node | ";
			std::cout << "p:" << node->p << " l:" << node->left << " r" \
				<< node->right << " val:" << value << " col:" << node->color;
			std::cout << "\033[0m" << std::endl;
		#endif

		return (node);
	}

	// x is a preallocated node with links pointing to T.nil
	void __rb_insert_node(node_pointer x) {
		if (empty()) {
			_root = x;
			_leftmost = x;
			_rightmost = x;
			return ;
		}
	}

	/*
		Recursively reaches all nodes sorted by value and applies function f.
		-> need to overload if non const function.
	*/
	void __rb_tree_inorder_walk(node_pointer subtree_root,
		typename rb_tree_node::const_void_function_pointer f) const {
		if (subtree_root != _nil) {
			__rb_tree_inorder_walk(subtree_root->left, f);
			(subtree_root->*f)();
			__rb_tree_inorder_walk(subtree_root->right, f);
		}
	}

// * * *

public:

	void print_tree() const { // ?
		__rb_tree_inorder_walk(_root, &rb_tree_node::print_value);
	}

	static node_pointer nil() {
		node_pointer nil = _node_allocator.allocate(1);
		_node_allocator.construct(nil, rb_tree_node());
		return (nil);
	}

}; /* RB TREE */

/* - STATIC ATTRIBUTES ---------------------------------------------------- */

// static node allocator definition:
template <class Value, class Compare>
	typename rb_tree<Value, Compare>::node_allocator_type
	rb_tree<Value, Compare>::_node_allocator;

// static value allocator definition:
template <class Value, class Compare>
	typename rb_tree<Value, Compare>::value_allocator_type
	rb_tree<Value, Compare>::_value_allocator;

// initialization of static node_pointer nil:
template <class Value, class Compare>
	typename rb_tree<Value, Compare>::node_pointer
	rb_tree<Value, Compare>::_nil = rb_tree<Value, Compare>::nil();
// template <class Value, class Compare>
// 	typename rb_tree<Value, Compare>::rb_tree_node
// 	rb_tree<Value, Compare>::_nil; // calls dflt constructor rb_tree_node
// initialization of static node_pointer nil:
// template <class Value, class Compare>
// 	typename rb_tree<Value, Compare>::node_pointer
// 	rb_tree<Value, Compare>::nil
// 		= rb_tree<Value, Compare>::rb_tree_node::rb_tree_node();

/* - end TREE ------------------------------------------------------------- */

} /* NAMESPACE FT end ------------------------------------------------------*/

#endif // _FT_NAIVE_TREE_HPP_

#undef DBG_ME

