#ifndef ABSTRACTPROGRAMMINGPROJECT_FUNCTIONALNODE_H
#define ABSTRACTPROGRAMMINGPROJECT_FUNCTIONALNODE_H

#include "TreeNode.h"

template<typename Tensor>
class FunctionalNode : public TreeNode<Tensor>{
private:
    bool derivative = false;
public:

    void set_derivative(string var){
        this->derivative = (this->val==var);
        if(this->left!= nullptr) ((FunctionalNode<Tensor>*)(this->left))->set_derivative(var);
        if(this->right!= nullptr) ((FunctionalNode<Tensor>*)(this->right))->set_derivative(var);
    }

    FunctionalNode(): TreeNode<Tensor>(){}
    explicit FunctionalNode(Tensor val): TreeNode<Tensor>(val){}
    explicit FunctionalNode(const TreeNode<Tensor>& other): TreeNode<Tensor>(other){}

    template<typename ResultType>
    Dual<ResultType> computeFunctional(){
        if(this->is_leaf()){
            if(derivative) return Dual(convert<ResultType>(this->val), 1);
            return Dual(convert<ResultType>(this->val));
        }
        else{
            if(isBiOperator(this->val[0])){
                Dual<ResultType> left_arg = ((FunctionalNode<Tensor>*)(this->left))->template computeFunctional<ResultType>();
                Dual<ResultType> right_arg = ((FunctionalNode<Tensor>*)(this->right))->template computeFunctional<ResultType>();
                return calculate<Dual<ResultType>>(left_arg, right_arg);
            }
            else if(isMonoOperator(this->val[0])){
                if(this->left != nullptr){
                    return calculate<Dual<ResultType>>(((FunctionalNode<Tensor>*)(this->right))->template computeFunctional<ResultType>());
                }
                else if(this->right != nullptr){
                    return calculate<Dual<ResultType>>(((FunctionalNode<Tensor>*)(this->right))->template computeFunctional<ResultType>());
                }
                else cout<<"ERROR"<<endl;
            }
        }
    }

};

#endif //ABSTRACTPROGRAMMINGPROJECT_FUNCTIONALNODE_H
