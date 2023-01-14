#ifndef ABSTRACTPROGRAMMINGPROJECT_VECTORNODE_H
#define ABSTRACTPROGRAMMINGPROJECT_VECTORNODE_H

#include "TreeNode.h"
#include "VectorNode.h"
#include "../../exceptions/CorectionExceptions.h"
#include "../OperatorDeductor.h"

template<typename Tensor>
class VectorNode : public TreeNode<Tensor>{
public:

    VectorNode(): TreeNode<Tensor>(){}
    VectorNode(Tensor val): TreeNode<Tensor>(val){}
    VectorNode(const VectorNode& other): TreeNode<Tensor>(other){}

    template<typename ResultType>
    ExpressionVector<ResultType> computeVector(){
        if(this->is_leaf()){
            return convertVector<ResultType>(this->val);
        }
        else{
            if(OperatorDeductor::isBiOperator(this->val[0])){
                ExpressionVector<ResultType> left_arg = ((VectorNode<Tensor>*)(this->left))->template computeVector<ResultType>();
                ExpressionVector<ResultType> right_arg = ((VectorNode<Tensor>*)(this->right))->template computeVector<ResultType>();
                return calculate<ExpressionVector<ResultType>>(left_arg, right_arg);
            }
            else if(OperatorDeductor::isMonoOperator(this->val[0])){
                if(this->left != nullptr){
                    return calculate<ExpressionVector<ResultType>>(((VectorNode<Tensor>*)(this->left))->template computeVector<ResultType>());
                }
                else if(this->right != nullptr){
                    return calculate<ExpressionVector<ResultType>>(((VectorNode<Tensor>*)(this->right))->template computeVector<ResultType>());
                }
                else throw TooFewArgumentsException();
            }
        }
        throw TreeException();
    }

};

#endif //ABSTRACTPROGRAMMINGPROJECT_VECTORNODE_H
