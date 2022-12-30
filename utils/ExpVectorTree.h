#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H

#include <iostream>
#include "ComputableTree.h"
#include "NodeCreators.h"

template<typename Tensor>
class VectorTree : public ComputableTree<Tensor, VectorNodeCreator>{
protected:
    string getNumber(string eqn, int& i) {
        string number;
        while (isNumberChar(eqn[i])) {
            number += eqn[i];
            i++;
        }
        number = '[' + number + ']';
        i--;
        return number;
    }
public:
    ExpressionVector<Tensor> computeVector(){
        if(this->root == nullptr)
            return ExpressionVector<Tensor>();
        return ((VectorNode<string>*)(this->root))->template computeVector<Tensor>();
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H
