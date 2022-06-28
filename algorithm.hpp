/* ************************************************************************ */
/*																			*/
/*							ft:: ALGORITHM									*/
/*																			*/
/* ************************************************************************ */

#ifndef _LIBFT_ALGORITHM_H_
# define _LIBFT_ALGORITHM_H_

namespace ft {
/* CONTENTS ------------------------------------------------------------------
equal
lexographically compare 
swap ?
--------------------------------------------------------------------------- */

// Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).
// 1) Elements are compared using operator<
template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 ) {
	InputIt1 it1 = first1;
	InputIt2 it2 = first2;
	while (*it1 == *it2 && it1 != last1) {
		++it1;
		++it2;
	}
	if ((*it1 == *it2 && it2 != last2)
		|| (it1 != last1 && *it1 < *it2)
		|| (*it1 < *it2 && it2 != last2))
		return (true);
	return (false);
}

template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp );

template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 ) {
	InputIt1 it1 = first1;
	InputIt2 it2 = first2;
	while (1) {
		if (!(*it1 == *it2))
			return (false);
		if (it1 == last1)
			break ; // could be lase nut l2 not last -> check comparison before
		it1++;
		it2++;
	}
	return (true);
}

// template< class InputIt1, class InputIt2, class BinaryPredicate >
// bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p );

} // NAMESPACE FT
#endif // _LIBFT_ALGORITHM_H_
