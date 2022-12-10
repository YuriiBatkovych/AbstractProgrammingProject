#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
#include <iostream>
#include <stack>
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

public:
    ExpressionTree(){}

    bool isOperand(char ch){
        return ch >= '0' && ch <= '9' || ch>='A' && ch<='Z' || ch>='a' && ch<='z';
    }

    bool isOperator(char ch){
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'
                || ch == '%';
    }

    bool isMonoOperator(char ch){
        return ch == '~';
    }

    bool isBiOperator(char ch){
        return isOperator(ch) && !isMonoOperator(ch);
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

    void constructFromONP(string eqn){
        stack<TreeNode<Tensor>*> tree_stack;
        for(int i=0; i<eqn.length(); i++){
            if(isOperand(eqn[i])) {
                auto* ptr = new TreeNode<Tensor>(eqn[i]);
                tree_stack.push(ptr);
            }
            else if(isOperator(eqn[i])){
                if(isBiOperator(eqn[i])){
                    cout<<"bi "<<eqn[i]<<" "<<endl;
                    auto* ptr = new TreeNode<Tensor>(eqn[i]);
                    ptr->set_right(tree_stack.top());
                    tree_stack.pop();
                    ptr->set_left(tree_stack.top());
                    tree_stack.pop();
                    tree_stack.push(ptr);
                    ptr->show();
                    cout<<endl;
                }
                else if(isMonoOperator(eqn[i])){
                    cout<<"mono"<<endl;
                    auto* ptr = new TreeNode<Tensor>(eqn[i]);
                    ptr->set_right(tree_stack.top());
                    tree_stack.pop();
                    tree_stack.push(ptr);
                    ptr->show();
                    cout<<endl;
                }
            }
        }

        if(!tree_stack.empty()){
            root = tree_stack.top();
            tree_stack.pop();
        }
        else cout<<"error"<<endl;
    }

    string constructONP(string eqn){
        int state = 0;
        int number_open_brackets=0;
        string wyjscie="";

        for(int i=0; i<eqn.length(); i++) //implementscja automatu sprawdzajacego poprwawnosc wyrazenie
        {                                       //podanego przez dr. Roska
            if(state==0)
            {
                if(eqn[i]=='~')
                    state = 2;
                else if(isOperand(eqn[i]))
                    state = 1;
                else if(eqn[i]=='(')
                    number_open_brackets++;
                else break;
            }
            else if(state==1)
            {
                if(isOperator(eqn[i]))
                    state = 0;
                else if(eqn[i]==')')
                {
                    if(number_open_brackets>0) number_open_brackets--;
                    else
                    {   state=0;
                        break;
                    }
                }
                else
                {   state=0;
                    break;
                }
            }
            else if(state==2)
            {
                if(eqn[i]=='(')
                {
                    state=0;
                    number_open_brackets++;
                }
                else if(isOperand(eqn[i]))
                    state = 1;
                else if(eqn[i]!='~') break;
            }
        }
        if(state==1 && number_open_brackets==0) //jeżeli wyrażenie prawidłowe zaczynamy konwersję (Algorytm Dijkstra)
        {
            stack<char> stos; //stos pomoczniczy
            for(int i=0; i<eqn.length(); i++)
            {
                if(isOperand(eqn[i]))
                    wyjscie += eqn[i];
                else if(eqn[i]=='(')
                    stos.push(eqn[i]);
                else if(isOperator(eqn[i]))
                {
                    while(!stos.empty() && priorytet(stos.top())>=priorytet(eqn[i])) {
                        wyjscie += stos.top();
                        stos.pop();
                    }
                    stos.push(eqn[i]);
                }
                else if(eqn[i]=='~'|| eqn[i]=='^' || eqn[i]=='=')
                {
                    while(!stos.empty() && priorytet(stos.top())>priorytet(eqn[i])) {
                        wyjscie += stos.top();
                        stos.pop();
                    }
                    stos.push(eqn[i]);
                }
                else if(eqn[i]==')')
                {
                    while(stos.top()!='(') {
                        wyjscie += stos.top();
                        stos.pop();
                    }
                    stos.pop();
                }
            }
            if(!stos.empty())
                while (!stos.empty()) {
                    wyjscie += stos.top();
                    stos.pop();
                }
            cout<<"ONP: "<<wyjscie<<endl;

        }
        else wyjscie="error";
        return wyjscie;
    }


    void inOrder(){
        inOrderShow(root);
    }
};


#endif //ABSTRACTPROGRAMMINGPROJECT_EXPTREE_H
