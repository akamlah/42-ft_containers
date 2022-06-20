/* ************************************************************************ */
/*																			*/
/*								ft:: MAP									*/
/*																			*/
/* ************************************************************************ */
/* ------------------------------- CONTENTS ----------------------------------
--------------------------------------------------------------------------- */

#ifndef _FT__RB_TREE_HPP_
# define _FT__RB_TREE_HPP_

namespace ft { /* NAMESPACE FT */

template <class, class, class> class __rb_tree;

template <class NodePtr>
NodePtr successor_node(NodePtr x) {
	if (x->left == NULL || x->right == NULL)
		return (NULL);
	if (!(x->right->left == NULL || x->right->right == NULL))
		return (min_node(x->right));
	NodePtr y = x->p;
	while (!(y->left == NULL || y->right == NULL) && y->p != NULL && x == y->right) { /* == if x->value <= y->value */
		/* go up the tree, unless y found s.t. y = y->p->left*/
		x = y; /* i.e. y is set to its parent */
		y = y->p;
	}
	return (y);
}

template <class NodePtr>
NodePtr min_node(NodePtr subtree_root) {
	NodePtr x = subtree_root;
	while (x != NULL && !(x->right == NULL || x->left == NULL) && x->left != NULL && !(x->left->left == NULL || x->left->right == NULL))
		x = x->left;
	return (x);
}

template <class NodePtr>
NodePtr predeccessor_node(NodePtr x) {
	if (x->left == NULL || x->right == NULL)
		return (NULL);
	if (!(x->left->left == NULL || x->left->right == NULL))
		return (max_node(x->left));
	NodePtr y = x->p;
	while (!(y->left == NULL || y->right == NULL) && y->p != NULL && x == y->left) { /* == if x->value <= y->value */
		/* go up the tree, unless y found s.t. y = y->p->left*/
		x = y; /* i.e. y is set to its parent */
		y = y->p;
	}
	return (y);
}

template <class NodePtr>
NodePtr max_node(NodePtr subtree_root) {
	NodePtr x = subtree_root;
	// while (x != NULL && !(x->right == NULL || x->left == NULL) && x->right && !(x->right->left == NULL || x->right->right == NULL))
	while (1) {
		if (x == NULL 
		|| (x->right == NULL 
		|| x->left == NULL) 
		|| x->right == NULL)
			break ;
		// if (x->right->left == NULL 
		// || x->right->right == NULL)
			break ;
		x = x->right;
	}
	return (x);
}

/* ---------------------------------------------------------------------------

RED BLACK TREE

--------------------------------------------------------------------------- */
/*
	Red-black tree datastructure implementation.
	The parent of the root is a node colled "_end_node"
	The leaves are implemented as nodes called "NULL", for convenience in
	dealing with boundary conditions.
	So all last nodes point to NULL.
	The end node is red.
	Root and NULL are black.
*/

template < /* RB TREE */
	class Value,
	class Compare,
	class Allocator
> class __rb_tree {

/* ======================== MEMBER TYPES & CLASSES ========================= */

	class __rb_node;

public:

	typedef Value value_type;
	typedef Compare compare_type;
	typedef Allocator value_allocator_type;
	typedef typename value_allocator_type::pointer			pointer;
	typedef typename value_allocator_type::reference		reference;
	typedef typename value_allocator_type::const_reference	const_reference;

	typedef typename value_allocator_type::template rebind<__rb_node>::other node_allocator_type;

	typedef typename node_allocator_type::pointer			node_pointer;
	typedef typename node_allocator_type::size_type			size_type;
	typedef typename node_allocator_type::difference_type	difference_type;

	class rb_tree_iterator {
	public:
		friend class __rb_tree;
		// category
		typedef typename __rb_tree<Value, Compare, Allocator>::value_type		value_type;
		typedef typename __rb_tree<Value, Compare, Allocator>::difference_type	difference_type;
		typedef typename __rb_tree<Value, Compare, Allocator>::node_pointer		node_pointer;
		typedef typename __rb_tree<Value, Compare, Allocator>::reference		reference;
	private:
		node_pointer	_node_ptr;
	public:
		rb_tree_iterator(node_pointer x): _node_ptr(x) {}
		rb_tree_iterator(const rb_tree_iterator& other): _node_ptr(other._node_ptr) {}
		~rb_tree_iterator() {}

		node_pointer get_node_ptr() const { return (_node_ptr); }
		void set_node_ptr(const node_pointer x) { _node_ptr = x; }

		rb_tree_iterator& operator=(const node_pointer& other)
			{ _node_ptr = other._node_ptr; return (*this); }

		reference operator*() const { return (_node_ptr->value); }
		pointer operator->() const { return (std::addressof(operator*())); }

		rb_tree_iterator& operator++() 
			{ _node_ptr = successor_node(_node_ptr); return (*this); }

		rb_tree_iterator& operator--() 
			{ _node_ptr = predeccessor_node(_node_ptr); return (*this); }

		friend bool operator==(const rb_tree_iterator& lhs, const rb_tree_iterator& rhs)
			{ return (lhs.get_node_ptr() == rhs.get_node_ptr()); } // compare ptr or values? test !

		friend bool operator!=(const rb_tree_iterator& lhs, const rb_tree_iterator& rhs)
			{ return (!(lhs == rhs)); }
	};

	class rb_tree_const_iterator {
	public:
		typedef typename __rb_tree<Value, Compare, Allocator>::value_type		value_type;
		typedef typename __rb_tree<Value, Compare, Allocator>::difference_type	difference_type;
		typedef typename __rb_tree<Value, Compare, Allocator>::node_pointer		node_pointer;
		typedef typename __rb_tree<Value, Compare, Allocator>::reference		reference;
	private:
		const node_pointer	_node_ptr;
	public:
		rb_tree_const_iterator(node_pointer x): _node_ptr(x) {}
		rb_tree_const_iterator(const rb_tree_const_iterator& other): _node_ptr(other._node_ptr) {}
		~rb_tree_const_iterator() {}
		
		node_pointer get_node_ptr() const { return (_node_ptr); }

		friend bool operator==(const rb_tree_const_iterator& lhs, const rb_tree_const_iterator& rhs)
			{ return (lhs.get_node_ptr() == rhs.get_node_ptr()); } // compare ptr or values? test !
		friend bool operator!=(const rb_tree_const_iterator& lhs, const rb_tree_const_iterator& rhs)
			{ return (!(lhs == rhs)); }
	};

	typedef rb_tree_iterator		iterator;
	typedef rb_tree_const_iterator	const_iterator;

private:

	class __rb_node {
	public:
		__rb_node* p;
		__rb_node* left;
		__rb_node* right;
		value_type value;
		bool isblack;

		typedef void (__rb_tree<Value, Compare, Allocator>::__rb_node::*const_void_function_pointer) () const;
		typedef void (__rb_tree<Value, Compare, Allocator>::__rb_node::*void_function_pointer) ();

		__rb_node(): p(NULL), left(NULL), right(NULL), value(), isblack(false) {}
		void print_value() const { std::cout << value << std::endl; }
		void __destroy() {
			__rb_tree::_value_allocator.destroy(&this->value);
			__rb_tree::_node_allocator.destroy(this);
			__rb_tree::_node_allocator.deallocate(this, 1);
		}
	};

/* ======================== ATTRIBUTES ==================================== */
private: // (protected ?)

	static node_allocator_type _node_allocator;
	static value_allocator_type _value_allocator;

// protected:
public:

	node_pointer _end_node;

	node_pointer _root;
	// node_pointer NULL;

/* ------------------------------------------------------------------------ */
/* ======================== PUBLIC MEMBER FUNCTIONS ======================= */
/* ------------------------------------------------------------------------ */
public:
/* ------------------------ construction: --------------------------------- */

	__rb_tree() {

		std::cout << "tree constr" << std::endl; // REMOVE

		__rb_init();
	}

	// __rb_tree(const __rb_tree& other);
	// __rb_tree& operator=(const __rb_tree& other);

/* ------------------------ destruction: ---------------------------------- */
	
	~__rb_tree() {
		__rb_tree_branching_walk(_root, &__rb_node::__destroy);
		_node_allocator.destroy(_end_node);
		_node_allocator.deallocate(_end_node, 1);
		// _node_allocator.destroy(NULL);
		// _node_allocator.deallocate(NULL, 1);
	}

/* ======================== ACCESSORS ===================================== */

	bool empty() const { return (_root == NULL); }
	// node_pointer nil() { return (NULL); }


/* ======================== QUERIES ======================================= */

	/*
		MAX
		Returns pointer to node with maximum value or NULL if the tree
		is empty or the node passed was NULL.
	*/
	node_pointer rb_max(node_pointer subtree_root) const {
		return (max_node(subtree_root));
		// node_pointer x = subtree_root;
		// while (x != NULL && x->right != NULL)
		// 	x = x->right;
		// return (x);
	}

	node_pointer rb_max() const { return (rb_max(_root)); }

	/*
		MIN
		Returns pointer to node with minimum value or NULL if the tree
		is empty or the node passed was NULL.
	*/
	node_pointer rb_min(node_pointer subtree_root) const {
		node_pointer x = subtree_root;
		while (x != NULL && x->left != NULL)
			x = x->left;
		return (x);
	}

	node_pointer rb_min() const { return (rb_min(_root)); }

	/*
		SEARCH
		Searches for a node containing the value given in a (sub-)tree rooted
		in the passed node. Returns a pointer to the node found or NULL
		if the tree was empty or no node was found.
	*/
	node_pointer rb_search(node_pointer subtree_root, value_type value) const {
		node_pointer x = subtree_root;
		while (x != NULL && value != x->value) {
			if (value < x->value)
				x = x->left;
			else
				x = x->right;
		}
		return (x);
	}

	node_pointer rb_search(value_type value) const { return (rb_search(_root, value)); }

	/*
		SUCCESSOR
		Returns pointer to the minimum of all values greater than x,
		or NULL if the tree was empty or the node passed was NULL.
	*/
	node_pointer rb_successor(node_pointer x) const {
		if (x == NULL)
			return (NULL);
		if (x->right != NULL)
			return (rb_min(x->right));
		node_pointer y = x->p;
		while (y != NULL && y != _end_node && x == y->right) { /* == if x->value <= y->value */
			/* go up the tree, unless y found s.t. y = y->p->left*/
			x = y; /* i.e. y is set to its parent */
			y = y->p;
		}
		return (y);
	}

	node_pointer rb_successor(value_type value) const {
		node_pointer x = rb_search(_root, value);
		return rb_successor(x);
	}

	/*
		PREDECESSOR
	*/
	node_pointer rb_predecessor(node_pointer x) const {
		if (x == NULL)
			return (NULL);
		if (x->left != NULL)
			return (rb_max(x->left));
		node_pointer y = x->p;
		while (y != NULL && y != _end_node && x == y->left) {
			x = y;
			y = y->p;
		}
		return (y);
	}

	node_pointer rb_predecessor(value_type value) const {
		node_pointer x = rb_search(_root, value);
		return rb_predecessor(x);
	}

/* ======================== MODIFIERS ===================================== */

	/*
		INSERT VALUE
		Allocates a node containing the value given and inserts it ito the
		tree. Recoloring and rotation operations might be performed.
		Returns [...]
	*/
	node_pointer rb_insert(const_reference value) {
		node_pointer node = __allocate_rb_node(value);
		__rb_insert_node(node);
		return (node);
	}

	/*
		DELETE VALUE
		Seraches for a node containing the value given and removes it from
		the tree. Does nothing if the value was not found.
		Recoloring and rotation operations might be performed.
	*/
	void rb_delete(const_reference value) {
		node_pointer z = rb_search(_root, value);
		if (z == NULL)
			return ;
		__rb_delete(z);
	}

/* ------------------------------------------------------------------------ */
/* ======================== INTERNAL FUNCTIONALITIES ====================== */
/* ------------------------------------------------------------------------ */

/* ------------------------ memory alocation: ----------------------------- */

private:

	void __rb_init() {
		_end_node = __allocate_rb_node(value_type()); // assignment is problem with const Value attributes!!
		// NULL = __allocate_rb_node(value_type());
		// NULL->isblack = true;
		_root = NULL;
	}

	// idea make an overload with void that builds defaukt node without value inplace.

	node_pointer __allocate_rb_node(const_reference value) const {
		node_pointer node = _node_allocator.allocate(1);
		_node_allocator.construct(node, __rb_node());
		// so now node->p, node->left, node->right = NULL, isblack = false, value x
		// -> have node constructor that constructs value inside to avoid copying ?
		_value_allocator.construct(&node->value, value);
		node->left = NULL;
		node->right = NULL;
		node->p = NULL;
		return (node);
	}

/* ------------------------ rotations: ------------------------------------ */
	/*
		X, Y are nodes, a,b, and c subtrees (either nodes, NULL, or branching subtrees)
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
		Right-rotates a node assuming node->right != NULL
		and the root's parent is _end_node
	*/
	void __rb_left_rotate(node_pointer x) {
		node_pointer y = x->right;
		x->right = y->left;
		if (y->left != NULL)
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
		Right-rotates a node assuming node->left != NULL
		and the root's parent is _end_node
	*/
	void __rb_right_rotate(node_pointer x) {
		node_pointer y = x->left;
		x->left = y->right;
		if (y->right != NULL)
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
		node_pointer y = NULL;
		node_pointer x = _root;
		while (x != NULL) {
			y = x;
			if (node->value < x->value)
				x = x->left;
			else
				x = x->right;
		}
		node->p = y;
		if (y == NULL) {
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
		while (x != _root && x->p && !x->p->isblack ) {
		/* CASES A: px is left child of ppx */
			if (x->p == x->p->p->left) {
				y = x->p->p->right;
				/* CASE 1: uncle is red (& not NULL, same cond because NULL->isblack = true) */
				if (!y->isblack) {
					x = x->p;
					x->isblack = true;
					x = x->p;
					x->isblack = (x == _root);
					y->isblack = true;
				}
				/* CASE 2+3: uncle is black (or NULL) */
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
				/* CASE 1: uncle is red (& not null, same cond because NULL->isblack = true) */
				if (!y->isblack) {
					x = x->p;
					x->isblack = true;
					x = x->p;
					x->isblack = (x == _root);
					y->isblack = true;
				}
				/* CASE 2+3: uncle is black (or NULL) */ 
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
		if (z->left == NULL) {
			fixup_pivot = z->right;
			__rb_transplant(z, z->right);
		}
		else if (z->right == NULL) {
			fixup_pivot = z->left;
			__rb_transplant(z, z->left);
		}
		else {
			node_pointer y = rb_min(z->right);
			was_black = y->isblack;
			fixup_pivot = y->right;
			if (y->p == z)
				/* pivot can be NULL, storing p info for fixup */
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
		if (was_black && _root != NULL)
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
					if (!y->right->isblack && y->right != NULL) {
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
					if (y->left->isblack || y->left == NULL) {
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
	void __rb_tree_inorder_walk(node_pointer subtree_root,
		typename __rb_node::const_void_function_pointer f) const {
		if (subtree_root != NULL) {
			__rb_tree_inorder_walk(subtree_root->left, f);
			(subtree_root->*f)();
			__rb_tree_inorder_walk(subtree_root->right, f);
		}
	}

	/*
		Recursively reaches all nodes without repetition and applies function f.
		Function f is a void non-const function of class __rb_node.
	*/
	void __rb_tree_branching_walk(node_pointer subtree_root,
		typename __rb_node::void_function_pointer f) {
		if (subtree_root != NULL) {
			__rb_tree_branching_walk(subtree_root->left, f);
			__rb_tree_branching_walk(subtree_root->right, f);
			(subtree_root->*f)();
		}
	}

/* ======================== LOOKUP & DEBUGGING =========================== */



}; /* RB TREE */

/* - STATIC ATTRIBUTES ---------------------------------------------------- */

// static node allocator definition:
template <class Value, class Compare, class Allocator>
	typename __rb_tree<Value, Compare, Allocator>::node_allocator_type
	__rb_tree<Value, Compare, Allocator>::_node_allocator;

// static value allocator definition:
template <class Value, class Compare, class Allocator>
	typename __rb_tree<Value, Compare, Allocator>::value_allocator_type
	__rb_tree<Value, Compare, Allocator>::_value_allocator;

/* - end TREE ------------------------------------------------------------- */

} /* NAMESPACE FT end ------------------------------------------------------*/

#endif // _FT__RB_TREE_HPP_
