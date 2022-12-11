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
    TreeNode<Tensor> *left, *right;

    TreeNode()
    {
        this->left = nullptr;
        this->right = nullptr;
    }


    TreeNode(char val)
    {
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    void set_left(TreeNode<Tensor>* left_node){
        this->left = left_node;
    }

    void set_right(TreeNode<Tensor>* right_node){
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

    void inOrderShow(TreeNode<char> *ptr)
    {
        if (ptr != nullptr)
        {
            inOrderShow(ptr->left);
            cout<<ptr->val;
            inOrderShow(ptr->right);
        }
    }

    int priorytet(char x)  //funkcja wyznaczającza priorytet operatora
    {   if(x=='=') return 0;
        else if(x=='>'|| x=='<') return 1;
        else if(x=='+'|| x=='-') return 2;
        else if(x=='*'|| x=='/' || x=='%') return 3;
        else if(x=='^') return 4;
        else if(x=='~') return 5;
        else if(isOperand(x)) return 6;
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
                if(isOperand(eqn[i])) {
                    auto* ptr = new TreeNode<Tensor>(eqn[i]);
                    tree_stack.push(ptr);
                }
                else if(isOperator(eqn[i])){
                    if(isBiOperator(eqn[i])){
                        auto* ptr = new TreeNode<Tensor>(eqn[i]);
                        ptr->set_right(tree_stack.top());
                        tree_stack.pop();
                        ptr->set_left(tree_stack.top());
                        tree_stack.pop();
                        tree_stack.push(ptr);
                    }
                    else if(isMonoOperator(eqn[i])){
                        auto* ptr = new TreeNode<Tensor>(eqn[i]);
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
        else cout<<eqn<<"Onp eqn is not correct";
    }

    void constructFromInfix(string eqn){
        string onp_form = constructONP(eqn);
        constructFromONP(onp_form);
    }

    string constructONP(string eqn){
        string output;

        if(Infix_correct(eqn)) //jeżeli wyrażenie prawidłowe zaczynamy konwersję (Algorytm Dijkstra)
        {
            stack<char> stos; //stos pomoczniczy
            for(int i=0; i<eqn.length(); i++)
            {
                if(isOperand(eqn[i]))
                    output += eqn[i];
                else if(eqn[i]=='(')
                    stos.push(eqn[i]);
                else if(isOperator(eqn[i]))
                {
                    while(!stos.empty() && priorytet(stos.top())>=priorytet(eqn[i])) {
                        output += stos.top();
                        stos.pop();
                    }
                    stos.push(eqn[i]);
                }
                else if(eqn[i]=='~'|| eqn[i]=='^' || eqn[i]=='=')
                {
                    while(!stos.empty() && priorytet(stos.top())>priorytet(eqn[i])) {
                        output += stos.top();
                        stos.pop();
                    }
                    stos.push(eqn[i]);
                }
                else if(eqn[i]==')')
                {
                    while(stos.top()!='(') {
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
