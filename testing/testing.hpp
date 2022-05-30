#ifndef TESTING_H
# define TESTING_H

#include <cassert>
#include <string>
#include <iostream>

#include <vector>
#include <list>
#include <stack>

#include "../vector.hpp"
#include "../iterator.hpp"
#include "../utility.hpp"
#include "../algorithm.hpp"
#include "../stack.hpp"

#include "ANSIpalette.h"
#include "TestClass.hpp"

#if STD
#define __NS__ std
#endif
#if !STD
#define __NS__ ft
#endif

void test_vector();
void test_stack();

#endif // TESTING_H
