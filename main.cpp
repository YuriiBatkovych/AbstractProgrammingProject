#include <iostream>
#include "utils/ExpTree.h"
using namespace std;


int main() {
    string exp;
    ExpressionTree<char> et;
    cout<<"Enter expression in ONP form: ";
    cin>>exp;
    et.constructFromONP(exp);

    cout<<"In-order Traversal of Expression Tree : ";
    et.inOrder();
    return 0;
}