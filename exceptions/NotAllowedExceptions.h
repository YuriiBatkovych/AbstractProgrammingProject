#ifndef ABSTRACTPROGRAMMINGPROJECT_NOTALLOWEDEXCEPTIONS_H
#define ABSTRACTPROGRAMMINGPROJECT_NOTALLOWEDEXCEPTIONS_H

#include <iostream>
using namespace std;

class VectorsNotAllowedException : public std::exception {
private:
    std::string message = "Vectors are not allowed on that type of expression.";
public:
    VectorsNotAllowedException(const std::string& msg = ""){
        this->message += msg;
    }
    const char* what () { return (this->message).c_str();}
};

class VariablesNotAllowedException : public std::exception {
private:
    string message = "Literal variables are not allowed on that type of expression.";
public:
    VariablesNotAllowedException(const std::string& msg = ""){
        this->message += msg;
    }
    const char* what () { return (this->message).c_str();}
};

#endif //ABSTRACTPROGRAMMINGPROJECT_NOTALLOWEDEXCEPTIONS_H
