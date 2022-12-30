#ifndef ABSTRACTPROGRAMMINGPROJECT_EXP_CHEK
#define ABSTRACTPROGRAMMINGPROJECT_EXP_CHEK

#include <iostream>
#include <stack>
#include <vector>
#include <bits/stdc++.h>

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

bool  isNumber(char ch){
    return ch >= '0' && ch <= '9';
}

bool  isNumberChar(char ch){
    return ch >= '0' && ch <= '9' || ch == '.';
}

bool isDoubleNumber(const string& s){
    return s.find('.') != std::string::npos;
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

bool isVector(string value){
    return value[0] == '[' && value[value.length()-1] == ']';
}

string getVectorWithoutBrackets(string vec){
    return vec.substr(1, vec.length()-2);
}

vector<string> parseCommaSeparated(const string& str){
    vector<string> v;

    stringstream ss(str);

    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(substr);
    }

    return v;
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
    for(int i=0; i<eqn.length(); i++)
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

    for(int i=0; i<eqn.length(); i++)
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