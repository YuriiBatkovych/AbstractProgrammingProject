#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H

#include <iostream>
#include "ExpTree.h"

template<typename Tensor>
class ExpVectorTree : public ExpressionTree<Tensor>{

protected:

    string getVariableName(string eqn, int& i){
        cout<<"ERRROR"<<endl;
        return "";
    }

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
        return this->root->template computeVector<Tensor>();
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H
