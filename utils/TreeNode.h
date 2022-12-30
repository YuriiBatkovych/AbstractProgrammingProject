#ifndef ABSTRACTPROGRAMMINGPROJECT_TREENODE_H
#define ABSTRACTPROGRAMMINGPROJECT_TREENODE_H

#include <iostream>
#include "Dual.h"
#include "ExpressionVector.h"

template<typename Tensor>
class TreeNode
{
protected:
    Tensor val;
    TreeNode *ancestor;
    TreeNode *left, *right;
public:
    TreeNode(){
        this->left = nullptr;
        this->right = nullptr;
        this->ancestor = nullptr;
    }


    TreeNode(Tensor val){
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
        this->ancestor = nullptr;
    }

    TreeNode(const TreeNode& other){
        this->val = other.val;

        if(other.left!=nullptr) this->left = new TreeNode<Tensor>(*other.left);
        else this->left = nullptr;

        if(other.right!=nullptr) this->right = new TreeNode<Tensor>(*other.right);
        else this->right = nullptr;

        this->ancestor = nullptr;
    }

    template<typename LeftType>
    void set_left(TreeNode<LeftType>* left_node){
        this->left = left_node;
    }

    template<typename RightType>
    void set_right(TreeNode<RightType>* right_node){
        this->right = right_node;
    }

    template<typename AncestorType>
    void set_ancestor(TreeNode<AncestorType>* ancestor_node){
        this->ancestor = ancestor_node;
    }

    auto get_left(){ return left; }
    auto get_right(){ return right; }
    auto get_ancestor(){ return ancestor; }

    Tensor get_value() { return val; }

    bool is_leaf(){ return left == nullptr && right == nullptr; }

    void show() {
        cout << val << " ";
        if (left != nullptr){
            cout << "left -> ( ";
            left->show();
            cout << ") ";
        }
        if (right != nullptr){
            cout << "right -> ( ";
            right->show();
            cout << ") ";
        }
    }

    template<typename ResultType>
    ResultType calculate(ResultType left_arg, ResultType right_arg){
        switch (val[0]) {
            case '*':
                return left_arg*right_arg;
            case '+':
                return left_arg+right_arg;
            case '-':
                return left_arg-right_arg;
            case '/':
                return left_arg/right_arg;
            case '^':
                return pow(left_arg, right_arg);
            default:
                return left_arg;
        }
    }

    template<typename ArgType>
    ArgType calculate(ArgType arg){
        switch (val[0]) {
            case '~':
                return -arg;
            default:
                return arg;
        }
    }

    void replace(string value, string replace_value){
        if(val==value) val = replace_value;
        if(left!= nullptr) left->replace(value, replace_value);
        if(right!= nullptr) right->replace(value, replace_value);
    }
};


#endif //ABSTRACTPROGRAMMINGPROJECT_TREENODE_H
