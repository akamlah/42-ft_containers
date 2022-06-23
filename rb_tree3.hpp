/* ------------------------------- CONTENTS ----------------------------------

CLASS rb_tree_iterator
CLASS rb_tree_const_iterator

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

---------------
RED BLACK TREE
---------------

public member types:

	value_type
	compare_type
	value_allocator_type
	pointer
	reference
	const_reference
	iterator
	const_iterator
	node_allocator_type
	node_pointer
	size_type
	difference_type


public member functions:

	rb_tree();
	~rb_tree();
	node_pointer insert(value_type value);
	void erase(const_reference value);

	bool empty() const;
	node_pointer min() const;
	node_pointer max() const;
	iterator begin() const;
	iterator end() const;										?????????
	node_pointer search(value_type value) const;
	node_pointer successor(value_type value) const;
	node_pointer predecessor(value_type value) const;

	void print_tree() const;									// DEBUG

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

NODE POINTER ALGORITHMS

	template <class NodePointer> NodePointer rb_min(NodePointer x);
	template <class NodePointer> NodePointer rb_max(NodePointer x);
	template <class NodePointer, typename T> NodePointer rb_search(NodePointer x, T value);
	template <class NodePointer> NodePointer rb_successor(NodePointer x);
	template <class NodePointer> NodePointer rb_predecessor(NodePointer x);
	template <class NodePointer> void rb_left_rotate(NodePointer& root, NodePointer x);
	template <class NodePointer> void rb_right_rotate(NodePointer& root, NodePointer x);
	template <class NodePointer> NodePointer rb_transplant(NodePointer& root, NodePointer u, NodePointer v);
	template <class NodePointer> void rb_insert(NodePointer& root, NodePointer node);
	template <class NodePointer> void rb_insert_fixup(NodePointer& root, NodePointer x);
	template <class NodePointer> void rb_delete(NodePointer& root, NodePointer z);
	template <class NodePointer> void rb_delete_fixup(NodePointer& root, NodePointer x);
	template <class NodePointer> void print_tree(NodePointer root);

--------------------------------------------------------------------------- */

#ifndef FT_RB_TREE
# define FT_RB_TREE

#include "iterator.hpp"
// leaves point to null.
// root s.t. p = 0
// node pointer algorithms separately.
#include <map>

namespace ft { /* NAMESPACE FT */

template <class, class, class> class rb_tree;

// tree node algorithms (end of page) - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <class NodePointer> NodePointer rb_min(NodePointer x);
template <class NodePointer> NodePointer rb_max(NodePointer x);
template <class NodePointer, typename T> NodePointer rb_search(NodePointer x, T value);
template <class NodePointer> NodePointer rb_successor(NodePointer x);
template <class NodePointer> NodePointer rb_predecessor(NodePointer x);
template <class NodePointer> void rb_left_rotate(NodePointer& root, NodePointer x);
template <class NodePointer> void rb_right_rotate(NodePointer& root, NodePointer x);
template <class NodePointer> NodePointer rb_transplant(NodePointer& root, NodePointer u, NodePointer v);
template <class NodePointer> void rb_insert(NodePointer& root, NodePointer node);
template <class NodePointer> void rb_insert_fixup(NodePointer& root, NodePointer x);
template <class NodePointer> void rb_delete(NodePointer& root, NodePointer z);
template <class NodePointer> void rb_delete_fixup(NodePointer& root, NodePointer x);
template <class NodePointer> void print_tree(NodePointer root);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template <class Value, class Compare, class Allocator>
class rb_tree_iterator {
public:
	typedef rb_tree<Value, Compare, Allocator>	tree_type;
	typedef bidirectional_iterator_tag			iterator_category;
	typedef typename tree_type::value_type		value_type;
	typedef typename tree_type::difference_type	difference_type;
	typedef typename tree_type::reference		reference;
	typedef typename tree_type::pointer			pointer;
	typedef typename tree_type::node_pointer	node_pointer;
private:
	node_pointer _node_ptr;
public:
	rb_tree_iterator(const node_pointer& x): _node_ptr(x) {}
	rb_tree_iterator(const rb_tree_iterator& other): _node_ptr(other.get_node_ptr()) {}

	rb_tree_iterator& operator=(const rb_tree_iterator& other)
		{ _node_ptr = other._node_ptr; return(*this); }
	node_pointer get_node_ptr() const { return(_node_ptr); }
	reference operator*() const { return(_node_ptr->value); }
	pointer operator->() const { return (std::addressof(operator*())); }
	// OR
	// {return pointer_traits<pointer>::pointer_to(get_node_ptr()->__value_);}
	// ?

	rb_tree_iterator& operator++() { _node_ptr = rb_successor(_node_ptr); return (*this); }
	rb_tree_iterator& operator--() { _node_ptr = rb_predecessor(_node_ptr); return (*this); }
	rb_tree_iterator operator++(int) { rb_tree_iterator old = *this;
		_node_ptr = rb_successor(_node_ptr); return (old); }
	rb_tree_iterator operator--(int) { rb_tree_iterator old = *this;
		_node_ptr = rb_predecessor(_node_ptr); return (old); }
	
	friend bool operator==(const rb_tree_iterator& lhs, const rb_tree_iterator& rhs)
		{ return(lhs.get_node_ptr() == rhs.get_node_ptr()); }
	friend bool operator!=(const rb_tree_iterator& lhs, const rb_tree_iterator& rhs)
		{ return(!(lhs == rhs)); }
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Value, class Compare, class Allocator>
class rb_tree_const_iterator { // ??????????????????????????????????????????????????????????????????????
public:
	typedef rb_tree<Value, Compare, Allocator>			tree_type;
	typedef rb_tree_iterator<Value, Compare, Allocator>	non_const_ite_type;
	typedef bidirectional_iterator_tag					iterator_category;
	typedef typename tree_type::value_type				value_type;
	typedef typename tree_type::difference_type			difference_type;
	typedef typename tree_type::const_reference			const_reference;
	typedef typename tree_type::const_pointer			const_pointer;
	typedef typename tree_type::node_pointer			node_pointer;
private:
	node_pointer _node_ptr;
public:
	rb_tree_const_iterator(const node_pointer& x): _node_ptr(x) {}
	rb_tree_const_iterator(const non_const_ite_type& ite): _node_ptr(ite.get_node_ptr()) {}
	rb_tree_const_iterator(const rb_tree_const_iterator& other): _node_ptr(other.get_node_ptr()) {}

	rb_tree_const_iterator& operator=(const rb_tree_const_iterator& other)
		{ _node_ptr = other._node_ptr; return(*this); }
	node_pointer get_node_ptr() const { return(_node_ptr); }

	const_reference operator*() const { return(_node_ptr->value); }
	const_pointer operator->() const { return (std::addressof(operator*())); } // or ptr_to ?

	rb_tree_const_iterator& operator++() { _node_ptr = rb_successor(_node_ptr); return (*this); }
	rb_tree_const_iterator& operator--() { _node_ptr = rb_predecessor(_node_ptr); return (*this); }
	rb_tree_const_iterator operator++(int) { rb_tree_const_iterator old = *this;
		_node_ptr = rb_successor(_node_ptr); return (old); }
	rb_tree_const_iterator operator--(int) { rb_tree_const_iterator old = *this;
		_node_ptr = rb_predecessor(_node_ptr); return (old); }
	
	friend bool operator==(const rb_tree_const_iterator& lhs, const rb_tree_const_iterator& rhs)
		{ return(lhs->get_node_ptr() == rhs->get_node_ptr()); }
	friend bool operator!=(const rb_tree_const_iterator& lhs, const rb_tree_const_iterator& rhs)
		{ return(!(lhs == rhs)); }
}; // ??????????????????????????????????????????????????????????????????????????????????????????????????

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/* ---------------------
	RED BLACK TREE
--------------------- */

template <	class T,
			class Compare = typename std::map<int, T>::key_compare,
			class Allocator = std::allocator<T> > // ?????????????? or free here and pass in map?
class rb_tree { // red black tree //

// member types, member classes, attributes. -------------------------------------------------------------

public:

typedef T												value_type;
typedef Compare											compare_type;
typedef Allocator										value_allocator_type;
typedef typename value_allocator_type::pointer			pointer;
typedef typename value_allocator_type::reference		reference;
typedef typename value_allocator_type::const_reference	const_reference;
typedef rb_tree_iterator<T, Compare, Allocator>			iterator;
typedef rb_tree_const_iterator<T, Compare, Allocator>	const_iterator;

private:

struct rb_node { // red black nodes
	struct rb_node* parent;
	struct rb_node* left;
	struct rb_node* right;
	value_type value;
	bool isblack;
	rb_node(): parent(NULL), left(NULL), right(NULL), isblack(false) {}
	rb_node(value_type val): parent(NULL), left(NULL), right(NULL), value(val), isblack(false) {}
	rb_node(const rb_node& other): parent(NULL), left(NULL), right(NULL), value(other.value), isblack(false) {}
	virtual ~rb_node() {}
	rb_node& operator=(const rb_node& other) {
			value = other.value; parent = other.parent; 
			left = other.left; right = other.right; isblack = other.isblack;
			return (*this);
	} // ?
};

public:

typedef typename value_allocator_type::template rebind<rb_node>::other	node_allocator_type;
typedef typename node_allocator_type::pointer							node_pointer;
typedef typename node_allocator_type::size_type							size_type;
typedef typename node_allocator_type::difference_type					difference_type;

private:

static node_allocator_type	_node_allocator;
static value_allocator_type	_value_allocator;
node_pointer	_detatched_node;
node_pointer	_root;
size_type		_size;

// member functions ------------------------------------------------------------------------------------

public: // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

rb_tree(): _root(NULL), _detatched_node(_new_node()), _size(0) {std::cout << "here" << std::endl;
}

~rb_tree() {
	_clear(_root);
	_node_allocator.destroy(_detatched_node);
	_node_allocator.deallocate(_detatched_node, 1);
}

node_pointer insert(value_type value) { // or iterator as return ?? -> then change also map insert
	std::cout << "INSERTING " << &value << std::endl;

	node_pointer x = _new_node(value);
	rb_insert(_root, x);
		std::cout << "done insert 0" << std::endl;
	++_size;
	_detatched_node->parent = max();
	return (x);
}

void erase(const_reference value) {
	std::cout << "DELETING " << value << std::endl;
	node_pointer z = rb_search(_root, value);
	if (z == NULL)
		return ;
	node_pointer tmp_z = z;

	// rb_delete(_root, z);			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	__tree_remove(_root, z);

	_node_allocator.destroy(tmp_z);
	_node_allocator.deallocate(tmp_z, 1);
	--_size;
}

bool empty() const { return (_root == NULL); }
size_type size() const { return (_size); }
node_pointer min() const { return (rb_min(_root)); }
node_pointer max() const { return (rb_max(_root)); }
iterator begin() const {return(iterator(min())); }
iterator end() const { return(iterator(_detatched_node)); } // ? i mean, works perfectly in loops until it != end()...
node_pointer search(value_type value) const { return (rb_search(_root, value)); }
node_pointer successor(value_type value) const
	{ return (rb_successor<node_pointer>(search(value))); }
node_pointer predecessor(value_type value) const
	{ return (rb_predecessor<node_pointer>(search(value))); }

private: // internal structure/ memory management  - - - - - - - - - - - - - - - - - - - - - - - - - -  -

node_pointer _new_node(value_type value) {
	node_pointer x = _node_allocator.allocate(1);
	_node_allocator.construct(x, value);
	return (x);
}

node_pointer _new_node(void) {
	std::cout << "here4" << std::endl;

	node_pointer x = _node_allocator.allocate(1);
	_node_allocator.construct(x);
	return (x);
}

// recursively destroys and frees the memory of all nodes of the subtree rooted in x.
void _clear(node_pointer x) {
	if (x) {
		// std::cout << "clear | " << x->value << std::endl;
		_clear(x->left);
		_clear(x->right);
		_node_allocator.destroy(x);
		_node_allocator.deallocate(x, 1);
	}
	_size = 0;
}

// fancy print function -------------------------------------------------------------------------------
public:
	/* Prints tree (including NULL leaves) horizontally. Example:
	└──0* 8
	    ├──1L 3
	    │     ├──2L ⁙
	    │     └──2R ⁙
	    └──1R 99
	            ├──2L ⁙
	            └──2R ⁙    */
	void print_tree() const {
		::ft::print_tree(_root);
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


// instance indipendent tree node ALGORITHMS =============================================================

// queries - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - 

// Returns min of subtree rooted in x, NULL if x was NULL.
template <class NodePointer>
NodePointer rb_min(NodePointer x) {
	while (x && x->left) {
		std::cout << "min while" << std::endl;
		x = x->left;
	}
	return (x);
}

// Returns max of subtree rooted in x, NULL if x was NULL.
template <class NodePointer>
NodePointer rb_max(NodePointer x) {
	while (x && x->right) {
		// std::cout << "max while" << std::endl;
		x = x->right;
	}
	return (x);
}

// Returns pointer to node containing value 'value' in subtree<T> rooted in x, else NULL.
template <class NodePointer, typename T>
NodePointer rb_search(NodePointer x, T value) {
	while (x && value != x->value) {
		if (value < x->value)
			x = x->left;
		else
			x = x->right;
	}
	return (x);
}

// Returns a pointer to the node with the next greater value after x, else NULL.
template <class NodePointer>
NodePointer rb_successor(NodePointer x) {
	if (!x)
		return (NULL);
	if (x->right)
		return (rb_min(x->right));
	NodePointer y = x->parent;
	while (y && x == y->right) {
		x = y;
		y = y->parent;
	}
	return (y);
}

// Returns a pointer to the node with the next smallest value before x, else NULL.
template <class NodePointer>
NodePointer rb_predecessor(NodePointer x) {
	if (!x)
		return (NULL);
	if (x->left)
		return (rb_max(x->left));
	NodePointer y = x->parent;
	while (y && x == y->left) {
		x = y;
		y = y->parent;
	}
	return (y);
}

// modeifiers - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - -

template <class NodePointer>
void rb_left_rotate(NodePointer& root, NodePointer x) {
	NodePointer y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

template <class NodePointer>
void rb_right_rotate(NodePointer& root, NodePointer x) {
	NodePointer y = x->left;
	x->left = y->right;
	if (y->right != NULL)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;
	y->right = x;
	x->parent = y;
}

template <class NodePointer>
NodePointer rb_transplant(NodePointer& root, NodePointer u, NodePointer v) {
	std::cout << "TRANSPLANT | u:" << u << " v:" << v << std::endl; // !
	if (!u->parent)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v)
		v->parent = u->parent;
	return u;
}

/* ---------------
	INSERTION
--------------- */

template <class NodePointer>
void rb_insert(NodePointer& root, NodePointer node) {
	NodePointer y = NULL;
	NodePointer x = root;
	while (x != NULL) {
		y = x;
		if (node->value < x->value)
			x = x->left;
		else
			x = x->right;
	}
	node->parent = y;
	if (y == NULL) {
		root = node;
		root->isblack = true;
	}
	else {
		if (node->value < y->value)
			y->left = node;
		else
			y->right = node;
		rb_insert_fixup(root, node);
	}
}

template <class NodePointer>
void rb_insert_fixup(NodePointer& root, NodePointer x) {
	NodePointer y;
	while (x != root && x->parent && !x->parent->isblack ) {
	/* CASES A: px is left child of ppx */
		if (x->parent == x->parent->parent->left) {
			y = x->parent->parent->right;
			/* CASE 1: uncle is red (& not NULL, same cond because NULL->isblack = true) */
			if (y && !y->isblack) {
				x = x->parent;
				x->isblack = true;
				x = x->parent;
				x->isblack = (x == root);
				y->isblack = true;
			}
			/* CASE 2+3: uncle is black (or NULL) */
			else {
				/* CASE 2: x is right child */
				if (x == x->parent->right) {
					x = x->parent;
					rb_left_rotate(root, x);
				}
				/* CASE 3 */
				x->parent->isblack = true;
				x->parent->parent->isblack = false;
				x = x->parent->parent;
				rb_right_rotate(root, x);
				break ;
			}
		}
	/* CASES B: px is left child of ppx */
		else {
			y = x->parent->parent->left;
			/* CASE 1: uncle is red (& not null, same cond because NULL->isblack = true) */
			if (y && !y->isblack) {
				x = x->parent;
				x->isblack = true;
				x = x->parent;
				x->isblack = (x == root);
				y->isblack = true;
			}
			/* CASE 2+3: uncle is black (or NULL) */ 
			else {
				/* CASE 2: x is left child */
				if (x == x->parent->left) {
					x = x->parent;
					rb_right_rotate(root, x);
				}
				/* CASE 3 */
				x->parent->isblack = true;
				x->parent->parent->isblack = false;
				x = x->parent->parent;
				rb_left_rotate(root, x);
				break ;
			}
		}
	}
}

/* ---------------
	DELETION
--------------- */

template <class NodePointer> // buggy - to solve. in the meantime use __tree_remove from the STL
void rb_delete(NodePointer& root, NodePointer z) {
	NodePointer y = z; // silbling
	NodePointer x; // moves into node y's original position
	bool y_was_black = y->isblack;
	if (!z->left) {
		// std::cout << "rb_delete | case z-left == null" << std::endl;
		x = z->right;
		rb_transplant(root, z, z->right);
	}
	else if (!z->right) {
		// std::cout << "rb_delete | case z-left == null" << std::endl;
		x = z->left;
		rb_transplant(root, z, z->left);
	}
	else {
		// std::cout << "rb_delete | case 2 children" << std::endl;

		y = rb_min(z->right);
		// std::cout << "min is " << y->value << std::endl;
		y_was_black = y->isblack;
		x = y->right;

		// if (y->parent == z)
		// 	x->parent = y; // x could be null -> segv
		// else {
		// 	rb_transplant(root, y, y->right);
		// 	y->right = z->right;
		// 	y->right->parent = y;
		// }

		if (y->parent != z) {
			rb_transplant(root, y, y->right);
			y->right = z->right;
			y->right->parent = y;
			// print_tree(root);
		}

		rb_transplant(root, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->isblack = z->isblack;
	}

	std::cout << "=================================" << std::endl;
	std::cout << "after BST delete" << std::endl;
	print_tree(root);
	std::cout << "=================================" << std::endl;

	if (y_was_black)
		rb_delete_fixup(root, x);
}

template <class NodePointer>
void rb_delete_fixup(NodePointer& root, NodePointer x) {
	NodePointer y; // sibling of x
	while (x != root && x && x->isblack) { // CASES A: x is left child, sibling y is right child
		if (x == x->parent->left) {
			y = x->parent->right;
			if (y && !y->isblack) { // CASE 1: sibling y is red. Goes into case 2/3/4.
				y->parent->isblack = false;
				y->isblack = true;
				rb_left_rotate(root, y->parent);
				if (root == y->left)
					root = y;
				y = y->left->right;
			}
			if (y->left->isblack && y->right->isblack) { // CASE 2: y is black and both childern are black
				y->isblack = false;
				x = y->parent;

				if (!x->isblack || x == root) {
					x->isblack = true;
					break ;
				}
				if (y == x->left)
					y = x->parent->right;
				else
					y = x->parent->left;

			}
			else { // CASE 3(+4): y is black and only right child is black
				if (!y->right->isblack && y->right != NULL) {
					y->left->isblack = true;
					y->isblack = false;
					rb_right_rotate(root, y);
					y = y->parent;
				}
				// CASE 4: y is black and only right child is black
				y->isblack = x->parent->isblack;
				y->parent->isblack = true;
				y->right->isblack = true;
				rb_left_rotate(root, y->parent);
				break ;
			}
		}
		else { // CASES B: x is right child, sibling y is left child
			y = x->parent->left;
			if (y && !y->isblack) { // CASE 1: sibling y is red. Goes into case 2/3/4.
				y->parent->isblack = false;
				y->isblack = true;
				rb_right_rotate(root, y->parent);
				if (root == y->right)
					root = y;
				y = y->right->left;
			}
			if (y->left->isblack && y->right->isblack) { // CASE 2: y is black and both childern are black
				y->isblack = false;
				x = y->parent;

				if (!x->isblack || x == root) {
					x->isblack = true;
					break ;
				}
				if (y == x->left)
					y = x->parent->right;
				else
					y = x->parent->left;

			}
			else { // CASE 3(+4): y is black and only right child is black
				if (y->left && y->right /* ? */ && y->left->isblack) {
					y->right->isblack = true;
					y->isblack = false;
					rb_left_rotate(root, y);
					y = y->parent;
				}
				// CASE 4: y is black and only right child is black
				y->isblack = y->parent->isblack;
				y->parent->isblack = true;
				y->left->isblack = true;
				rb_right_rotate(root, y->parent);
				break ;
			}
		}
	}
	if (x)
		x->isblack = true;
}

template <class NodePointer>
void
__tree_remove(NodePointer root, NodePointer z)
{
	NodePointer y = (z->left == NULL || z->right == NULL) ?
		z : rb_successor<NodePointer>(z);
	NodePointer x = y->left != NULL ? y->left : y->right;
	NodePointer w = NULL;
	if (x != NULL)
		x->parent = y->parent;
	if (y && y->parent && y->parent->left == y) {
		y->parent->left = x;
		if (y != root)
			w = y->parent->right;
		else
			root = x;
	}
	else {
		y->parent->right = x;
		w = y->parent->left;
	}
	bool removed_black = y->isblack;
	if (y != z) {
		y->parent = z->parent;
		if (z && z->parent && z->parent->left == z)
			y->parent->left = y;
		else
			y->parent->right = y;
		y->left = z->left;
		y->left->parent = y;
		y->right = z->right;
		if (y->right != NULL)
			y->right->parent = y;
		y->isblack = z->isblack;
		if (root == z)
			root = y;
	}

	std::cout << "=================================" << std::endl;
	std::cout << "after BST delete" << std::endl;
	print_tree(root);
	std::cout << "=================================" << std::endl;

	if (removed_black && root != NULL) {
		if (x != NULL)
			x->isblack = true;
		else {
			while (true) {
				if (!(w && w->parent && w->parent->left == w)) {
					if (!w->isblack) {
						w->isblack = true;
						w->parent->isblack = false;
						rb_left_rotate(root, w->parent);
						if (root == w->left)
							root = w;
						w = w->left->right;
					}
					if ((w->left  == NULL || w->left->isblack) &&
						(w->right == NULL || w->right->isblack)) {
						w->isblack = false;
						x = w->parent;
						if (x == root || !x->isblack) {
							x->isblack = true;
							break;
						}
						w = (w && w->parent && w->parent->left == w) ?
									x->parent->right :
									x->parent->left;
					}
					else {
						if (w->right == NULL || w->right->isblack) {
							w->left->isblack = true;
							w->isblack = false;
							rb_right_rotate(root, w);
							w = w->parent;
						}
						w->isblack = w->parent->isblack;
						w->parent->isblack = true;
						w->right->isblack = true;
						rb_left_rotate(root, w->parent);
						break;
					}
				}
				else {
					if (!w->isblack) {
						w->isblack = true;
						w->parent->isblack = false;
						rb_right_rotate(root, w->parent);
						if (root == w->right)
							root = w;
						w = w->right->left;
					}
					if ((w->left  == NULL || w->left->isblack) &&
						(w->right == NULL || w->right->isblack)) {
						w->isblack = false;
						x = w->parent;
						if (!x->isblack || x == root) {
							x->isblack = true;
							break;
						}
						w = (x && x->parent && x->parent->left == x) ?
								   x->parent->right :
									x->parent->left;
					}
					else {
						if (w->left == NULL || w->left->isblack) {
							w->right->isblack = true;
							w->isblack = false;
							rb_left_rotate(root, w);
							w = w->parent;
						}
						w->isblack = w->parent->isblack;
						w->parent->isblack = true;
						w->left->isblack = true;
						rb_right_rotate(root, w->parent);
						break;
					}
				}
			}
		}
	}
}

// PRINT ----------------------------------------------------------------------------------------------

template <class NodePointer>
static void _pretty_print(std::string prefix, NodePointer x, bool isleft, int iter);

template <class NodePointer>
void print_tree(NodePointer root) {
	_pretty_print("", root, false, -1);
	std::cout << std::endl;
}

template <class NodePointer>
static void _pretty_print(std::string prefix, NodePointer x, bool isleft, int iter) {
	++iter;
	if (x == NULL) {
		std::cout << "\033[0;34m"; // blue
		std::cout << prefix;
		std::cout << (isleft ? "├──" : "└──");
		std::cout << iter;
		std::cout << (isleft ? "L " : "R ");
		std::cout << "\033[0m"; // no color
		std::cout << "⁙";
		std::cout << std::endl;
	}
	if (x != NULL) {
		std::cout << "\033[0;34m"; // blue
		std::cout << prefix;
		if (iter == 0) {
			std::cout << "└──";
			std::cout << iter << "* ";
		}
		else {
			std::cout << (isleft ? "├──" : "└──");
			std::cout << iter;
			std::cout << (isleft ? "L " : "R ");
		}
		std::cout << "\033[0m"; // no color
		if (x->isblack == false)
			std::cout << "\033[0;31m"; // red
		std::cout << x->value;
		/* un-/comment to print/not print node's addresses */
			std::cout << " " << "\033[0;34m" << x; // blue
		std::cout << "\033[0m" << std::endl; // no color
		_pretty_print(prefix + (isleft ? "│     " : "      "), x->left, true, iter);
		_pretty_print(prefix + (isleft ? "│     " : "      "), x->right, false, iter);
	}
}

// -----------------------------------------------------------------------------------------------------

} /* NAMESPACE FT */

#endif // FT_RB_TREE
