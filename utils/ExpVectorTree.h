#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H

#include <iostream>
#include "ComputableTree.h"
#include "NodeCreators.h"

template<typename Tensor>
class VectorTree : public ExpressionTree<Tensor, VectorNodeCreator>{
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

    string getVariableName(const string& eqn, int& i){
        throw VariablesNotAllowedException();
    }
public:

    VectorTree(): ExpressionTree<Tensor, VectorNodeCreator>(){}
    VectorTree(const ExpressionTree<Tensor, VectorNodeCreator>& expTree):
            ExpressionTree<Tensor, VectorNodeCreator>(expTree){};

    ExpressionVector<Tensor> compute(){
        if(this->root == nullptr)
            return ExpressionVector<Tensor>();
        return ((VectorNode<string>*)(this->root))->template computeVector<Tensor>();
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H
