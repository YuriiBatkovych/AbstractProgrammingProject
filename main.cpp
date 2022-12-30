#include <iostream>
#include "utils/ExpTree.h"
#include "utils/Dual.h"
#include "utils/ExpressionVector.h"
#include "utils/ExpVectorTree.h"
#include "utils/ExpVectorTree.h"
#include "utils/FunctionalTree.h"
using namespace std;


int main() {

    FunctionalTree<int, 3> functionalTree;
    functionalTree.constructFromInfix("x*y+3*z-15");
    auto result = functionalTree.computeFunctional("z",1,2,4);
    cout<<result.getValue()<<" "<<result.getDerivative()<<endl;
    return 0;
}