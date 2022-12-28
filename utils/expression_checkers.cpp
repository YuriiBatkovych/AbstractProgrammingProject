#ifndef ABSTRACTPROGRAMMINGPROJECT_EXP_CHEK
#define ABSTRACTPROGRAMMINGPROJECT_EXP_CHEK

#include <iostream>
#include <stack>
using namespace std;

bool isOperand(char ch){
    return ch >= '0' && ch <= '9' || ch>='A' && ch<='Z' || ch>='a' && ch<='z';
}

bool isONPOperand(char ch){
    return ch == '{' || ch == '[';
}

bool isLetter(char ch){
    return ch>='A' && ch<='Z' || ch>='a' && ch<='z';
}

bool isVariableNameChar(char ch){
    return ch >= '0' && ch <= '9' || ch>='A' && ch<='Z' || ch>='a' && ch<='z' || ch=='_';
}

bool  isNumberChar(char ch){
    return ch >= '0' && ch <= '9' || ch == '.';
}

bool isVectorChar(char ch){
    return isNumberChar(ch) || ch=='[' || ch==']' || ch==',';
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

string getONPOperand(string eqn, int& i){
    string operand;
    i++;
    while(eqn[i]!='}' && eqn[i]!=']'){
        operand+=eqn[i];
        i++;
    }

    if(eqn[i]==']')
        operand = '['+operand+']';

    return operand;
}


bool ONP_correct(string eqn){
    stack<string> stos;
    for(int i=0; i<eqn.length(); i++)//sprawdzamy poprawnosc "probujac obliczyc to wyrazenie"
    {
        if(isONPOperand(eqn[i])){
            string operand = getONPOperand(eqn, i);
            stos.push(operand);
        }
        else if(isBiOperator(eqn[i])) {
            if (stos.empty())
                return false;
            stos.pop();
        }
        else if(isMonoOperator(eqn[i])){
            if(stos.empty())
                return false;
        }
        else return false;
    }
    if(stos.empty()) return false;
    else{
        stos.pop();
        return stos.empty();
    }
}

bool Infix_correct(string eqn){
    int state = 0;
    int number_open_brackets=0;

    for(int i=0; i<eqn.length(); i++) //implementscja automatu sprawdzajacego poprwawnosc wyrazenie
    {
        if(state==0){
            if(eqn[i]=='~')
                state = 2;
            else if(isOperand(eqn[i])) {
                state = 1;
                while(isNumberChar(eqn[i]) || isVariableNameChar(eqn[i]))
                    i++;
                i--;
            }
            else if(eqn[i]=='[') {  //vector
                state = 1;
                while(isVectorChar(eqn[i])&&eqn[i]!=']')
                    i++;
            }
            else if(eqn[i]=='(')
                number_open_brackets++;
            else break;
        }
        else if(state==1){
            if(isOperator(eqn[i]))
                state = 0;
            else if(eqn[i]==')'){
                if(number_open_brackets>0) number_open_brackets--;
                else{
                    state=0;
                    break;
                }
            }
            else{
                state=0;
                break;
            }
        }
        else {
            if (eqn[i] == '(') {
                state = 0;
                number_open_brackets++;
            } else if (isOperand(eqn[i])) {
                state = 1;
                while(isNumberChar(eqn[i]) || isVariableNameChar(eqn[i]))
                    i++;
                i--;
            }
            else if (eqn[i] != '~') break;
        }
    }
    return state==1 && number_open_brackets==0;
}

#endif