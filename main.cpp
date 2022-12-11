#include <iostream>
#include "utils/ExpTree.h"
using namespace std;


int main() {
    string exp;
    for(int i=0; i<10; i++){
        ExpressionTree<char> et;
        cout<<"Enter expression in Infix form: ";
        cin>>exp;
        et.constructFromInfix(exp);
        cout<<"In-order Traversal of Expression Tree : ";
        et.inOrder();
        cout<<endl;
    }
    return 0;
}