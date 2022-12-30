#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
#include <iostream>
#include <stack>
#include <cstdlib>
#include <utility>
#include "expression_checkers.cpp"
#include "converters.cpp"
#include "Dual.h"

using namespace std;

template<typename Tensor>
class TreeNode
{
private:
    template<typename ResultType>
    ResultType recursiveCompute(){
        if(isBiOperator(val[0])){
            ResultType left_arg = left->compute<ResultType>();
            ResultType right_arg = right->compute<ResultType>();
            return calculate<ResultType>(left_arg, right_arg);
        }
        else if(isMonoOperator(val[0])){
            if(left != nullptr){
                return calculate<ResultType>(left->compute<ResultType>());
            }
            else if(right != nullptr){
                return calculate<ResultType>(right->compute<ResultType>());
            }
            else cout<<"ERROR"<<endl;
        }
    }

protected:
    Tensor val;
    bool derivative = false;
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

    void set_derivative(string var){
        this->derivative = (val==var);
        if(left!= nullptr) left->set_derivative(var);
        if(right!= nullptr) right->set_derivative(var);
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

    template<typename ResultType>
    ResultType compute(){
        if(this->is_leaf()){
            return convert<ResultType>(val);
        }
        else{
            return recursiveCompute<ResultType>();
        }
    }

    template<typename ResultType>
    ExpressionVector<ResultType> computeVector(){
        if(this->is_leaf()){
            return convertVector<ResultType>(val);
        }
        else{
            if(isBiOperator(val[0])){
                ExpressionVector<ResultType> left_arg = left->computeVector<ResultType>();
                ExpressionVector<ResultType> right_arg = right->computeVector<ResultType>();
                return calculate<ExpressionVector<ResultType>>(left_arg, right_arg);
            }
            else if(isMonoOperator(val[0])){
                if(left != nullptr){
                    return calculate<ExpressionVector<ResultType>>(left->computeVector<ResultType>());
                }
                else if(right != nullptr){
                    return calculate<ExpressionVector<ResultType>>(right->computeVector<ResultType>());
                }
                else cout<<"ERROR"<<endl;
            }
        }
    }

    template<typename ResultType>
    Dual<ResultType> computeFunctional(){
        if(this->is_leaf()){
            if(derivative) return Dual(convert<ResultType>(val), 1);
            return Dual(convert<ResultType>(val));
        }
        else{
            if(isBiOperator(val[0])){
                Dual<ResultType> left_arg = left->template computeFunctional<ResultType>();
                Dual<ResultType> right_arg = right->template computeFunctional<ResultType>();
                return calculate<Dual<ResultType>>(left_arg, right_arg);
            }
            else if(isMonoOperator(val[0])){
                if(left != nullptr){
                    return calculate<Dual<ResultType>>(left->template computeFunctional<ResultType>());
                }
                else if(right != nullptr){
                    return calculate<Dual<ResultType>>(right->template computeFunctional<ResultType>());
                }
                else cout<<"ERROR"<<endl;
            }
        }
    }
};

template<typename Tensor>
class ExpressionTree
{
protected:
    TreeNode<string>* root;

    void inOrderShow(TreeNode<string> *ptr){
        if (ptr != nullptr)
        {
            inOrderShow(ptr->get_left());
            cout<<ptr->get_value();
            inOrderShow(ptr->get_right());
        }
    }

    void preOrderShow(TreeNode<string> *ptr){
        if (ptr != nullptr)
        {
            cout<<ptr->get_value();
            preOrderShow(ptr->get_left());
            preOrderShow(ptr->get_right());
        }
    }

    void postOrderShow(TreeNode<string> *ptr){
        if (ptr != nullptr)
        {
            postOrderShow(ptr->get_left());
            postOrderShow(ptr->get_right());
            cout<<ptr->get_value();
        }
    }

    int priority(string x)  //funkcja wyznaczającza priorytet operatora
    {   if(x=="=") return 0;
        else if(x==">"|| x=="<") return 1;
        else if(x=="+"|| x=="-") return 2;
        else if(x=="*"|| x=="/" || x=="%") return 3;
        else if(x=="^") return 4;
        else if(x=="~") return 5;
        else if(isOperand(x[0])) return 6;
        else return -2;
    }

    virtual string getVariableName(string eqn, int& i){
        string variable;

        while(isVariableNameChar(eqn[i])){
            variable += eqn[i];
            i++;
        }
        variable = '{' + variable + '}';
        i--;
        return variable;
    }

    virtual string getNumber(string eqn, int& i){
        string number;

        while (isNumberChar(eqn[i])){
            number += eqn[i];
            i++;
        }
        number = '{' + number + '}';
        i--;
        return number;
    }

    string getVector(string eqn, int i){
        string vector;

        while(isVectorChar(eqn[i]) && eqn[i]!=']'){
            vector+=eqn[i];
            i++;
        }

        return vector+']';
    }

    string constructONP(string eqn){
        string output;

        if(Infix_correct(eqn)) //jeżeli wyrażenie prawidłowe zaczynamy konwersję (Algorytm Dijkstra)
        {
            stack<string> stos; //stos pomoczniczy
            for(int i=0; i<eqn.length(); i++)
            {
                if(isOperand(eqn[i])) {
                    if(isLetter(eqn[i])){
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
                else if(isOperator(eqn[i]))
                {
                    string tmp(1, eqn[i]);
                    while(!stos.empty() && priority(stos.top())>=priority(tmp)) {
                        output += stos.top();
                        stos.pop();
                    }
                    string s(1, eqn[i]);
                    stos.push(s);
                }
                else if(eqn[i]=='~'|| eqn[i]=='^' || eqn[i]=='=')
                {
                    string tmp(1, eqn[i]);
                    while(!stos.empty() && priority(stos.top())>priority(tmp)) {
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
        else cout<<"Infix eqn is not correct"<<endl;
        return output;
    }

    void constructFromONP(string eqn){
        stack<TreeNode<string>*> tree_stack;
        if(ONP_correct(eqn)){
            for(int i=0; i<eqn.length(); i++){
                if(isONPOperand(eqn[i])) {
                    string operand = getONPOperand(eqn, i);
                    auto* ptr = new TreeNode<string>(operand);
                    tree_stack.push(ptr);
                }
                else if(isOperator(eqn[i])){
                    if(isBiOperator(eqn[i])){
                        string tmp = string(1, eqn[i]);
                        auto* ptr = new TreeNode<string>(tmp);
                        ptr->set_right(tree_stack.top());
                        tree_stack.top()->set_ancestor(ptr);
                        tree_stack.pop();
                        ptr->set_left(tree_stack.top());
                        tree_stack.top()->set_ancestor(ptr);
                        tree_stack.pop();
                        tree_stack.push(ptr);
                    }
                    else if(isMonoOperator(eqn[i])){
                        string tmp = string(1, eqn[i]);
                        auto* ptr = new TreeNode<string>(tmp);
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
            else cout<<"error"<<endl;
        }
        else cout<<eqn<<" Onp eqn is not correct"<<endl;
    }

public:
    ExpressionTree(){
        root = nullptr;
    }

    void constructFromInfix(string eqn){
        string onp_form = constructONP(eqn);
        constructFromONP(onp_form);
    }

    virtual Tensor compute(){
        if(root == nullptr)
            return 0;
        return root->compute<Tensor>();
    }

    void inOrder(){
        if(root== nullptr){
            cout<<"Tree is empty"<<endl;
            return;
        }
        inOrderShow(root);
        cout<<endl;
    }

    void preOrder(){
        if(root== nullptr){
            cout<<"Tree is empty"<<endl;
            return;
        }
        preOrderShow(root);
        cout<<endl;
    }

    void postOrder(){
        if(root== nullptr){
            cout<<"Tree is empty"<<endl;
            return;
        }
        postOrderShow(root);
        cout<<endl;
    }
};


#endif //ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
