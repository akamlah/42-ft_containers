/* ************************************************************************ */
/*																			*/
/*							ft:: ALGORITHM									*/
/*																			*/
/* ************************************************************************ */

/* CONTENTS -------------------------------------------------------------------------------------------

LEXICOGRAPHICAL COMPARE:

	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 );

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp );


EQUAL

	template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 );

	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p );

---------------------------------------------------------------------------------------------------- */

#ifndef _FT_ALGORITHM_H_
# define _FT_ALGORITHM_H_

namespace ft {

// Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).
// Elements are compared using operator<
template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 ) {
	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
		if (*first1 < *first2)
			return (true);
		if (*first2 < *first1)
			return (false);
	}
	return (first1 == last1) && (first2 != last2);
}

// Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).
// Elements are compared using custom comp
template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp ) {
	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
		if (comp(*first1, *first2))
			return (true);
		if (comp(*first2, *first1))
			return (false);
	}
	return (first1 == last1) && (first2 != last2);
}


// Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)),
// and false otherwise
template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 ) {
	InputIt1 it1 = first1;
	InputIt2 it2 = first2;
	while (1) {
		if (!(*it1 == *it2))
			return (false);
		if (it1 == last1)
			break ;
		it1++;
		it2++;
	}
	return (true);
}

// Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)),
// and false otherwise, equality is checked for using predict p
template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p ) {
	InputIt1 it1 = first1;
	InputIt2 it2 = first2;
	while (1) {
		if (!p(*it1, *it2))
			return (false);
		if (it1 == last1)
			break ;
		it1++;
		it2++;
	}
	return (true);
}

} // NAMESPACE FT
#endif // _FT_ALGORITHM_H_
