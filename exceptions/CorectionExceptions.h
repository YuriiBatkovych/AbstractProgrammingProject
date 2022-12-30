#ifndef ABSTRACTPROGRAMMINGPROJECT_CORECTIONEXCEPTIONS_H
#define ABSTRACTPROGRAMMINGPROJECT_CORECTIONEXCEPTIONS_H

#include <iostream>

class InfixExpressionException : public std::exception {
private:
    std::string message = "Infix Expression is not correct.";
public:
    InfixExpressionException(const std::string& msg = ""){
        this->message += msg;
    }
    const char* what () { return (this->message).c_str();}
};


class ONPExpressionException : public std::exception {
private:
    std::string message = "ONP Expression is not correct.";
public:
    ONPExpressionException(const std::string& msg = ""){
        this->message += msg;
    }
    const char* what () { return (this->message).c_str();}
};

#endif //ABSTRACTPROGRAMMINGPROJECT_CORECTIONEXCEPTIONS_H
