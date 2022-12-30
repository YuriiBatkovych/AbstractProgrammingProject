#ifndef ABSTRACTPROGRAMMINGPROJECT_ARGUMENTSEXCEPTION_H
#define ABSTRACTPROGRAMMINGPROJECT_ARGUMENTSEXCEPTION_H

#include <iostream>

class TooFewArgumentsException : public std::exception {
private:
    std::string message = "There are no necessary arguments to perform an operation.";
public:
    TooFewArgumentsException(const std::string& msg = ""){
        this->message += msg;
    }
    const char* what () { return (this->message).c_str();}
};


class TooMuchArgumentsException : public std::exception {
private:
    std::string message = "There are more arguments on the expression then defined.";
public:
    TooMuchArgumentsException(const std::string& msg = ""){
        this->message += msg;
    }
    const char* what () { return (this->message).c_str();}
};

#endif //ABSTRACTPROGRAMMINGPROJECT_ARGUMENTSEXCEPTION_H
