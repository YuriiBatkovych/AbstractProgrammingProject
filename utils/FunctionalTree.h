#ifndef ABSTRACTPROGRAMMINGPROJECT_FUNCTIONALTREE_H
#define ABSTRACTPROGRAMMINGPROJECT_FUNCTIONALTREE_H

#include <iostream>
#include "ExpVectorTree.h"
#include <list>
#include <algorithm>
#include <cstdarg>
#include <utility>
#include "Dual.h"
#include "NodeCreators.h"
#include "../concepts/MathConcepts.h"
#include "OperatorDeductor.h"

template<typename Tensor, int N_arguments>
requires AllOperators<Tensor>
class FunctionalTree : public ExpressionTree<Tensor, FunctionalNodeCreator>{
private:
    list<string> argument_names;

    bool variable_exist(const string& variable){
        return std::find(argument_names.begin(), argument_names.end(), variable) != argument_names.end();
    }

protected:
    string getVariableName(const string& eqn, int& i){
        string variable;

        while(OperatorDeductor::isVariableNameChar(eqn[i])){
            variable += eqn[i];
            i++;
        }

        if(!variable_exist(variable)){
            argument_names.push_back(variable);
            if(argument_names.size()>N_arguments)
                throw TooMuchArgumentsException();
        }

        variable = '{' + variable + '}';
        i--;

        return variable;
    }

    string getNumber(const string& eqn, int& i){
        string number;

        while (OperatorDeductor::isNumberChar(eqn[i])){
            number += eqn[i];
            i++;
        }
        number = '{' + number + '}';
        i--;
        return number;
    }

public:

    FunctionalTree(): ExpressionTree<Tensor, FunctionalNodeCreator>(){}
    [[maybe_unused]] FunctionalTree(const ExpressionTree<Tensor, FunctionalNodeCreator>& expTree):
            ExpressionTree<Tensor, FunctionalNodeCreator>(expTree){};

    Dual<Tensor> compute(string derivative_variable, Tensor arg, ...){
        if(this->root == nullptr)
            return Dual<Tensor>();

        va_list args;
        va_start(args, arg);

        auto* copyRoot = new FunctionalNode<string>(*(this->root));
        copyRoot->set_derivative(std::move(derivative_variable));

        for(string& var : argument_names){
            copyRoot->replace(var, std::to_string(arg));
            arg = va_arg(args, Tensor);
        }

        va_end(args);
        return copyRoot->template computeFunctional<Tensor>();
    }
};


#endif //ABSTRACTPROGRAMMINGPROJECT_FUNCTIONALTREE_H
