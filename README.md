# 42-ft_containers
Some of the c++98 STL containers recoded from scratch for learning purposes: vector, map, stack and set

The implementation is found in the 'src' folder at the root of this directory.
Map, vector, stack and set were implemented strictly following the naming and the features in the STL, so every function in the '98 standard is provided also here. All descriptions and references match the ones of the [standard library](#https://en.cppreference.com/w/).
Amongst these four containers, also the following .hpp files are provided, as subsidiary for the main objective:
* algorithm.hpp: containing lexicographical_compare and equal algorithms
* iterator.hpp: reverse iterator and iterator_traits
* type_traits.hpp: enable_if and is_integral
* rb_tree.hpp: template for red-black serach tree, underlying data structure for map and set
* utility.hpp: pair

The naming is chosen after the STL iplementation of all the reproduced functionalities.

### TESTING

The folder 'testbench' provides extensive unit tests for each container, written during the development. The tests can be built and excuted with 'make':
* 'make std' compiles the tests using the STL containers
* 'make' compiles using the containers in this project
* execute the build with './test_ft_containers'
* 'make comp' builds the tests with both namespaces, executes the builds and redirects the outputs to files and then prints the diff to stdout
