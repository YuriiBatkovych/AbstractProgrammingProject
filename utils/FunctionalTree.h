#ifndef ABSTRACTPROGRAMMINGPROJECT_FUNCTIONALTREE_H
#define ABSTRACTPROGRAMMINGPROJECT_FUNCTIONALTREE_H

#include <iostream>
#include "ExpVectorTree.h"
#include <list>
#include <algorithm>
#include <cstdarg>
#include "Dual.h"

template<typename Tensor, int N_arguments>
class FunctionalTree : public ExpressionTree<Tensor>{
private:
    list<string> argument_names;

    bool variable_exist(string variable){
        return std::find(argument_names.begin(), argument_names.end(), variable) != argument_names.end();
    }

protected:
    string getVariableName(string eqn, int& i){
        string variable;

        while(isVariableNameChar(eqn[i])){
            variable += eqn[i];
            i++;
        }

        if(!variable_exist(variable)){
            argument_names.push_back(variable);
            if(argument_names.size()>N_arguments)
                cout<<"Error"<<endl;
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

public:

    Dual<Tensor> computeFunctional(string derivative_variable, Tensor arg, ...){
        if(this->root == nullptr)
            return Dual<Tensor>();

        va_list args;
        va_start(args, arg);

        auto* copyRoot = new TreeNode<string>(*(this->root));
        copyRoot->set_derivative(derivative_variable);

        for(string& var : argument_names){
            copyRoot->replace(var, std::to_string(arg));
            arg = va_arg(args, Tensor);
        }

        va_end(args);
        return copyRoot->template computeFunctional<Tensor>();
    }
};


#endif //ABSTRACTPROGRAMMINGPROJECT_FUNCTIONALTREE_H