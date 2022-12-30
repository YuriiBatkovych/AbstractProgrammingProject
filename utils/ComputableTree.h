#ifndef ABSTRACTPROGRAMMINGPROJECT_COMPUTABLETREE_H
#define ABSTRACTPROGRAMMINGPROJECT_COMPUTABLETREE_H

#include <iostream>
#include "ExpTree.h"
#include "NodeCreators.h"
#include "ComputeNode.h"

template<typename Tensor,
         template<typename> class NodeCreator = ComputeNodeCreator
        >
class ComputableTree : public ExpressionTree<Tensor, NodeCreator>{

protected:
    string getVariableName(const string& eqn, int& i){
        cout<<"ERRROR"<<endl;
        return "";
    }
public:

    virtual Tensor compute(){
        if(this->root == nullptr)
            return Tensor();
        return ((ComputeNode<string>*)(this->root))->template compute<Tensor>();
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_COMPUTABLETREE_H
