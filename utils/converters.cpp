#ifndef ABSTRACTPROGRAMMINGPROJECT_CONVERTERS
#define ABSTRACTPROGRAMMINGPROJECT_CONVERTERS

#include "expression_checkers.cpp"

template<typename InputType, typename OutputType>
OutputType convert(InputType input){}

template<typename NumericType>
NumericType convert(string value){
    if(!value.empty() && isNumber(value[0])) {
        return static_cast<NumericType>(atof(value.c_str()));
    }
    else cout<<"ERROR"<<endl;   ////TO DO
}

template<typename NumericType>
vector<NumericType> convertVector(string value){
    vector<string> vecOfNums = parseCommaSeparated(getVectorWithoutBrackets(value));
    vector<double> nums;
    nums.reserve(vecOfNums.size());
    for (auto & vecOfNum : vecOfNums)
        nums.push_back(static_cast<NumericType>(strtod(vecOfNum.c_str(), nullptr)));
    return nums;
}

template<>
string convert(string value){
    return value;
}

#endif