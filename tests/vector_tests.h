#ifndef ABSTRACTPROGRAMMINGPROJECT_VECTOR_TESTS_H
#define ABSTRACTPROGRAMMINGPROJECT_VECTOR_TESTS_H

#include <iostream>
#include "../utils/Trees/ExpVectorTree.h"
#include "../utils/ExpressionVector.h"

void test_vector_ordinary()
{
    VectorTree<float> vectorTree;
    vectorTree.constructFromInfix("([1,4,6]+[9,6,4])/[1,2,5]");
    auto result = vectorTree.compute();

    ExpressionVector<float> trueResult;
    trueResult.push_back(10);
    trueResult.push_back(5);
    trueResult.push_back(2);
    IS_TRUE(trueResult == result);
}

void test_vector_multiply()
{
    VectorTree<int> vectorTree;
    vectorTree.constructFromInfix("([1,4,6]+[9,6,4])");

    VectorTree<int> vectorTree1;
    vectorTree1.constructFromInfix("[2,2,2]");

    VectorTree<int> vectorTree2 = vectorTree1 * vectorTree;
    auto result = vectorTree2.compute();

    ExpressionVector<int> trueResult;
    trueResult.push_back(20);
    trueResult.push_back(20);
    trueResult.push_back(20);
    IS_TRUE(trueResult == result);
}

void test_vector_sub()
{
    VectorTree<int> vectorTree;
    vectorTree.constructFromInfix("([1,4,6]+[9,6,4])");

    VectorTree<int> vectorTree1;
    vectorTree1.constructFromInfix("[2,2,2]");

    VectorTree<int> vectorTree2 = vectorTree - vectorTree1;
    auto result = vectorTree2.compute();

    ExpressionVector<int> trueResult;
    trueResult.push_back(8);
    trueResult.push_back(8);
    trueResult.push_back(8);
    IS_TRUE(trueResult == result);
}

void test_vector_zero()
{
    VectorTree<float> vectorTree;
    vectorTree.constructFromInfix("[0]");
    auto result = vectorTree.compute();

    ExpressionVector<float> trueResult;
    trueResult.push_back(0);
    IS_TRUE(trueResult == result);
}


#endif //ABSTRACTPROGRAMMINGPROJECT_VECTOR_TESTS_H
