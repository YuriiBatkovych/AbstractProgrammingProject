#include <iostream>
#include "utils/ExpTree.h"
#include "utils/ExpressionVector.h"
#include "utils/ExpVectorTree.h"
#include "utils/FunctionalTree.h"
#include "utils/ExpressionTreeOperators.h"
using namespace std;


int main() {

    FunctionalTree<int, 3> functionalTree;
    functionalTree.constructFromInfix("x*y^4+3*z-15");
    auto result = functionalTree.compute("y",1,2,4);
    functionalTree.inOrder();
    cout<<result.getValue()<<" "<<result.getDerivative()<<endl;

    VectorTree<double> vectorTree;
    vectorTree.constructFromInfix("[1,4,6]/[2,2,3]+[0,9,7.8]*([3,4,5]+[1,1,1])");
    vectorTree.preOrder();
    cout<<vectorTree.compute()<<endl;

    ComputableTree<double> computableTree;
    computableTree.constructFromInfix("23+78.9/3-(22+102)");
    computableTree.postOrder();
    cout<<computableTree.compute()<<endl;

    ComputableTree<double> computableTree2;
    computableTree2.constructFromInfix("100-23+9");
    computableTree2.postOrder();
    cout<<computableTree2.compute()<<endl;

    ComputableTree<double> ct = computableTree + computableTree2;
    ct.inOrder();
    cout<<ct.compute()<<endl;
//    ComputableTree<float> computableTree2;
//    computableTree2.constructFromInfix("23*a-4");


    return 0;
}