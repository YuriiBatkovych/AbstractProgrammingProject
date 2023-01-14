#ifndef ABSTRACTPROGRAMMINGPROJECT_COMPUTENODE_H
#define ABSTRACTPROGRAMMINGPROJECT_COMPUTENODE_H

#include "TreeNode.h"
#include "ComputeNode.h"
#include "../../exceptions/ArgumentsException.h"
#include "../../exceptions/CorectionExceptions.h"

template<typename Tensor>
class ComputeNode : public TreeNode<Tensor>{
private:
    template<typename ResultType>
    ResultType recursiveCompute(){
        if(OperatorDeductor::isBiOperator(this->val[0])){
            ResultType left_arg = ((ComputeNode<Tensor>*)(this->left))->template compute<ResultType>();
            ResultType right_arg = ((ComputeNode<Tensor>*)(this->right))->template compute<ResultType>();
            return calculate<ResultType>(left_arg, right_arg);
        }
        else if(OperatorDeductor::isMonoOperator(this->val[0])){
            if(this->left != nullptr){
                return calculate<ResultType>(((ComputeNode<Tensor>*)(this->left))->template compute<ResultType>());
            }
            else if(this->right != nullptr){
                return calculate<ResultType>(((ComputeNode<Tensor>*)(this->right))->template compute<ResultType>());
            }
            else throw TooFewArgumentsException();
        }
        throw TreeException();
    }

public:

    ComputeNode(): TreeNode<Tensor>(){}
    explicit ComputeNode(Tensor val): TreeNode<Tensor>(val){}
    explicit ComputeNode(const TreeNode<Tensor>& other): TreeNode<Tensor>(other){}

    template<typename ResultType>
    ResultType compute(){
        if(this->is_leaf()){
            return convert<ResultType>(this->val);
        }
        else{
            return recursiveCompute<ResultType>();
        }
    }

};


#endif //ABSTRACTPROGRAMMINGPROJECT_COMPUTENODE_H
