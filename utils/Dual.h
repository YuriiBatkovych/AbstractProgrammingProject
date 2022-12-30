#ifndef ABSTRACTPROGRAMMINGPROJECT_DUAL_H
#define ABSTRACTPROGRAMMINGPROJECT_DUAL_H

#include <iostream>
#include <cmath>

using namespace std;

template<typename Numeric>
class Dual {
private:
    Numeric val;
    Numeric der;

public:
    Dual(){
        this->val = 0;
        this->der = 0;
    };

    explicit Dual(Numeric val):val(val), der(0){};

    Dual(Numeric val, Numeric der):val(val), der(der){};

    void setValue(Numeric value){
        this->val = value;
    };

    void setDerivative(Numeric derivative){
        this->der = derivative;
    };

    [[nodiscard]] Numeric getValue() const{
        return val;
    };

    [[nodiscard]] Numeric getDerivative() const{
        return der;
    };

    // operators
    template<typename NumericLeft, typename NumericRight>
    friend Dual<NumericLeft> operator+(const Dual<NumericLeft>& u, const Dual<NumericRight>& v);

    template<typename NumericLeft, typename NumericRight>
    friend Dual<NumericLeft> operator-(const Dual<NumericLeft>& u, const Dual<NumericRight>& v);

    template<typename NumericLeft, typename NumericRight>
    friend Dual<NumericLeft> operator*(const Dual<NumericLeft>& u, const Dual<NumericRight>& v);

    template<typename NumericLeft, typename NumericRight>
    friend Dual<NumericLeft> operator/(const Dual<NumericLeft>& u, const Dual<NumericRight>& v);

    template<typename NumericRight>
    Dual<Numeric> operator+=(const Dual<NumericRight>& u){
        *this = *this+u;
        return *this;
    };

    template<typename NumericRight>
    Dual<Numeric> operator-=(const Dual<NumericRight>& u){
        *this = *this-u;
        return *this;
    };

    template<typename NumericRight>
    Dual<Numeric> operator*=(const Dual<NumericRight>& u){
        *this = *this*u;
        return *this;
    };

    template<typename NumericRight>
    Dual<Numeric> operator/=(const Dual<NumericRight>& u){
        *this = *this/u;
        return *this;
    };

    Dual<Numeric> operator-(){
        this->val = -val;
        this->der = -der;
        return *this;
    };

    template<typename NumericType>
    friend std::ostream& operator<<(std::ostream& os, const Dual<NumericType>& a);

    // maths
    template<typename NumericType>
    friend Dual<NumericType> sin(Dual<NumericType> d);

    template<typename NumericType>
    friend Dual<NumericType> cos(Dual<NumericType> d);

    template<typename NumericType>
    friend Dual<NumericType> exp(Dual<NumericType> d);

    template<typename NumericType>
    friend Dual<NumericType> log(Dual<NumericType> d);

    template<typename NumericType>
    friend Dual<NumericType> abs(Dual<NumericType> d);

    template<typename NumericType>
    friend Dual<NumericType> pow(Dual<NumericType> d, double p);

    template<typename NumericType>
    friend Dual<NumericType> pow(Dual<NumericType> left, Dual<NumericType> right);
};

template<typename NumericLeft, typename NumericRight>
Dual<NumericLeft> operator+(const Dual<NumericLeft>& u, const Dual<NumericRight>& v){
    return {u.val+v.val, u.der+v.der};
}

template<typename NumericLeft, typename NumericRight>
Dual<NumericLeft> operator-(const Dual<NumericLeft>& u, const Dual<NumericRight>& v){
    return {u.val-v.val, u.der-v.der};
}

template<typename NumericLeft, typename NumericRight>
Dual<NumericLeft> operator*(const Dual<NumericLeft>& u, const Dual<NumericRight>& v){
    return {u.val*v.val, u.der*v.val+u.val*v.der};
}

template<typename NumericLeft, typename NumericRight>
Dual<NumericLeft> operator/(const Dual<NumericLeft>& u, const Dual<NumericRight>& v){
    return {u.val/v.val, (u.der*v.val-u.val*v.der)/(v.val*v.val)};
}

template<typename Numeric>
std::ostream& operator<<(std::ostream& os, const Dual<Numeric>& a){
    os << a.val;
    return os;
}

template<typename NumericLeft, typename NumericRight>
Dual<NumericLeft> operator+(const NumericLeft value, const Dual<NumericRight>& v){
    Dual<NumericLeft> d(value);
    return d+v;
}

template<typename NumericLeft, typename NumericRight>
Dual<NumericLeft> operator-(const NumericLeft value, const Dual<NumericRight>& v){
    Dual<NumericLeft> d(value);
    return d-v;
}

template<typename NumericLeft, typename NumericRight>
Dual<NumericLeft> operator*(const NumericLeft value, const Dual<NumericRight>& v){
    Dual<NumericLeft> d(value);
    return d*v;
}

template<typename NumericLeft, typename NumericRight>
Dual<NumericLeft> operator/(const NumericLeft value, const Dual<NumericRight>& v){
    Dual<NumericLeft> d(value);
    return d/v;
}

template<typename Numeric>
Dual<Numeric> sin(Dual<Numeric> d){
    return {::sin(d.val), d.der*::cos(d.val)};
}

template<typename Numeric>
Dual<Numeric> cos(Dual<Numeric> d){
    return {::cos(d.val), -d.der*::sin(d.val)};
}

template<typename Numeric>
Dual<Numeric> exp(Dual<Numeric> d){
    return {::exp(d.val), d.der*::exp(d.val)};
}

template<typename Numeric>
Dual<Numeric> log(Dual<Numeric> d){
    return {::log(d.val), d.der/d.val};
}

template<typename Numeric>
Dual<Numeric> abs(Dual<Numeric> d){
    int sign = d.val==0 ? 0 : d.val/::abs(d.val);
    return {static_cast<double>(::abs(d.val)), d.der*sign};
}

template<typename Numeric>
Dual<Numeric> pow(Dual<Numeric> d, double p){
    return {::pow(d.val, p), p*d.der*::pow(d.val, p-1)};
}

template<typename Numeric>
Dual<Numeric> pow(Dual<Numeric> left, Dual<Numeric> right){
    return {::pow(left.val, right.val), right.val*left.der*::pow(left.val, right.val-1)};
}

#endif //ABSTRACTPROGRAMMINGPROJECT_DUAL_H
