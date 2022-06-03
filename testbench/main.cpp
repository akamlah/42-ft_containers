/* ************************************************************************ */
/*																			*/
/*							ft_containers: tests							*/
/*																			*/
/* ************************************************************************ */

#include "testing.hpp"


int main() {

	// test_vector();
	// test_stack();
	// tests_type_traits_and_utils();
	test_map();

	// system("leaks test_ft_containers | tail -3");
	system("leaks test_ft_containers");

	return (0);
}

// todo: change vector is_integral to ft::
// check if better use const iterators in erase, insert, assign and range constructor vector
// swap specialization vector ?
// debugs ?
