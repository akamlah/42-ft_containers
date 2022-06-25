
/* ************************************************************************ */
/* ------------------------------- CONTENTS ----------------------------------
--------------------------------------------------------------------------- */

#ifndef FT_RB_TREE
# define FT_RB_TREE

#include "iterator.hpp"
// leaves point to null.
// root s.t. p = 0
// node pointer algorithms separately.
#include <map>

namespace ft { /* NAMESPACE FT */

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
------------------------
	RED BLACK TREE
------------------------
Red-black tree datastructure implementation.
The parent of the root is a node colled "_end_node"
The leaves are implemented as nodes called "_NIL", for convenience in
dealing with boundary conditions.
So all last nodes point to _NIL.
The end node is red.
Root and _NIL are black.
*/

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

template <	class T,
			class Compare,
			// class Compare = typename std::map<>::key_compare,
			// class Compare = std::less<T>, // test with this for integers or objects holding ints
			class Allocator = std::allocator<T> > // ?????????????? or free here and pass in map?
class rb_tree {

// types/ classes - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

public:

typedef T												value_type;
typedef Compare											value_compare;
typedef Allocator										value_allocator_type;
typedef typename value_allocator_type::pointer			pointer;
typedef typename value_allocator_type::const_pointer	const_pointer;
typedef typename value_allocator_type::reference		reference;
typedef typename value_allocator_type::const_reference	const_reference;

private:

// class rb_node;
// friend class rb_node; // because access to _NIL, pvt attribute of tree classes, is needed

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

class rb_node {
public:
	rb_node* parent;
	rb_node* left;
	rb_node* right;
	value_type value;
	bool isblack;
	rb_node(bool isblack = false): parent(NULL), left(NULL), right(NULL), value(), isblack(isblack) {}
	rb_node(value_type val): parent(_NIL), left(_NIL), right(_NIL), value(val), isblack(false) {}
	rb_node(const rb_node& other)
		: parent(_NIL), left(_NIL), right(_NIL), value(other.value), isblack(false) {}
	// virtual ~rb_node() {} // not needed ?
	void __destroy()
		{ rb_tree::_node_allocator.destroy(this); rb_tree::_node_allocator.deallocate(this, 1); }
	// hacky ^^
};

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

public:

typedef typename value_allocator_type::template rebind<rb_node>::other	node_allocator_type;
typedef typename node_allocator_type::pointer							node_pointer;
typedef typename node_allocator_type::size_type							size_type;
typedef typename node_allocator_type::difference_type					difference_type;

// class rb_iterator;
// friend class rb_iterator; // also because access to _NIL and other functions needed. ?
// template <class, class, class, class> friend class map; // needed ???
	// template <class, class, class, class> class map;
	// template <class, class, class, class> friend class map; // needed ???

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

class rb_iterator {
public:
	typedef bidirectional_iterator_tag				iterator_category;
	typedef typename rb_tree::value_type			value_type;
	typedef typename rb_tree::difference_type		difference_type;
	typedef typename rb_tree::reference				reference;
	typedef typename rb_tree::pointer				pointer;

	typedef typename rb_tree::node_pointer			node_pointer; // ??? ugly ...
private:
	node_pointer _base_ptr;
public:
	rb_iterator(): _base_ptr(_NIL) {}
	rb_iterator(const node_pointer& x): _base_ptr(x) {}

	node_pointer get_base_ptr() const { return(_base_ptr); }
	reference operator*() const { return(_base_ptr->value); }
	pointer operator->() const { return (std::addressof(operator*())); }

	// returning _end_node as if it was max()->left, even though they are not linked.
	rb_iterator& operator++() {
		node_pointer tmp = rb_successor(_base_ptr);
		_base_ptr = (_base_ptr != _NIL && tmp == _NIL) ? _end_node : tmp;
		return(*this);
	}

	// to ensure that --end() == max(), two cases considered
	// rb_max(_end_node->left) should be == max(_root)
	rb_iterator& operator--() {
		_base_ptr = (_base_ptr == _end_node) ? rb_max(_end_node->left) : rb_predecessor(_base_ptr);
		return(*this);
	}

	rb_iterator operator++(int) { node_pointer old = _base_ptr; ++*this; return(rb_iterator(old)); }
	rb_iterator operator--(int) { node_pointer old = _base_ptr; --*this; return(rb_iterator(old)); }

	friend bool operator==(const rb_iterator& lhs, const rb_iterator& rhs)
		{ return(lhs.get_base_ptr() == rhs.get_base_ptr()); }
	friend bool operator!=(const rb_iterator& lhs, const rb_iterator& rhs)
		{ return(!(lhs == rhs)); }
};

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

class rb_const_iterator {
public:
	typedef bidirectional_iterator_tag				iterator_category;
	typedef typename rb_tree::value_type			value_type;
	typedef typename rb_tree::difference_type		difference_type;
	typedef typename rb_tree::const_reference		const_reference; // ! wrong
	typedef typename rb_tree::const_pointer			const_pointer; // ! wrong
private:
	rb_iterator _base_ite;
public:
	rb_const_iterator(): _base_ite() {}
	rb_const_iterator(const node_pointer& x): _base_ite(x) {}
	node_pointer get_base_ite() const { return(_base_ite); }
	node_pointer get_base_ptr() const { return(_base_ite.get_base_ptr()); }
	const_reference operator*() const { return(get_base_ptr()->value); }  // ????
	const_pointer operator->() const { return (std::addressof(operator*())); }  // ???? 'pointer to node ->'
	rb_const_iterator& operator++() { ++_base_ite; return(*this); }
	rb_const_iterator& operator--() { --_base_ite; return(*this); }
	rb_const_iterator operator++(int)
		{ node_pointer old = _base_ite; ++*this; return(rb_const_iterator(old)); }
	rb_const_iterator operator--(int)
		{ node_pointer old = _base_ite; --*this; return(rb_const_iterator(old)); }
	friend bool operator==(const rb_const_iterator& lhs, const rb_const_iterator& rhs)
		{ return(lhs.get_base_ptr() == rhs.get_base_ptr()); }
	friend bool operator!=(const rb_const_iterator& lhs, const rb_const_iterator& rhs)
		{ return(!(lhs == rhs)); }
};

// ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~    ~  

typedef rb_iterator			iterator;
typedef rb_const_iterator	const_iterator;


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// attributes - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

protected: // ?
static node_allocator_type	_node_allocator;
static value_allocator_type	_value_allocator;
static node_pointer			_NIL;
static node_pointer			_end_node;

private:
static size_type	_nb_trees;
node_pointer		_root;
size_type			_size;
value_compare		_comp; // ? needed ?


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// publilc member functions - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

public:

rb_tree(): _root(_NIL), _size(0) { //, _comp(Compare) {
	++_nb_trees;
}

explicit rb_tree(const Compare& c, const Allocator& alloc = Allocator()) // ?
	: _root(_NIL), _size(0), _comp(c) {
	_value_allocator = alloc;
	++_nb_trees;
}

~rb_tree() {
	_clear(_root);
	if (_nb_trees == 1)
		_end_node->__destroy();
		_NIL->__destroy();
	--_nb_trees;
}

// + cpy constr ?
// + operator= (for map cpy constr)

// accessors - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

bool empty() const { return (_root == _NIL); }
iterator NIL() const { return (iterator(_NIL)); }
size_type size() const { return (_size); }

node_pointer min() const { return (empty() ? NULL : rb_min(_root)); }
node_pointer max() const { return (empty() ? NULL : rb_max(_root)); }

node_pointer search(value_type value) const { return (_search(_root, value)); }

iterator begin() {return(iterator(min())); }
const_iterator begin() const {return(const_iterator(begin())); }
iterator end() { return(iterator(_end_node)); }
const_iterator end() const { return(const_iterator(end())); }

node_pointer successor(value_type value) const { return (rb_successor(search(value))); }
node_pointer predecessor(value_type value) const { return (rb_predecessor(search(value))); }

// modifiers - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/*
	INSERT VALUE
	Allocates a node containing the value given and inserts it ito the
	tree. Recoloring and rotation operations might be performed.
	Returns [...]
*/
iterator insert(value_type value) { // or iterator as return ?? -> then change also map insert
	std::cout << "inserting "<< std::endl;
	node_pointer x = _new_node(value);
	_tree_insert(x);
	++_size;
	return (x);
}

/*
	DELETE VALUE

	Seraches (in value overload) for a node containing the value given
	and removes it from the tree. Does nothing if the value was not found.
	Recoloring and rotation operations might be performed by _tree_delete()
*/
void erase(node_pointer z) {
	node_pointer tmp_z = z;
	_tree_delete(z);
	tmp_z->__destroy();
	--_size;
}

void erase(const_reference value) { //  necessary ?
	node_pointer z = search(value);
	if (!z || z == _NIL)
		return ;
	erase(z);
}

void erase(iterator pos) { // needed in map
	node_pointer z = pos.get_base_ptr();
	erase(z);
}

// lookup - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/*
	Prints tree (including _NIL nodes) horizontally. Example:
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

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// internal structure/ memory management  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
private:

// uses parametric constructor of node -> color == red, ptrs init to _NIL
node_pointer _new_node(value_type value) {
	node_pointer x = _node_allocator.allocate(1);
	_node_allocator.construct(x, value);
	return (x);
}

// uses dflt constr of node -> ptrs init to NULL, not _NIL. Used for _end_node & _NIL itself.
static node_pointer _new_node(bool isblack) {
	node_pointer x = _node_allocator.allocate(1);
	_node_allocator.construct(x, isblack);
	return (x);
}

// recursively destroys and frees the memory of all nodes of the subtree rooted in x.
void _clear(node_pointer x) {
	if (x != _NIL) {
		_clear(x->left);
		_clear(x->right);
		x->__destroy();
	}
	_size = 0;
}

// usage of value_compare as modular function for more control
bool _tree_compare(value_type& val1, value_type& val2) const {
	if (_comp(val1, val2))
		return (true);
	return (false);
}

/*
	SEARCH
	Searches for a node containing the value given in a (sub-)tree rooted
	in the passed node. Returns a pointer to the node found or _NIL
	if the tree was empty or no node was found.
*/
node_pointer _search(node_pointer x, value_type value) const {
	while (x != _NIL && value != x->value) {
		if (_tree_compare(value, x->value))
			x = x->left;
		else
			x = x->right;
	}
	return (x == _NIL ? NULL : x);
}

// (algorithms at end of file - these are member functions)
void _right_rotate(node_pointer x);
void _left_rotate(node_pointer x);
void _transplant(node_pointer u, node_pointer v);
void _tree_insert(node_pointer node);
void _tree_insert_fixup(node_pointer node);
void _tree_delete(node_pointer z);
void _tree_delete_fixup(node_pointer x);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// NON_MEMBER FUNCTIONS ('friend' for access to _NIL, in order to be used by iterators as well)

/*
	MAX
	Returns pointer to node with maximum value or _NIL if the tree
	is empty or the node passed was _NIL.
*/
friend node_pointer rb_max(node_pointer x) {
	while (x != _NIL && x->right != _NIL)
		x = x->right;
	return (x);
}

/*
	MIN
	Returns pointer to node with minimum value or _NIL if the tree
	is empty or the node passed was _NIL.
*/
friend node_pointer rb_min(node_pointer x) {
	while (x != _NIL && x->left != _NIL)
		x = x->left;
	return (x);
}

/*
	SUCCESSOR
	Returns a pointer to the node with the next greater value after x, else NULL.
	'y->parent != NULL' checks that y != _end_node indirectly
*/
friend node_pointer rb_successor(node_pointer x) {
	if (x == _NIL)
		return (_NIL);
	if (x->right != _NIL)
		return (rb_min(x->right));
	node_pointer y = x->parent;
	while (y != _NIL && y->parent != NULL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return (y == _end_node ? _NIL : y);
}

/*
	PREDECESSOR
	Returns a pointer to the node with the next smallest value before x, else NULL.
	'y->parent != NULL' checks that y != _end_node indirectly
*/
friend node_pointer rb_predecessor(node_pointer x) {
	if (x == _NIL)
		return (_NIL);
	if (x->left != _NIL)
		return (rb_max(x->left));
	node_pointer y = x->parent;
	while (y != _NIL && y->parent != NULL && x == y->left) {
		x = y;
		y = y->parent;
	}
	return (y == _end_node ? _NIL : y);
}

// debugging print function - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/* Recursive core of print_tree() */
void __pretty_print(std::string prefix, node_pointer x, bool isleft, int iter) const {
	++iter;
	if (x == _NIL) {
		std::cout << "\033[0;34m";
		std::cout << prefix;
		std::cout << (isleft ? "├──" : "└──");
		std::cout << iter;
		std::cout << (isleft ? "L " : "R ");
		std::cout << "\033[0m";
		std::cout << "⁙";
		std::cout << "\033[0;34m" << " " << x << "\033[0m";
		std::cout << std::endl;
	}
	if (x != _NIL) {
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
		std::cout << x->value << " " << "\033[0;34m" << x;
		// std::cout << x; // if no << overload
		std::cout << "\033[0m" << std::endl;
		__pretty_print(prefix + (isleft ? "│     " : "      "), x->left, true, iter);
		__pretty_print(prefix + (isleft ? "│     " : "      "), x->right, false, iter);
	}
}

}; // RB TREE ===========================================================================================

// static tree node allocator attribute definition:
template <class Value, class Compare, class Allocator>
	typename rb_tree<Value, Compare, Allocator>::node_allocator_type
	rb_tree<Value, Compare, Allocator>::_node_allocator;

// static tree value allocator attribute definition:
template <class Value, class Compare, class Allocator>
	typename rb_tree<Value, Compare, Allocator>::value_allocator_type
	rb_tree<Value, Compare, Allocator>::_value_allocator;

// static tree nil attribute definition:
template <class Value, class Compare, class Allocator>
	typename rb_tree<Value, Compare, Allocator>::node_pointer
		rb_tree<Value, Compare, Allocator>::_NIL = _new_node(true);

// static tree nil attribute definition:
template <class Value, class Compare, class Allocator>
	typename rb_tree<Value, Compare, Allocator>::node_pointer
		rb_tree<Value, Compare, Allocator>::_end_node = _new_node(false);

// static tree instance counter _nb_trees attribute definition:
template <class Value, class Compare, class Allocator>
	typename rb_tree<Value, Compare, Allocator>::size_type
		rb_tree<Value, Compare, Allocator>::_nb_trees = 0;

// tree node ALGORITHMS (member functions) ==============================================================

/* ---------------
	ROTATIONS
------------------
X, Y are nodes, a,b, and c subtrees (either nodes, _NIL, or branching subtrees)
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
	Right-rotates a node assuming node->right != _NIL
	and the root's parent is _end_node
*/
template <class Value, class Compare, class Allocator>
void rb_tree<Value, Compare, Allocator>::_left_rotate(node_pointer x) {
	node_pointer y = x->right;
	x->right = y->left;
	if (y->left != _NIL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == _end_node)
		_root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

/*
	Right-rotates a node assuming node->left != _NIL
	and the root's parent is _end_node
*/
template <class Value, class Compare, class Allocator>
void rb_tree<Value, Compare, Allocator>:: _right_rotate(node_pointer x) {
	node_pointer y = x->left;
	x->left = y->right;
	if (y->right != _NIL)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == _end_node)
		_root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;
	y->right = x;
	x->parent = y;
}

/* ---------------
	TRANSPLANT
--------------- */

/*
	Replaces subtree rooted at node u with subtree rooted at node v.
	Does not update v->left and v->right.
*/
template <class Value, class Compare, class Allocator>
void rb_tree<Value, Compare, Allocator>::_transplant(node_pointer u, node_pointer v) {
	if (u->parent == _end_node)
		_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

/* ---------------
	INSERTION
--------------- */
/*
	Inserts nodes following standard binary search tree insertion routine
	afterwards calling _tree_insert_fixup to restore red-black properties.
*/
template <class Value, class Compare, class Allocator>
void rb_tree<Value, Compare, Allocator>::_tree_insert(node_pointer node) {
	node_pointer y = _NIL;
	node_pointer x = _root;
	while (x != _NIL) {
		y = x;
		x = (_tree_compare(node->value, x->value)) ? x->left : x->right;
	}
	node->parent = y;
	if (y == _NIL) {
		_root = node;
		node->parent = _end_node;
		_end_node->left = _root;
		_end_node->right = _root;
		_root->isblack = true;
	}
	else {
		if (_tree_compare(node->value, y->value))
			y->left = node;
		else
			y->right = node;
		_tree_insert_fixup(node);
	}
}

/*
	Performs recoloring and rotations to rebalance the tree and restore
	red-black properties after insertion.
*/
template <class Value, class Compare, class Allocator>
void rb_tree<Value, Compare, Allocator>::_tree_insert_fixup(node_pointer x) {
	node_pointer y;
	while (x != _root && !x->parent->isblack) {
	/* CASES A: px is left child of ppx */
		if (x->parent == x->parent->parent->left) {
			y = x->parent->parent->right;
			/* CASE 1: uncle is red (& not _NIL, same cond because _NIL->isblack = true) */
			if (!y->isblack) {
				x = x->parent;
				x->isblack = true;
				x = x->parent;
				x->isblack = (x == _root);
				y->isblack = true;
			}
			/* CASE 2+3: uncle is black (or _NIL) */
			else {
				/* CASE 2: x is right child */
				if (x == x->parent->right) {
					x = x->parent;
					_left_rotate(x);
				}
				/* CASE 3 */
				x->parent->isblack = true;
				x->parent->parent->isblack = false;
				x = x->parent->parent;
				_right_rotate(x);
				break ;
			}
		}
	/* CASES B: px is left child of ppx */
		else {
			y = x->parent->parent->left;
			/* CASE 1: uncle is red (& not null, same cond because _NIL->isblack = true) */
			if (!y->isblack) {
				x = x->parent;
				x->isblack = true;
				x = x->parent;
				x->isblack = (x == _root);
				y->isblack = true;
			}
			/* CASE 2+3: uncle is black (or _NIL) */ 
			else {
				/* CASE 2: x is left child */
				if (x == x->parent->left) {
					x = x->parent;
					_right_rotate(x);
				}
				/* CASE 3 */
				x->parent->isblack = true;
				x->parent->parent->isblack = false;
				x = x->parent->parent;
				_left_rotate(x);
				break ;
			}
		}
	}
}

/* ---------------
	DELETION
--------------- */
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
template <class Value, class Compare, class Allocator>
void rb_tree<Value, Compare, Allocator>::_tree_delete(node_pointer z) {
	node_pointer fixup_pivot;
	bool was_black = z->isblack;
	if (z->left == _NIL) {
		fixup_pivot = z->right;
		_transplant(z, z->right);
	}
	else if (z->right == _NIL) {
		fixup_pivot = z->left;
		_transplant(z, z->left);
	}
	else {
		node_pointer y = rb_min(z->right);
		was_black = y->isblack;
		fixup_pivot = y->right;
		if (y->parent == z)
			/* pivot can be _NIL, storing p info for fixup */
			fixup_pivot->parent = y;
		else {
			_transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		_transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->isblack = z->isblack;
	}
	if (was_black && _root != _NIL)
		_tree_delete_fixup(fixup_pivot);
}

/*
	Deletion fixup recoloring and rotation routine to restore
	red-black properties of the tree.
*/
template <class Value, class Compare, class Allocator>
void rb_tree<Value, Compare, Allocator>::_tree_delete_fixup(node_pointer x) {
	node_pointer y; /* sibling of x */
	while (x != _root && x->isblack) {
	/* CASES A: x is left child, sibling y is right child */
		if (x == x->parent->left) {
			y = x->parent->right;
			/* CASE 1: sibling y is red. Goes into case 2/3/4. */
			if (!y->isblack) {
				y->parent->isblack = false;
				y->isblack = true;
				_left_rotate(y->parent);
				if (_root == y->left)
					_root = y;
				y = y->left->right;
			}
			/* CASE 2: y is black and both childern are black */
			if (y->left->isblack && y->right->isblack) {
				y->isblack = false;
				x = y->parent;
				// if (x == _NIL->isblack || x == _root) {
				// 	x->isblack = true;
				// 	break ;
				// }
				// if (y == x->left)
				// 	y = x->parent->right;
				// else
				// 	y = x->parent->left;
			}
			else {
				/* CASE 3(+4): y is black and only right child is black */
				if (!y->right->isblack && y->right != _NIL) {
					y->left->isblack = true;
					y->isblack = false;
					_right_rotate(y);
					y = y->parent;
				}
				/* CASE 4: y is black and only right child is black */
				y->isblack = x->parent->isblack;
				y->parent->isblack = true;
				y->right->isblack = true;
				_left_rotate(y->parent);
				break ;
			}
		}
	/* CASES B: x is right child, sibling y is left child */
		else {
			y = x->parent->left;
			/* CASE 1: sibling y is red. Goes into case 2/3/4. */
			if (!y->isblack) {
				y->parent->isblack = false;
				y->isblack = true;
				_right_rotate(y->parent);
				if (_root == y->right)
					_root = y;
				y = y->right->left;
			}
			/* CASE 2: y is black and both childern are black */
			if (y->left->isblack && y->right->isblack) {
				y->isblack = false;
				x = y->parent;
				// if (x == _NIL->isblack || x == _root) {
				// 	x->isblack = true;
				// 	break ;
				// }
				// if (y == x->left)
				// 	y = x->parent->right;
				// else
				// 	y = x->parent->left;
			}
			else {
				/* CASE 3(+4): y is black and only right child is black */
				if (y->left->isblack || y->left == _NIL) {
					y->right->isblack = true;
					y->isblack = false;
					_left_rotate(y);
					y = y->parent;
				}
				/* CASE 4: y is black and only right child is black */
				y->isblack = y->parent->isblack;
				y->parent->isblack = true;
				y->left->isblack = true;
				_right_rotate(y->parent);
				break ;
			}
		}
	}
	x->isblack = true;
}

} /* NAMESPACE FT end ------------------------------------------------------*/

#endif // _FTRB_TREE_HPP_

#undef DBG_ME
