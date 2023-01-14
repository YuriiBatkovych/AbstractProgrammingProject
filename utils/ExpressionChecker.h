#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONCHECKER_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONCHECKER_H

#include <iostream>
#include "OperatorDeductor.h"
#include <stack>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class ExpressionChecker{
public:
    static string getVectorWithoutBrackets(string vec){
        return vec.substr(1, vec.length()-2);
    }

    static vector<string> parseCommaSeparated(const string& str){
        vector<string> v;

        stringstream ss(str);

        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            v.push_back(substr);
        }

        return v;
    }

    static bool ONP_correct(string eqn){
        stack<string> stos;
        for(int i=0; i<eqn.length(); i++)
        {
            if(OperatorDeductor::isONPOperand(eqn[i])){
                string operand = OperatorDeductor::getONPOperand(eqn, i);
                stos.push(operand);
            }
            else if(OperatorDeductor::isBiOperator(eqn[i])) {
                if (stos.empty())
                    return false;
                stos.pop();
            }
            else if(OperatorDeductor::isMonoOperator(eqn[i])){
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

    static bool Infix_correct(string eqn){
        int state = 0;
        int number_open_brackets=0;

        for(int i=0; i<eqn.length(); i++)
        {
            if(state==0){
                if(eqn[i]=='~')
                    state = 2;
                else if(OperatorDeductor::isOperand(eqn[i])) {
                    state = 1;
                    while(OperatorDeductor::isNumberChar(eqn[i]) ||
                          OperatorDeductor::isVariableNameChar(eqn[i]))
                        i++;
                    i--;
                }
                else if(eqn[i]=='[') {  //vector
                    state = 1;
                    while(OperatorDeductor::isVectorChar(eqn[i])&&eqn[i]!=']')
                        i++;
                }
                else if(eqn[i]=='(')
                    number_open_brackets++;
                else break;
            }
            else if(state==1){
                if(OperatorDeductor::isOperator(eqn[i]))
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
                } else if (OperatorDeductor::isOperand(eqn[i])) {
                    state = 1;
                    while(OperatorDeductor::isNumberChar(eqn[i]) ||
                          OperatorDeductor::isVariableNameChar(eqn[i]))
                        i++;
                    i--;
                }
                else if (eqn[i] != '~') break;
            }
        }
        return state==1 && number_open_brackets==0;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONCHECKER_H
