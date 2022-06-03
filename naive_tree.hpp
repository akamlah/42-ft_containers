/* ************************************************************************ */
/*																			*/
/*								ft:: MAP									*/
/*																			*/
/* ************************************************************************ */
/* ------------------------------- CONTENTS ----------------------------------
--------------------------------------------------------------------------- */

#ifndef _FT_NAIVE_TREE_HPP_
# define _FT_NAIVE_TREE_HPP_

#define DBG_ME 0

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

		node->p = NULL;
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

	// todo : leftmost/rightmost maintainance
	void __rb_left_rotate(node_pointer x) {
		if (!x || x == _nil) {
			std::cout << "RETURN Lrot" << std::endl;
			return ; // ?
		}
		node_pointer y = x->right;
		x->right = y->left;
		if (y->left != _nil)
			y->left-> p = x;
		y->p = x->p;
		if (x->p == _nil)
			_root = y;
		else if (x->p == x->p->left)
			x->p->left = y;
		else
			x->p->right = y;
		y->left = x;
		x->p = y;
	}

	// todo : leftmost/rightmost maintainance
	void __rb_right_rotate(node_pointer x) {
		if (!x || x == _nil) {
			std::cout << "RETURN Rrot" << std::endl;
			return ; // ?
		}
		node_pointer y = x->left;
		x->left = y->right;
		if (y->right != _nil)
			y->right-> p = x;
		y->p = x->p;
		if (x->p == _nil)
			_root = y;
		else if (x->p == x->p->right)
			x->p->right = y;
		else
			x->p->left = y;
		y->right = x;
		x->p = y;
	}

	// x is a preallocated node with links pointing to T.nil
	// todo : leftmost/rightmost maintainance
	void __rb_insert_node(node_pointer node) {
		node_pointer parent = _nil;
		node_pointer trailing_ptr = _root;

		while (trailing_ptr != _nil) {
			parent = trailing_ptr;
			if (node->value < trailing_ptr->value)
				trailing_ptr = trailing_ptr->left;
			else
				trailing_ptr = trailing_ptr->right;
		}
		node->p = parent;
		if (parent == _nil) {
			_root = node;
			// _leftmost = node;
			// _rightmost = node;
		}
		else if (node->value < parent->value)
			parent->left = node;
		else
			parent->right = node;
		node->left = _nil;
		node->right = _nil;
		node->color = red;

		// rebalancing routine: recoloring & rotations
		node_pointer uncle;
		node_pointer pivot = node;
		
		while (pivot->p->color == red && pivot->p->p != _root/* ? */) {
		// while (pivot->color == red && pivot != _root && pivot->p->p != _root && pivot->p != _root/* ? */) {
			if (pivot->p == pivot->p->p->left) {
				uncle = pivot->p->p->right;
				if (uncle->color == red) {
					pivot->p->color = black;
					uncle->color = black;
					pivot->p->p->color = red;
					pivot = pivot->p->p;
				}
				else if (pivot == pivot->p->right) {
					pivot = pivot->p;
					std::cout << "in if Lrot" << std::endl;
					__rb_left_rotate(pivot);
				}
				pivot->p->color = black;
				pivot->p->p->color = red;
				std::cout << "in if Rrot" << std::endl;
				__rb_right_rotate(pivot->p->p);
			}
			else {
				uncle = pivot->p->p->left;
				if (uncle->color == red) {
					pivot->p->color = black;
					uncle->color = black;
					if (pivot->p != _root)
						pivot->p->p->color = red;
					pivot = pivot->p->p;
				}
				else if (pivot == pivot->p->left) {
					pivot = pivot->p;
					std::cout << "in else Rrot" << std::endl;
					__rb_right_rotate(pivot);
				}
				pivot->p->color = black;
				if (pivot->p != _root)
					pivot->p->p->color = red;
				std::cout << "in else Lrot" << std::endl;
				__rb_left_rotate(pivot->p->p);
			}
			}
		_root->color = black;
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
		// __rb_tree_inorder_walk(_root, &rb_tree_node::print_value);
		__pretty_print("", _root, false, -1);
		std::cout << std::endl;
	}

	void info() const {
		std::cout << "root:" << _root->value << std::endl;
	}

	static node_pointer __rb_tree_genarate_nil() {
		node_pointer nil = _node_allocator.allocate(1);
		_node_allocator.construct(nil, rb_tree_node());
		return (nil);
	}

// * * *

private:

	void __pretty_print(std::string prefix, node_pointer x, bool isleft, int iter) const {
		++iter;
		if (x != NULL) {
			std::cout << "\033[0;34m";
			std::cout << prefix;
			if (x == _root) {
				std::cout << "└──";
				std::cout << iter << "* ";
			}
			else {
				std::cout << (isleft ? "├──" : "└──");
				std::cout << iter;
				std::cout << (isleft ? "L " : "R ");
			}
			std::cout << "\033[0m";
			if (x->color == red)
				std::cout << "\033[0;31m";
			if (x == _nil)//<< "\033[0;34m"
				std::cout  << "⁙";
			else
				std::cout << x->value;
			std::cout << "\033[0m" << std::endl;
			__pretty_print(prefix + (isleft ? "│     " : "      "), x->left, true, iter);
			__pretty_print(prefix + (isleft ? "│     " : "      "), x->right, false, iter);
		}
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
	rb_tree<Value, Compare>::_nil = rb_tree<Value, Compare>::__rb_tree_genarate_nil();
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

