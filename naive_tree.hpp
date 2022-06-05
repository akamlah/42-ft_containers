/* ************************************************************************ */
/*																			*/
/*								ft:: MAP									*/
/*																			*/
/* ************************************************************************ */
/* ------------------------------- CONTENTS ----------------------------------

all leaves are objet node nil, const isblack black
_root->p = NULL;
NULL->left = _root;
NULL->right = NULL;
--------------------------------------------------------------------------- */

#ifndef _FT_NAIVE_TREE_HPP_
# define _FT_NAIVE_TREE_HPP_

// #define DBG_ME 0
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
	// static nil_allocator_type NULL_allocator;

	node_pointer _end_node;
	node_pointer _root; // make pvt with accessor
	node_pointer _nil;

	// node_pointer _leftmost; // for linear time begin()
	// node_pointer _rightmost; // for linear time in set functions (?) & empty()


/* ------------------------------------------------------------------------ */
/* ======================== MEMBER FUNCTIONS ============================== */
/* ------------------------------------------------------------------------ */

public:

/* ------------------------ construction: --------------------------------- */

	rb_tree() {

		_end_node = __allocate_rb_node(value_type()); // is red ... 
		_nil = __allocate_rb_node(value_type());
		_nil->isblack = true;
		_root = _nil;
	}

	rb_tree(const rb_tree& other);
	rb_tree& operator=(const rb_tree& other);

/* ------------------------ destruction: ---------------------------------- */
	
	~rb_tree() {
		// destroy & free all nodes (and values?)
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
		if (_root == _nil) {
			_root = node;
			node->p = _end_node;
			_end_node->left = _root;
			_end_node->right = _root;
			// _leftmost = _root;
			// _rightmost = _root;
			_root->isblack = true;
			std::cout << "insert node (case root): "; node->__node_info_();
			print_tree();
			return ;
		}
		std::cout << "insert node (case normal): "; node->__node_info_();
		__rb_insert_node(node);
		print_tree();
	}

/* ======================== INTERNAL FUNCTIONALITIES ====================== */
// private:

// * * *

	node_pointer __allocate_rb_node(const_reference value) const {
		node_pointer node = _node_allocator.allocate(1);
		_node_allocator.construct(node, rb_tree_node());
		// so now node->p, node->left, node->right = NULL, isblack = false, value x
		// -> have node constructor that constructs value inside to avoid copying...
		_value_allocator.construct(&node->value, value);
		node->left = _nil;
		node->right = _nil;
		node->p = _nil;

		std::cout << "allc node: "; node->__node_info_();

		return (node);
	}

	// todo : leftmost/rightmost maintainance
	void __rb_left_rotate(node_pointer x) {
		node_pointer y = x->right;
		x->right = y->left;
		if (y->left != _nil)
			y->left->p = x;
		y->p = x->p;
		if (x->p == _end_node) // || null?
			_root = y;
		else if (x == x->p->left)
			x->p->left = y;
		else
			x->p->right = y;
		y->left = x;
		x->p = y;
	}

	// todo : leftmost/rightmost maintainance
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
		if (node->value < y->value)
			y->left = node;
		else
			y->right = node;
		if (node->p && node->p->p && node->p->p != _end_node) { // if x is at least in second level ?
			print_tree();
			__rb_insert_fixup(node);
		}
	}

	void __rb_insert_fixup(node_pointer x) {
		std::cout << "Insert fixup " << std::endl;
		while (x != _root && !x->p->isblack) {
			if (x->p == x->p->p->left) { /* CASES A: px is left child of ppx */ std::cout << "CASE A";
				node_pointer y = x->p->p->right;
				if (!y->isblack) { /* CASE A1: uncle is red (& not null) */ std::cout << "1 " << std::endl;
					x = x->p;
					x->isblack = true;
					x = x->p;
					x->isblack = (x == _root);
					y->isblack = true;
				}
				else /* CASE A2-3: uncle is black or null */ {
					if (x == x->p->right) { std::cout << "2 " << std::endl; 
						x = x->p;
						__rb_left_rotate(x);
						print_tree();
					}
					std::cout << "3 " << std::endl;
					x = x->p;
					x->isblack = true;
					x = x->p;
					x->isblack = false;
					__rb_right_rotate(x);
					print_tree();
					break ;
				}
			}
			else { /* CASES B: px is left child of ppx */ std::cout << "CASE B";
				node_pointer y = x->p->p->left;
				if (!y->isblack) { std::cout << "1 " << std::endl; // same cond...
					x = x->p;
					x->isblack = true;
					x = x->p;
					x->isblack = (x == _root);
					y->isblack = true;
				}
				else /* CASE B2-3: uncle is black or null */ {
					if (x == x->p->left) { std::cout << "2 " << std::endl;
						x = x->p;
						__rb_right_rotate(x);
						print_tree();
					}
					std::cout << "3 " << std::endl;
					x = x->p;
					x->isblack = true;
					x = x->p;
					x->isblack = false;
					__rb_left_rotate(x);
					print_tree();
					break ;
				}
			}
		}
	}

/* ======================== WALKS ======================================= */

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

	void __rb_tree_branching_walk(node_pointer subtree_root,
		typename rb_tree_node::void_function_pointer f) {
		if (subtree_root != _nil) {
			__rb_tree_branching_walk(subtree_root->left, f);
			__rb_tree_branching_walk(subtree_root->right, f);
			(subtree_root->*f)();
		}
	}

/* ======================== LOOKUP ======================================= */

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

public:

	void print_tree() const { // ?
		// __rb_tree_inorder_walk(_root, &rb_tree_node::print_value);
		__pretty_print("", _root, false, -1);
		std::cout << std::endl;
	}

	void info() const {
		std::cout << "\033[0;34m";
		std::cout << "root:" << _root << " ";
		if (_root != _nil) {
			std::cout << "root->value:" << _root->value << " ";
			std::cout << "root->isblack?:" << _root->isblack << " ";
			std::cout << "root->p:" << _root->p << " ";
			std::cout << "root->l:" << _root->left << " ";
			if (_root->left != _nil)
				std::cout << "," << _root->left->value << " ";
			std::cout << "root->r:" << _root->right << " ";
			if (_root->right != _nil)
				std::cout << "," << _root->right->value << " ";
		}
		std::cout << "\033[0m";
		std::cout << std::endl;
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

