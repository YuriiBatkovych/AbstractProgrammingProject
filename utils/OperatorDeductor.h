#ifndef ABSTRACTPROGRAMMINGPROJECT_OPERATORDEDUCTOR_H
#define ABSTRACTPROGRAMMINGPROJECT_OPERATORDEDUCTOR_H

#include <iostream>
#include "../exceptions/OperatorException.h"
using namespace std;

class OperatorDeductor{
public:
    template<typename ResultType>
    static ResultType calculate(char _operator, ResultType left_arg, ResultType right_arg){
        switch (_operator) {
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
                throw OperatorException();
        }
    }

    template<typename ArgType>
    static ArgType calculate(char _operator, ArgType arg){
        switch (_operator) {
            case '~':
                return -arg;
            default:
                throw OperatorException();
        }
    }

    static bool isOperand(char ch){ return ch >= '0' && ch <= '9' || ch>='A' && ch<='Z' || ch>='a' && ch<='z';}

    static bool isONPOperand(char ch){
        return ch == '{' || ch == '[';
    }

    static bool isLetter(char ch){
        return ch>='A' && ch<='Z' || ch>='a' && ch<='z';
    }

    static bool isVariableNameChar(char ch){
        return ch >= '0' && ch <= '9' || ch>='A' && ch<='Z' || ch>='a' && ch<='z' || ch=='_';
    }

    static bool isNumber(char ch){
        return ch >= '0' && ch <= '9';
    }

    static bool isNumberChar(char ch){
        return ch >= '0' && ch <= '9' || ch == '.';
    }

    static bool isDoubleNumber(const string& s){
        return s.find('.') != std::string::npos;
    }

    static bool isVectorChar(char ch){
        return isNumberChar(ch) || ch=='[' || ch==']' || ch==',';
    }

    static bool isOperator(char ch){
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'
               || ch == '%';
    }

    static bool isMonoOperator(char ch){
        return ch == '~';
    }

    static bool isBiOperator(char ch){
        return isOperator(ch) && !isMonoOperator(ch);
    }

    static bool isVector(string value){
        return value[0] == '[' && value[value.length()-1] == ']';
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OPERATORDEDUCTOR_H
