#ifndef ABSTRACTPROGRAMMINGPROJECT_FUNC_TESTS
#define ABSTRACTPROGRAMMINGPROJECT_FUNC_TESTS

#include <iostream>
#include "../utils/Trees/FunctionalTree.h"
#include "../utils/Dual.h"
using namespace std;

void test_function_ordinary()
{
    FunctionalTree<int, 3> functionalTree;
    functionalTree.constructFromInfix("x*y^4+3*z-15");
    auto result = functionalTree.compute("y",1,2,4);
    IS_TRUE(result.getValue() == 13);
    IS_TRUE(result.getDerivative() == 32);
}

void test_function_zero()
{
    FunctionalTree<int, 2> functionalTree;
    functionalTree.constructFromInfix("y");
    auto result = functionalTree.compute("x",1,2);
    IS_TRUE(result.getValue() == 1);
    IS_TRUE(result.getDerivative() == 0);
}

#endif