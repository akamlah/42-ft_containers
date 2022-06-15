/* ************************************************************************ */
/*																			*/
/*								ft:: MAP									*/
/*																			*/
/* ************************************************************************ */
/* ------------------------------- CONTENTS ----------------------------------

--------------------------------------------------------------------------- */

#ifndef _FT__RB_TREE_HPP_
# define _FT__RB_TREE_HPP_

// #define DBG_ME 0
#define DBG_ME 1

namespace ft { /* NAMESPACE FT */


/*
	Red-black tree datastructure implementation.
	The parent of the root is a node colled "_end_node"
	The leaves are implemented as nodes called "_nil", for convenience in
	dealing with boundary conditions.
	So all last nodes point to _nil.
	The end node is red.
	Root and _nil are black.
*/

template < /* RB TREE */
	class Value,
	class Compare,
	class Allocator
> class __rb_tree {

/* ======================== MEMBER TYPES & CLASSES ========================= */

public:

	typedef Value value_type;
	typedef Compare compare_type;
	typedef Allocator value_allocator_type;
	typedef typename value_allocator_type::pointer			pointer;
	typedef typename value_allocator_type::reference		reference;
	typedef typename value_allocator_type::const_reference	const_reference;

private:

	class __rb_node {
	public:
		__rb_node* p;
		__rb_node* left;
		__rb_node* right;
		value_type value;
		bool isblack;
		typedef void (__rb_tree<Value, Compare>::__rb_node::*const_void_function_pointer) () const;
		typedef void (__rb_tree<Value, Compare>::__rb_node::*void_function_pointer) () ;
		__rb_node(): p(NULL), left(NULL), right(NULL), value(), isblack(false) {
			// info();
		}
		void print_value() const { std::cout << value << std::endl; }
		void __destroy() {
			__rb_tree::_value_allocator.destroy(&this->value);
			__rb_tree::_node_allocator.destroy(this);
			__rb_tree::_node_allocator.deallocate(this, 1);
		}
		void info() {
			#if DBG_ME
				std::cout << "\033[38;5;67m";
				std::cout << "NODE INFO | ";
				std::cout << this << " | ";
				std::cout << "p:" << p << " l:" << left << " r" << right << " val:" \
				<< value << " col:" << isblack << "\033[0m" << std::endl;
			#endif
		}
	};

public:

	// typedef typename std::allocator<Value>					value_allocator_type;
	typedef typename value_allocator_type::template rebind<__rb_node>::other node_allocator_type;
	typedef typename node_allocator_type::pointer			node_pointer;
	typedef typename node_allocator_type::size_type			size_type;
	typedef typename node_allocator_type::difference_type	difference_type;

/* ======================== ATTRIBUTES ==================================== */

// private: // (protected ?)

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

	__rb_tree() {
		__rb_init();
	}

	// __rb_tree(const __rb_tree& other);
	// __rb_tree& operator=(const __rb_tree& other);

/* ------------------------ destruction: ---------------------------------- */
	
	~__rb_tree() {
		____rb_tree_branching_walk(_root, &__rb_node::__destroy);
		_node_allocator.destroy(_end_node);
		_node_allocator.deallocate(_end_node, 1);
		_node_allocator.destroy(_nil);
		_node_allocator.deallocate(_nil, 1);
	}

/* ======================== ACCESSORS ===================================== */

	bool empty() const {
		return (_root == _nil);
	}

/* ======================== QUERIES ======================================= */

	/*
		MAX
		Returns pointer to node with maximum value or _nil if the tree
		is empty or the node passed was _nil.
	*/
	node_pointer rb_max(node_pointer subtree_root) const {
		node_pointer x = subtree_root;
		while (x != _nil && x->right != _nil)
			x = x->right;
		return (x);
	}

	/*
		MIN
		Returns pointer to node with minimum value or _nil if the tree
		is empty or the node passed was _nil.
	*/
	node_pointer rb_min(node_pointer subtree_root) const {
		node_pointer x = subtree_root;
		while (x != _nil && x->left != _nil)
			x = x->left;
		return (x);
	}

	/*
		SEARCH
		Searches for a node containing the value given in a (sub-)tree rooted
		in the passed node. Returns a pointer to the node found or _nil
		if the tree was empty or no node was found.
	*/
	node_pointer rb_search(node_pointer subtree_root, value_type value) const {
		node_pointer x = subtree_root;
		while (x != _nil && value != x->value) {
			if (value < x->value)
				x = x->left;
			else
				x = x->right;
		}
		return (x);
	}

	/*
		SUCCESSOR
		Returns pointer to the minimum of all values greater than x,
		or _nil if the tree was empty or the node passed was _nil.
	*/
	node_pointer rb_successor(value_type value) const {
		node_pointer x = rb_search(_root, value);
		if (x == _nil)
			return (_nil);
		if (x->right != _nil)
			return (rb_min(x->right));
		node_pointer y = x->p;
		while (y != _nil && y != _end_node && x == y->right) { /* == if x->value <= y->value */
			/* go up the tree, unless y found s.t. y = y->p->left*/
			x = y; /* i.e. y is set to its parent */
			y = y->p;
		}
		return (y);
	}

/* ======================== MODIFIERS ===================================== */

	/*
		INSERT VALUE
		Allocates a node containing the value given and inserts it ito the
		tree. Recoloring and rotation operations might be performed.
		Returns [...]
	*/
	void rb_insert(const_reference value) {
		node_pointer node = __allocate_rb_node(value);
		/* node ptr = */ __rb_insert_node(node);
		// return (iterator to the node, bool true)
		// if node->vl < leftmost, leftmost = node etc
	}

	/*
		DELETE VALUE
		Seraches for a node containing the value given and removes it from
		the tree. Does nothing if the value was not found.
		Recoloring and rotation operations might be performed.
	*/
	void rb_delete(const_reference value) {
		node_pointer z = rb_search(_root, value);
		if (z == _nil)
			return ;
		__rb_delete(z);
	}

/* ------------------------------------------------------------------------ */
/* ======================== INTERNAL FUNCTIONALITIES ====================== */
/* ------------------------------------------------------------------------ */

/* ------------------------ memory alocation: ----------------------------- */

private:

	void __rb_init() {
		#if DBG_ME
		std::cout << "END ";
		#endif
		_end_node = __allocate_rb_node(value_type());
		#if DBG_ME
		std::cout << "NIL ";
		#endif
		_nil = __allocate_rb_node(value_type());
		_nil->isblack = true;
		_root = _nil;
	}

	node_pointer __allocate_rb_node(const_reference value) const {
		node_pointer node = _node_allocator.allocate(1);
		_node_allocator.construct(node, __rb_node());
		// so now node->p, node->left, node->right = NULL, isblack = false, value x
		// -> have node constructor that constructs value inside to avoid copying ?
		_value_allocator.construct(&node->value, value);
		node->left = _nil;
		node->right = _nil;
		node->p = _nil;
		/* dbg */ node->info();
		return (node);
	}

/* ------------------------ rotations: ------------------------------------ */
	/*
		X, Y are nodes, a,b, and c subtrees (either nodes, _nil, or branching subtrees)
		Rotations are reversible and change the local structure as follows:
		|                                                      |
		|       |          right rotate X ->         |         |
		|       X                                    Y         |
		|      / \         <- left rotate Y         / \        |
		|     a   Y                                X   c       |
		|        / \                              / \          |
		|       b   c                            a   b         |
		|                                                      |
	*/

	/*
		Right-rotates a node assuming node->right != _nil
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
		Right-rotates a node assuming node->left != _nil
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

/* ------------------------ transplant: ----------------------------------- */

	/*
		Replaces subtree rooted at node u with subtree rooted at node v.
		Does not update v->left and v->right.
	*/
	node_pointer __rb_transplant(node_pointer u, node_pointer v) {
		if (u->p == _end_node)
			_root = v;
		else if (u == u->p->left)
			u->p->left = v;
		else
			u->p->right = v;
		v->p = u->p;
		return u; // to not loose ptr, for leaks (?)
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
		node_pointer y;
		while (x != _root && !x->p->isblack) {
		/* CASES A: px is left child of ppx */
			if (x->p == x->p->p->left) {
				y = x->p->p->right;
				/* CASE 1: uncle is red (& not _nil, same cond because _nil->isblack = true) */
				if (!y->isblack) {
					x = x->p;
					x->isblack = true;
					x = x->p;
					x->isblack = (x == _root);
					y->isblack = true;
				}
				/* CASE 2+3: uncle is black (or _nil) */
				else {
					/* CASE 2: x is right child */
					if (x == x->p->right) {
						x = x->p;
						__rb_left_rotate(x);
					}
					/* CASE 3 */
					x->p->isblack = true;
					x->p->p->isblack = false;
					x = x->p->p;
					__rb_right_rotate(x);
					break ;
				}
			}
		/* CASES B: px is left child of ppx */
			else {
				y = x->p->p->left;
				/* CASE 1: uncle is red (& not null, same cond because _nil->isblack = true) */
				if (!y->isblack) {
					x = x->p;
					x->isblack = true;
					x = x->p;
					x->isblack = (x == _root);
					y->isblack = true;
				}
				/* CASE 2+3: uncle is black (or _nil) */ 
				else {
					/* CASE 2: x is left child */
					if (x == x->p->left) {
						x = x->p;
						__rb_right_rotate(x);
					}
					/* CASE 3 */
					x->p->isblack = true;
					x->p->p->isblack = false;
					x = x->p->p;
					__rb_left_rotate(x);
					break ;
				}
			}
		}
	}

/* ------------------------ deletion: ----------------------------------- */

	/*
		Standard binary search tree deletion algorithm + color tmp variables
		and maintenance of a pointer to the pivot for the fixup routine.
		Calls fixup function to restore red-black properties.
		CASE 1 (else): z has empty left subtree
		CASE 2 (else if): z has non-empty left subtree but empty right subtree
		CASE 3+4 (else): z has both non-empty left and non-empty right subtrees
			CASE 3 (if): z->R min was z'successor
			CASE 4 (else): z->R min is not z's child (i.e. successor)
			Both converge to a final transplant.
	*/
	void __rb_delete(node_pointer z) {
		node_pointer tmp_z = z;
		node_pointer fixup_pivot;
		bool was_black = z->isblack;
		if (z->left == _nil) {
			fixup_pivot = z->right;
			__rb_transplant(z, z->right);
		}
		else if (z->right == _nil) {
			fixup_pivot = z->left;
			__rb_transplant(z, z->left);
		}
		else {
			node_pointer y = rb_min(z->right);
			was_black = y->isblack;
			fixup_pivot = y->right;
			if (y->p == z)
				/* pivot can be _nil, storing p info for fixup */
				fixup_pivot->p = y;
			else {
				__rb_transplant(y, y->right);
				y->right = z->right;
				y->right->p = y;
			}
			__rb_transplant(z, y);
			y->left = z->left;
			y->left->p = y;
			y->isblack = z->isblack;
		}
		tmp_z->__destroy();
		if (was_black && _root != _nil)
			__rb_delete_fixup(fixup_pivot);
	}

	/*
		Deletion fixup recoloring and rotation routine to restore
		red-black properties of the tree.
	*/
	void __rb_delete_fixup(node_pointer x) {
		node_pointer y; /* sibling of x */
		while (x != _root && x->isblack) {
		/* CASES A: x is left child, sibling y is right child */
			if (x == x->p->left) {
				y = x->p->right;
				/* CASE 1: sibling y is red. Goes into case 2/3/4. */
				if (!y->isblack) {
					y->p->isblack = false;
					y->isblack = true;
					__rb_left_rotate(y->p);
					if (_root == y->left)
						_root = y;
					y = y->left->right;
				}
				/* CASE 2: y is black and both childern are black */
				if (y->left->isblack && y->right->isblack) {
					y->isblack = false;
					x = y->p;
	/* TEST TODO */	// if (!x->isblack || x == _root) {
					// 	x->isblack = true;
					// 	break ;
					// }
					// if (y == x->left)
					// 	y = x->p->right;
					// else
					// 	y = x->p->left;
				}
				else {
					/* CASE 3(+4): y is black and only right child is black */
					if (!y->right->isblack && y->right != _nil) {
						y->left->isblack = true;
						y->isblack = false;
						__rb_right_rotate(y);
						y = y->p;
					}
					/* CASE 4: y is black and only right child is black */
					y->isblack = x->p->isblack;
					y->p->isblack = true;
					y->right->isblack = true;
					__rb_left_rotate(y->p);
					break ;
				}
			}
		/* CASES B: x is right child, sibling y is left child */
			else {
				y = x->p->left;
				/* CASE 1: sibling y is red. Goes into case 2/3/4. */
				if (!y->isblack) {
					y->p->isblack = false;
					y->isblack = true;
					__rb_right_rotate(y->p);
					if (_root == y->right)
						_root = y;
					y = y->right->left;
				}
				/* CASE 2: y is black and both childern are black */
				if (y->left->isblack && y->right->isblack) {
					y->isblack = false;
					x = y->p;
	/* TEST TODO */	// if (!x->isblack || x == _root) {
					// 	x->isblack = true;
					// 	break ;
					// }
					// if (y == x->left)
					// 	y = x->p->right;
					// else
					// 	y = x->p->left;
				}
				else {
					/* CASE 3(+4): y is black and only right child is black */
					if (y->left->isblack || y->left == _nil) {
						y->right->isblack = true;
						y->isblack = false;
						__rb_left_rotate(y);
						y = y->p;
					}
					/* CASE 4: y is black and only right child is black */
					y->isblack = y->p->isblack;
					y->p->isblack = true;
					y->left->isblack = true;
					__rb_right_rotate(y->p);
					break ;
				}
			}
		}
		x->isblack = true;
	}

/* ======================== WALKS ======================================= */

	/*
		Recursively reaches all nodes sorted by value and applies function f.
		Function f is a void const function of class __rb_node.
	*/
	void ____rb_tree_inorder_walk(node_pointer subtree_root,
		typename __rb_node::const_void_function_pointer f) const {
		if (subtree_root != _nil) {
			____rb_tree_inorder_walk(subtree_root->left, f);
			(subtree_root->*f)();
			____rb_tree_inorder_walk(subtree_root->right, f);
		}
	}

	/*
		Recursively reaches all nodes without repetition and applies function f.
		Function f is a void non-const function of class __rb_node.
	*/
	void ____rb_tree_branching_walk(node_pointer subtree_root,
		typename __rb_node::void_function_pointer f) {
		if (subtree_root != _nil) {
			____rb_tree_branching_walk(subtree_root->left, f);
			____rb_tree_branching_walk(subtree_root->right, f);
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
			/* un-/comment to print/not print nil's address */
				// std::cout << "\033[0;34m" << " " << x << "\033[0m";
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
			/* un-/comment to print/not print node's addresses */
				std::cout << " " << "\033[0;34m" << x;
			std::cout << "\033[0m" << std::endl;
			__pretty_print(prefix + (isleft ? "│     " : "      "), x->left, true, iter);
			__pretty_print(prefix + (isleft ? "│     " : "      "), x->right, false, iter);
		}
	}

}; /* RB TREE */

/* - STATIC ATTRIBUTES ---------------------------------------------------- */

// static node allocator definition:
template <class Value, class Compare>
	typename __rb_tree<Value, Compare>::node_allocator_type
	__rb_tree<Value, Compare>::_node_allocator;

// static value allocator definition:
template <class Value, class Compare>
	typename __rb_tree<Value, Compare>::value_allocator_type
	__rb_tree<Value, Compare>::_value_allocator;

/* - end TREE ------------------------------------------------------------- */

} /* NAMESPACE FT end ------------------------------------------------------*/

#endif // _FT__RB_TREE_HPP_

#undef DBG_ME

