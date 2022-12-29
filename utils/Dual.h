#ifndef ABSTRACTPROGRAMMINGPROJECT_DUAL_H
#define ABSTRACTPROGRAMMINGPROJECT_DUAL_H

#include <iostream>
#include <cmath>

using namespace std;

class Dual {
private:
    double val;
    double der;

public:
    Dual(){
        this->val = 0;
        this->der = 0;
    };

    explicit Dual(double val):val(val), der(0){};

    Dual(double val, double der):val(val), der(der){};

    void setValue(double value){
        this->val = value;
    };

    void setDerivative(double derivative){
        this->der = derivative;
    };

    [[nodiscard]] double getValue() const{
        return val;
    };

    [[nodiscard]] double getDerivative() const{
        return der;
    };

    // operators
    friend Dual operator+(const Dual& u, const Dual& v);
    friend Dual operator-(const Dual& u, const Dual& v);
    friend Dual operator*(const Dual& u, const Dual& v);
    friend Dual operator/(const Dual& u, const Dual& v);

    Dual operator+=(const Dual& u){
        *this = *this+u;
        return *this;
    };

    Dual operator-=(const Dual& u){
        *this = *this-u;
        return *this;
    };

    Dual operator*=(const Dual& u){
        *this = *this*u;
        return *this;
    };

    Dual operator/=(const Dual& u){
        *this = *this/u;
        return *this;
    };

    friend std::ostream& operator<<(std::ostream& os, const Dual& a);

    // maths
    friend Dual sin(Dual d);
    friend Dual cos(Dual d);
    friend Dual exp(Dual d);
    friend Dual log(Dual d);
    friend Dual abs(Dual d);
    friend Dual pow(Dual d, double p);
};


Dual operator+(const Dual& u, const Dual& v){
    return {u.val+v.val, u.der+v.der};
}

Dual operator-(const Dual& u, const Dual& v){
    return {u.val-v.val, u.der-v.der};
}

Dual operator*(const Dual& u, const Dual& v){
    return {u.val*v.val, u.der*v.val+u.val*v.der};
}

Dual operator/(const Dual& u, const Dual& v){
    return {u.val/v.val, (u.der*v.val-u.val*v.der)/(v.val*v.val)};
}

std::ostream& operator<<(std::ostream& os, const Dual& a){
    os << a.val;
    return os;
}


Dual operator+(const double value, const Dual& v){
    Dual d(value);
    return d+v;
}

Dual operator-(const double value, const Dual& v){
    Dual d(value);
    return d-v;
}

Dual operator*(const double value, const Dual& v){
    Dual d(value);
    return d*v;
}

Dual operator/(const double value, const Dual& v){
    Dual d(value);
    return d/v;
}

Dual sin(Dual d){
    return {::sin(d.val), d.der*::cos(d.val)};
}

Dual cos(Dual d){
    return {::cos(d.val), -d.der*::sin(d.val)};
}

Dual exp(Dual d){
    return {::exp(d.val), d.der*::exp(d.val)};
}

Dual log(Dual d){
    return {::log(d.val), d.der/d.val};
}

Dual abs(Dual d){
    int sign = d.val==0 ? 0 : d.val/::abs(d.val);
    return {static_cast<double>(::abs(d.val)), d.der*sign};
}

Dual pow(Dual d, double p){
    return {::pow(d.val, p), p*d.der*::pow(d.val, p-1)};
}

#endif //ABSTRACTPROGRAMMINGPROJECT_DUAL_H
