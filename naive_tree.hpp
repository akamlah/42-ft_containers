/* ************************************************************************ */
/*																			*/
/*								ft:: MAP									*/
/*																			*/
/* ************************************************************************ */
/* ------------------------------- CONTENTS ----------------------------------
--------------------------------------------------------------------------- */

#ifndef _FT_NAIVE_TREE_HPP_
# define _FT_NAIVE_TREE_HPP_

namespace ft { /* NAMESPACE FT */

template <class _Tp, class _Allocator = std::allocator<_Tp> >
class Tree
{
	struct node {
		node* p;
		node* left;
		node* right;
		_Tp value;
		bool color;
	};

	node* nil;
	node* root;

public:

	Tree() {

	}

	node* new_node() {
		node* new_node = new node();
		new_node.value = 
	}

}; /* _TREE */

/* - end TREE ------------------------------------------------------------- */

} /* NAMESPACE FT end ------------------------------------------------------*/

#endif // _FT_NAIVE_TREE_HPP_

#undef RED
#undef BLACK
