#include <iostream>
#include "utils/ExpTree.h"
#include "utils/Dual.h"
using namespace std;


int main() {

    Dual x(5);
    Dual y(6);

    Dual f = pow(x, 2)*y;

    cout<<f.getDerivative()<<" "<<f.getValue()<<endl;

    return 0;
}