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

	system("leaks test_ft_containers | tail -3");
	// system("leaks test_ft_containers");
	return (0);
}

// swap specialization vector ?
// debugs ?
