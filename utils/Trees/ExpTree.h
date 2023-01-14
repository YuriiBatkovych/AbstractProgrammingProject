#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
#include <iostream>
#include <stack>
#include <cstdlib>
#include <utility>
#include "../converters.cpp"
#include "../Dual.h"
#include "../Nodes/TreeNode.h"
#include "../Nodes/NodeCreators.h"
#include "../../exceptions/CorectionExceptions.h"
#include "../ExpressionChecker.h"
using namespace std;

template<typename Tensor,
        template<typename> class NodeCreator=TreeNodeCreator
        >
class ExpressionTree
{
protected:
    TreeNode<string>* root;

    void inOrderShow(ostream& out, TreeNode<string> *ptr){
        if (ptr != nullptr)
        {
            inOrderShow(out, ptr->get_left());
            out<<ptr->get_value();
            inOrderShow(out, ptr->get_right());
        }
    }

    void preOrderShow(ostream& out, TreeNode<string> *ptr){
        if (ptr != nullptr)
        {
            out<<ptr->get_value();
            preOrderShow(out, ptr->get_left());
            preOrderShow(out, ptr->get_right());
        }
    }

    void postOrderShow(ostream& out, TreeNode<string> *ptr){
        if (ptr != nullptr)
        {
            postOrderShow(out, ptr->get_left());
            postOrderShow(out, ptr->get_right());
            out<<ptr->get_value();
        }
    }

    virtual string getVariableName(const string& eqn, int& i){
        string variable;

        while(OperatorDeductor::isVariableNameChar(eqn[i])){
            variable += eqn[i];
            i++;
        }
        variable = '{' + variable + '}';
        i--;
        return variable;
    }

    virtual string getNumber(const string& eqn, int& i){
        string number;

        while (OperatorDeductor::isNumberChar(eqn[i])){
            number += eqn[i];
            i++;
        }
        number = '{' + number + '}';
        i--;
        return number;
    }

    virtual string getVector(const string& eqn, int i){
        string vector;

        while(OperatorDeductor::isVectorChar(eqn[i]) && eqn[i]!=']'){
            vector+=eqn[i];
            i++;
        }

        return vector+']';
    }

    string constructONP(string eqn){
        string output;

        if(ExpressionChecker::Infix_correct(eqn))
        {
            stack<string> stos;
            for(int i=0; i<eqn.length(); i++)
            {
                if(OperatorDeductor::isOperand(eqn[i])) {
                    if(OperatorDeductor::isLetter(eqn[i])){
                        string var_name = getVariableName(eqn, i);
                        output += var_name;
                    }
                    else {
                        string var_name = getNumber(eqn, i);
                        output += var_name;
                    }
                }
                else if(eqn[i]=='['){  //poczatek definicji vectora
                    string vector = getVector(eqn, i);
                    output += vector;
                    i += vector.length()-1;
                }
                else if(eqn[i]=='(') {
                    stos.push("(");
                }
                else if(OperatorDeductor::isOperator(eqn[i]))
                {
                    string tmp(1, eqn[i]);
                    while(!stos.empty() && OperatorDeductor::priority(stos.top())>=OperatorDeductor::priority(tmp)) {
                        output += stos.top();
                        stos.pop();
                    }
                    string s(1, eqn[i]);
                    stos.push(s);
                }
                else if(eqn[i]=='~'|| eqn[i]=='^' || eqn[i]=='=')
                {
                    string tmp(1, eqn[i]);
                    while(!stos.empty() && OperatorDeductor::priority(stos.top())>OperatorDeductor::priority(tmp)) {
                        output += stos.top();
                        stos.pop();
                    }
                    string s(1, eqn[i]);
                    stos.push(s);
                }
                else if(eqn[i]==')')
                {
                    while(stos.top() != "(") {
                        output += stos.top();
                        stos.pop();
                    }
                    stos.pop();
                }
            }
            if(!stos.empty())
                while (!stos.empty()) {
                    output += stos.top();
                    stos.pop();
                }
        }
        else throw InfixExpressionException();
        return output;
    }

    void constructFromONP(string eqn){
        stack<TreeNode<string>*> tree_stack;
        if(ExpressionChecker::ONP_correct(eqn)){
            for(int i=0; i<eqn.length(); i++){
                if(OperatorDeductor::isONPOperand(eqn[i])) {
                    string operand = OperatorDeductor::getONPOperand(eqn, i);
                    auto* ptr = NodeCreator<string>::create(operand);
                    tree_stack.push(ptr);
                }
                else if(OperatorDeductor::isOperator(eqn[i])){
                    if(OperatorDeductor::isBiOperator(eqn[i])){
                        string tmp = string(1, eqn[i]);
                        auto* ptr = NodeCreator<string>::create(tmp);
                        ptr->set_right(tree_stack.top());
                        tree_stack.top()->set_ancestor(ptr);
                        tree_stack.pop();
                        ptr->set_left(tree_stack.top());
                        tree_stack.top()->set_ancestor(ptr);
                        tree_stack.pop();
                        tree_stack.push(ptr);
                    }
                    else if(OperatorDeductor::isMonoOperator(eqn[i])){
                        string tmp = string(1, eqn[i]);
                        auto* ptr = NodeCreator<string>::create(tmp);
                        ptr->set_right(tree_stack.top());
                        tree_stack.top()->set_ancestor(ptr);
                        tree_stack.pop();
                        tree_stack.push(ptr);
                    }
                }
            }

            if(!tree_stack.empty()){
                root = tree_stack.top();
                tree_stack.pop();
            }
            else throw ONPExpressionException();
        }
        else throw ONPExpressionException();
    }

public:
    ExpressionTree(){
        root = nullptr;
    }

    ExpressionTree(const ExpressionTree<Tensor, NodeCreator>& expTree){
        root = NodeCreator<string>::copy(*expTree.root);
    }

    void constructFromInfix(string eqn){
        string onp_form = constructONP(eqn);
        constructFromONP(onp_form);
    }

    void inOrder(ostream& out){
        if(root== nullptr){
            out<<"Tree is empty"<<endl;
            return;
        }
        inOrderShow(out, root);
        out<<endl;
    }

    void preOrder(ostream& out){
        if(root== nullptr){
            out<<"Tree is empty"<<endl;
            return;
        }
        preOrderShow(out, root);
        out<<endl;
    }

    void postOrder(ostream& out){
        if(root== nullptr){
            out<<"Tree is empty"<<endl;
            return;
        }
        postOrderShow(out, root);
        out<<endl;
    }

    template<typename TensorType,
             template<typename> class NodeCreatorClass>
    friend ExpressionTree<TensorType, NodeCreatorClass>
        operator+(const ExpressionTree<TensorType, NodeCreatorClass>& u,
                  const ExpressionTree<TensorType, NodeCreatorClass>& v);

    template<typename TensorType,
            template<typename> class NodeCreatorClass>
    friend ExpressionTree<TensorType, NodeCreatorClass>
    operator-(const ExpressionTree<TensorType, NodeCreatorClass>& u,
              const ExpressionTree<TensorType, NodeCreatorClass>& v);

    template<typename TensorType,
            template<typename> class NodeCreatorClass>
    friend ExpressionTree<TensorType, NodeCreatorClass>
    operator*(const ExpressionTree<TensorType, NodeCreatorClass>& u,
              const ExpressionTree<TensorType, NodeCreatorClass>& v);

    template<typename TensorType,
            template<typename> class NodeCreatorClass>
    friend ExpressionTree<TensorType, NodeCreatorClass>
    operator/(const ExpressionTree<TensorType, NodeCreatorClass>& u,
              const ExpressionTree<TensorType, NodeCreatorClass>& v);
};

#endif //ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
