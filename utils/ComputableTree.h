#ifndef ABSTRACTPROGRAMMINGPROJECT_COMPUTABLETREE_H
#define ABSTRACTPROGRAMMINGPROJECT_COMPUTABLETREE_H

#include <iostream>
#include "ExpTree.h"
#include "NodeCreators.h"
#include "ComputeNode.h"
#include "../exceptions/NotAllowedExceptions.h"

template<typename Tensor,
         template<typename> class NodeCreator = ComputeNodeCreator
        >
class ComputableTree : public ExpressionTree<Tensor, NodeCreator>{

protected:
    string getVariableName(const string& eqn, int& i){
        throw VariablesNotAllowedException();
    }

    virtual string getVector(const string& eqn, int i){
        throw VectorsNotAllowedException();
    }
public:

    ComputableTree(): ExpressionTree<Tensor, NodeCreator>(){}
    ComputableTree(const ExpressionTree<Tensor, NodeCreator>& expTree):
                    ExpressionTree<Tensor, NodeCreator>(expTree){};

    virtual Tensor compute(){
        if(this->root == nullptr)
            return Tensor();
        return ((ComputeNode<string>*)(this->root))->template compute<Tensor>();
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_COMPUTABLETREE_H
