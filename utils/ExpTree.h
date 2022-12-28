#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
#include <iostream>
#include <stack>
#include "expression_checkers.cpp"

using namespace std;

template<typename Tensor>
class TreeNode
{
public:
    Tensor val;
    TreeNode *left, *right;

    TreeNode()
    {
        this->left = nullptr;
        this->right = nullptr;
    }


    TreeNode(Tensor val)
    {
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    template<typename LeftType>
    void set_left(TreeNode<LeftType>* left_node){
        this->left = left_node;
    }

    template<typename RightType>
    void set_right(TreeNode<RightType>* right_node){
        this->right = right_node;
    }

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
};

template<typename Tensor>
class ExpressionTree
{
private:
    TreeNode<Tensor>* root;

    void inOrderShow(TreeNode<Tensor> *ptr)
    {
        if (ptr != nullptr)
        {
            inOrderShow(ptr->left);
            cout<<ptr->val;
            inOrderShow(ptr->right);
        }
    }

    int priorytet(string x)  //funkcja wyznaczającza priorytet operatora
    {   if(x=="=") return 0;
        else if(x==">"|| x=="<") return 1;
        else if(x=="+"|| x=="-") return 2;
        else if(x=="*"|| x=="/" || x=="%") return 3;
        else if(x=="^") return 4;
        else if(x=="~") return 5;
        else if(isOperand(x[0])) return 6;
        else return -2;
    }

public:
    ExpressionTree(){
        root = nullptr;
    }

    void constructFromONP(string eqn){
        stack<TreeNode<Tensor>*> tree_stack;
        if(ONP_correct(eqn)){
            for(int i=0; i<eqn.length(); i++){
                if(isONPOperand(eqn[i])) {
                    string operand = getONPOperand(eqn, i);
                    auto* ptr = new TreeNode<Tensor>(operand);
                    tree_stack.push(ptr);
                }
                else if(isOperator(eqn[i])){
                    if(isBiOperator(eqn[i])){
                        string tmp = string(1, eqn[i]);
                        auto* ptr = new TreeNode<Tensor>(tmp);
                        ptr->set_right(tree_stack.top());
                        tree_stack.pop();
                        ptr->set_left(tree_stack.top());
                        tree_stack.pop();
                        tree_stack.push(ptr);
                    }
                    else if(isMonoOperator(eqn[i])){
                        string tmp = string(1, eqn[i]);
                        auto* ptr = new TreeNode<Tensor>(tmp);
                        ptr->set_right(tree_stack.top());
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

    void constructFromInfix(string eqn){
        string onp_form = constructONP(eqn);
        constructFromONP(onp_form);
    }

    string getVariableName(string eqn, int& i){
        string variable;

        while(isVariableNameChar(eqn[i])){
            variable += eqn[i];
            i++;
        }
        variable = '{' + variable + '}';
        i--;
        return variable;
    }

    string getNumber(string eqn, int& i){
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
                    while(!stos.empty() && priorytet(stos.top())>=priorytet(tmp)) {
                        output += stos.top();
                        stos.pop();
                    }
                    string s(1, eqn[i]);
                    stos.push(s);
                }
                else if(eqn[i]=='~'|| eqn[i]=='^' || eqn[i]=='=')
                {
                    string tmp(1, eqn[i]);
                    while(!stos.empty() && priorytet(stos.top())>priorytet(tmp)) {
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


    void inOrder(){
        if(root== nullptr){
            cout<<"Tree is empty";
        }
        else inOrderShow(root);
        cout<<endl;
        root->show();
        cout<<endl;
    }
};


#endif //ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
