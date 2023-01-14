#ifndef ABSTRACTPROGRAMMINGPROJECT_CONVERTERS
#define ABSTRACTPROGRAMMINGPROJECT_CONVERTERS

#include "expression_checkers.cpp"
#include "ExpressionVector.h"
#include "../exceptions/NumericConvertionException.h"
#include "OperatorDeductor.h"

template<typename InputType, typename OutputType>
OutputType convert(InputType input){}

template<typename NumericType>
NumericType convert(string value){
    if(!value.empty() && OperatorDeductor::isNumber(value[0])) {
        return static_cast<NumericType>(atof(value.c_str()));
    }
    else throw NumericConvertionException();
}

template<>
string convert(string value){
    return value;
}


template<typename NumericType>
ExpressionVector<NumericType> convertVector(string value){
    vector<string> vecOfNums = parseCommaSeparated(getVectorWithoutBrackets(value));
    ExpressionVector<NumericType> nums;
    nums.reserve(vecOfNums.size());
    for (auto & vecOfNum : vecOfNums)
        nums.push_back(static_cast<NumericType>(strtod(vecOfNum.c_str(), nullptr)));
    return nums;
}
#endif