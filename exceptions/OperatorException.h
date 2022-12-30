#ifndef ABSTRACTPROGRAMMINGPROJECT_OPERATOREXCEPTION_H
#define ABSTRACTPROGRAMMINGPROJECT_OPERATOREXCEPTION_H

#include <iostream>

class OperatorException : public std::exception {
private:
    std::string message = "Operator is not supported.";
public:
    OperatorException(const std::string& msg = ""){
        this->message += msg;
    }
    const char* what () { return (this->message).c_str();}
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OPERATOREXCEPTION_H

