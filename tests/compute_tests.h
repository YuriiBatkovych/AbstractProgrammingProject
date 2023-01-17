#ifndef ABSTRACTPROGRAMMINGPROJECT_COMPUTE_TESTS_H
#define ABSTRACTPROGRAMMINGPROJECT_COMPUTE_TESTS_H

#include <iostream>
#include "../utils/Trees/ComputableTree.h"
#include "../utils/Trees/ExpressionTreeOperators.h"
using namespace std;

#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << "file"<< __FILE__ << std::endl; }

void test_compute_ordinary()
{
    ComputableTree<double> computableTree;
    computableTree.constructFromInfix("23+78.9/3-(22+102)");
    double result = computableTree.compute();
    IS_TRUE(result == -74.7);
}

void test_compute_addable()
{
    ComputableTree<double> computableTree;
    computableTree.constructFromInfix("10+10");
    double result = computableTree.compute();
    IS_TRUE(result == 20);

    ComputableTree<double> computableTree1;
    computableTree1.constructFromInfix("10*10");
    double result1 = computableTree1.compute();
    IS_TRUE(result1 == 100);

    ComputableTree<double> computableTree2 = computableTree + computableTree1;
    IS_TRUE(computableTree2.compute() == 120)
}

void test_compute_division()
{
    ComputableTree<double> computableTree;
    computableTree.constructFromInfix("10+10");
    double result = computableTree.compute();
    IS_TRUE(result == 20);

    ComputableTree<double> computableTree1;
    computableTree1.constructFromInfix("10*10");
    double result1 = computableTree1.compute();
    IS_TRUE(result1 == 100);

    ComputableTree<double> computableTree2 = computableTree1 / computableTree;
    IS_TRUE(computableTree2.compute() == 5)
}


void test_compute_zero()
{
    ComputableTree<float> computableTree;
    computableTree.constructFromInfix("0");
    double result = computableTree.compute();
    IS_TRUE(result == 0);

    computableTree.constructFromInfix("99-99");
    result = computableTree.compute();
    IS_TRUE(result == 0);
}



#endif