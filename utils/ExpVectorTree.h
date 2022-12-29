#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H

#include <iostream>
#include "ExpTree.h"

template<typename Tensor>
class TreeNodeVector : public TreeNode<Tensor>{
public:
    template<typename ResultType>
    vector<ResultType> compute(){
        if(this->is_leaf()){
            return convertVector<ResultType>(this->val);
        }
        else{
            if(isBiOperator(this->val[0])){
                ResultType left_arg = this->left->template compute<ResultType>();
                ResultType right_arg = this->right->template compute<ResultType>();
                return calculate<ResultType>(left_arg, right_arg);
            }
            else if(isMonoOperator(this->val[0])){
                if(this->left != nullptr){
                    return calculate<ResultType>(this->left->template compute<ResultType>());
                }
                else if(this->right != nullptr){
                    return calculate<ResultType>(this->right->template compute<ResultType>());
                }
                else cout<<"ERROR"<<endl;
            }
        }
    }
};


template<typename Tensor>
class ExpVectorTree : public ExpressionTree<Tensor>{

protected:

    string getVariableName(string eqn, int& i){
        cout<<"ERRROR"<<endl;
        return "";
    }

    string getNumber(string eqn, int& i){
        string number;

        while (isNumberChar(eqn[i])){
            number += eqn[i];
            i++;
        }
        number = '[' + number + ']';
        i--;
        return number;
    }

};

#endif //ABSTRACTPROGRAMMINGPROJECT_EXPVECTORTREE_H
