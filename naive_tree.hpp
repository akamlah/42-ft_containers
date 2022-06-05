/* ************************************************************************ */
/*																			*/
/*								ft:: MAP									*/
/*																			*/
/* ************************************************************************ */
/* ------------------------------- CONTENTS ----------------------------------

--------------------------------------------------------------------------- */

#ifndef _FT_NAIVE_TREE_HPP_
# define _FT_NAIVE_TREE_HPP_

// #define DBG_ME 0
#define DBG_ME 1

namespace ft { /* NAMESPACE FT */


/*
	Red-black tree datastructure implementation.
	The parent of the root is a node colled "_end_node"
	The leaves are implemented as nodes called "_nil".
	This allows to store variables as _nil->p (parent) in algorithms without
	extra cases. So all last nodes point to _nil.

	The end node is red.
	Root and _nil are black.
*/

template < /* RB TREE */
	class Value,
	class Compare
> class rb_tree {

/* ======================== MEMBER TYPES & CLASSES ========================= */

public:

	typedef Value value_type;
	typedef Compare compare_type;

	class rb_tree_node {
	public:
		rb_tree_node* p;
		rb_tree_node* left;
		rb_tree_node* right;
		value_type value;
		bool isblack;
		typedef void (rb_tree<Value, Compare>::rb_tree_node::*const_void_function_pointer) () const;
		typedef void (rb_tree<Value, Compare>::rb_tree_node::*void_function_pointer) () ;
		rb_tree_node(): p(NULL), left(NULL), right(NULL), value(), isblack(false) {
			__node_info_();
		}
		void print_value() const { std::cout << value << std::endl; }
		void __destroy_node() {
			rb_tree::_value_allocator.destroy(&this->value);
			rb_tree::_node_allocator.destroy(this);
			rb_tree::_node_allocator.deallocate(this, 1);
		}
		void __node_info_() {
			#if DBG_ME
				std::cout << "\033[38;5;67m";
				std::cout << "NODE INFO | ";
				std::cout << this << " | ";
				std::cout << "p:" << p << " l:" << left << " r" << right << " val:" \
				<< value << " col:" << isblack << "\033[0m" << std::endl;
			#endif
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

	static node_allocator_type _node_allocator;
	static value_allocator_type _value_allocator;

	node_pointer _end_node;
	node_pointer _root;
	node_pointer _nil;

/* ------------------------------------------------------------------------ */
/* ======================== PUBLIC MEMBER FUNCTIONS ======================= */
/* ------------------------------------------------------------------------ */

public:

/* ------------------------ construction: --------------------------------- */

	rb_tree() {

		_end_node = __allocate_rb_node(value_type());
		_nil = __allocate_rb_node(value_type());
		_nil->isblack = true;
		_root = _nil;
	}

	rb_tree(const rb_tree& other);
	rb_tree& operator=(const rb_tree& other);

/* ------------------------ destruction: ---------------------------------- */
	
	~rb_tree() {
		__rb_tree_branching_walk(_root, &rb_tree_node::__destroy_node);

		_node_allocator.destroy(_end_node);
		_node_allocator.deallocate(_end_node, 1);
		_node_allocator.destroy(_nil);
		_node_allocator.deallocate(_nil, 1);
	}

/* ======================== ACCESSORS ===================================== */

	bool empty() const {
		return (_root == NULL);
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


/* ------------------------------------------------------------------------ */
/* ======================== INTERNAL FUNCTIONALITIES ====================== */
/* ------------------------------------------------------------------------ */

private:

	node_pointer __allocate_rb_node(const_reference value) const {
		node_pointer node = _node_allocator.allocate(1);
		_node_allocator.construct(node, rb_tree_node());
		// so now node->p, node->left, node->right = NULL, isblack = false, value x
		// -> have node constructor that constructs value inside to avoid copying ?
		_value_allocator.construct(&node->value, value);
		node->left = _nil;
		node->right = _nil;
		node->p = _nil;
		return (node);
	}

/* ------------------------ rotations: ------------------------------------- */
	/*
		X, Y are nodes, a,b, and c subtrees (either nodes, _nil, or branching subtrees)
		Rotetions are reversible and change the local structure as follows:
		|                                                   |
		|       |          right rotate ->        |         |
		|       X                                 Y         |
		|      / \         <- left rotate        / \        |
		|     a   Y                             X   c       |
		|        / \                           / \          |
		|       b   c                         a   b         |
		|                                                   |
	*/

	/*
		Right-rotetes a node assuming node->right != _nil
		and the root's parent is _end_node
	*/
	void __rb_left_rotate(node_pointer x) {
		node_pointer y = x->right;
		x->right = y->left;
		if (y->left != _nil)
			y->left->p = x;
		y->p = x->p;
		if (x->p == _end_node)
			_root = y;
		else if (x == x->p->left)
			x->p->left = y;
		else
			x->p->right = y;
		y->left = x;
		x->p = y;
	}

	/*
		Right-rotetes a node assuming node->left != _nil
		and the root's parent is _end_node
	*/
	void __rb_right_rotate(node_pointer x) {
		node_pointer y = x->left;
		x->left = y->right;
		if (y->right != _nil)
			y->right->p = x;
		y->p = x->p;
		if (x->p == _end_node)
			_root = y;
		else if (x == x->p->right)
			x->p->right = y;
		else
			x->p->left = y;
		y->right = x;
		x->p = y;
	}

/* ------------------------ insertion: ------------------------------------ */

	/*
		Inserts nodes following standard binary search tree insertion routine
		afterwards calling __rb_insert_fixup to restore red-black properties.
	*/
	void __rb_insert_node(node_pointer node) {
		node_pointer y = _nil;
		node_pointer x = _root;
		while (x != _nil) {
			y = x;
			if (node->value < x->value)
				x = x->left;
			else
				x = x->right;
		}
		node->p = y;
		if (y == _nil) {
			_root = node;
			node->p = _end_node;
			_end_node->left = _root;
			_end_node->right = _root;
			_root->isblack = true;
		}
		else {
			if (node->value < y->value)
				y->left = node;
			else
				y->right = node;
			__rb_insert_fixup(node);
		}
	}

	/*
		Performs recoloring and rotations to rebalance the tree and restore
		red-black properties after insertion.
	*/
	void __rb_insert_fixup(node_pointer x) {
		while (x != _root && !x->p->isblack) {
			if (x->p == x->p->p->left) { /* CASES A: px is left child of ppx */
				node_pointer y = x->p->p->right;
				if (!y->isblack) { /* CASE 1: uncle is red (& not _nil, same cond because _nil->isblack = true) */
					x = x->p;
					x->isblack = true;
					x = x->p;
					x->isblack = (x == _root);
					y->isblack = true;
				}
				else { /* CASE 2+3: uncle is black (or _nil) */
					if (x == x->p->right) {  /* CASE 2: x is right child */
						x = x->p;
						__rb_left_rotate(x);
						print_tree();
					}
					x->p->isblack = true;
					x->p->p->isblack = false;
					x = x->p->p;
					__rb_right_rotate(x);
					break ;
				}
			}
			else { /* CASES B: px is left child of ppx */
				node_pointer y = x->p->p->left;
				if (!y->isblack) {/* CASE 1: uncle is red (& not null, same cond because _nil->isblack = true) */
					x = x->p;
					x->isblack = true;
					x = x->p;
					x->isblack = (x == _root);
					y->isblack = true;
				}
				else {  /* CASE 2+3: uncle is black (or _nil) */ 
					if (x == x->p->left) { /* CASE 2: x is left child */
						x = x->p;
						__rb_right_rotate(x);
						print_tree();
					}
					x->p->isblack = true;
					x->p->p->isblack = false;
					x = x->p->p;
					__rb_left_rotate(x);
					break ;
				}
			}
		}
	}

/* ======================== WALKS ======================================= */

	/*
		Recursively reaches all nodes sorted by value and applies function f.
		Function f is a void const function of class rb_tree_node.
	*/
	void __rb_tree_inorder_walk(node_pointer subtree_root,
		typename rb_tree_node::const_void_function_pointer f) const {
		if (subtree_root != _nil) {
			__rb_tree_inorder_walk(subtree_root->left, f);
			(subtree_root->*f)();
			__rb_tree_inorder_walk(subtree_root->right, f);
		}
	}

	/*
		Recursively reaches all nodes without repetition and applies function f.
		Function f is a void non-const function of class rb_tree_node.
	*/
	void __rb_tree_branching_walk(node_pointer subtree_root,
		typename rb_tree_node::void_function_pointer f) {
		if (subtree_root != _nil) {
			__rb_tree_branching_walk(subtree_root->left, f);
			__rb_tree_branching_walk(subtree_root->right, f);
			(subtree_root->*f)();
		}
	}

/* ======================== LOOKUP & DEBUGGING =========================== */

public:

	/*
		Prints tree (including _nil nodes) horizontally. Example:
		└──0* 8
		    ├──1L 3
		    │     ├──2L ⁙
		    │     └──2R ⁙
		    └──1R 99
		          ├──2L ⁙
		          └──2R ⁙
	*/
	void print_tree() const {
		__pretty_print("", _root, false, -1);
		std::cout << std::endl;
	}

private:

	/*
		Recursive core of print_tree()
	*/
	void __pretty_print(std::string prefix, node_pointer x, bool isleft, int iter) const {
		++iter;
		if (x == _nil) {
			std::cout << "\033[0;34m";
			std::cout << prefix;
			std::cout << (isleft ? "├──" : "└──");
			std::cout << iter;
			std::cout << (isleft ? "L " : "R ");
			std::cout << "\033[0m";
			std::cout << "⁙";
			std::cout << std::endl;
		}
		if (x != _nil) {
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
			if (x->isblack == false)
				std::cout << "\033[0;31m";
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

/* - end TREE ------------------------------------------------------------- */

} /* NAMESPACE FT end ------------------------------------------------------*/

#endif // _FT_NAIVE_TREE_HPP_

#undef DBG_ME

