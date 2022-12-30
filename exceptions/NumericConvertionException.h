#ifndef ABSTRACTPROGRAMMINGPROJECT_NUMERICCONVERTIONEXCEPTION_H
#define ABSTRACTPROGRAMMINGPROJECT_NUMERICCONVERTIONEXCEPTION_H

#include <iostream>

class NumericConvertionException : public std::exception {
private:
    std::string message = "Value to convert is empty or not numeric.";
public:
    NumericConvertionException(const std::string& msg = ""){
        this->message += msg;
    }
    const char* what () { return (this->message).c_str();}
};

#endif //ABSTRACTPROGRAMMINGPROJECT_NUMERICCONVERTIONEXCEPTION_H
