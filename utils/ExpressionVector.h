#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONVECTOR_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONVECTOR_H

#include <iostream>
#include <vector>
#include <cmath>

template<typename NumericType>
class ExpressionVector : public std::vector<NumericType>{
public:
    template<typename NumericLeft, typename NumericRight>
    friend ExpressionVector<NumericLeft> operator+(const ExpressionVector<NumericLeft>& u,
                                                   const ExpressionVector<NumericRight>& v);

    template<typename NumericLeft, typename NumericRight>
    friend ExpressionVector<NumericLeft> operator-(const ExpressionVector<NumericLeft>& u,
                                                   const ExpressionVector<NumericRight>& v);

    template<typename NumericLeft, typename NumericRight>
    friend ExpressionVector<NumericLeft> operator*(const ExpressionVector<NumericLeft>& u,
                                                   const ExpressionVector<NumericRight>& v);

    template<typename NumericLeft, typename NumericRight>
    friend ExpressionVector<NumericLeft> operator/(const ExpressionVector<NumericLeft>& u,
                                                   const ExpressionVector<NumericRight>& v);

    template<typename NumericRight>
    ExpressionVector<NumericType> operator+=(const ExpressionVector<NumericRight>& u){
        *this = *this+u;
        return *this;
    };

    template<typename NumericRight>
    ExpressionVector<NumericType> operator-=(const ExpressionVector<NumericRight>& u){
        *this = *this-u;
        return *this;
    };

    template<typename NumericRight>
    ExpressionVector<NumericType> operator*=(const ExpressionVector<NumericRight>& u){
        *this = *this*u;
        return *this;
    };

    template<typename NumericRight>
    ExpressionVector<NumericType> operator/=(const ExpressionVector<NumericRight>& u){
        *this = *this/u;
        return *this;
    };

    ExpressionVector<NumericType> operator-(){
        for(size_t i=0; i<this->size(); i++)
            (*this)[i] = - (*this)[i];
        return *this;
    };

    template<typename Numeric>
    friend std::ostream& operator<<(std::ostream& os, const ExpressionVector<Numeric>& a);


    template<typename Numeric>
    friend ExpressionVector<Numeric> pow(ExpressionVector<Numeric> d, double p);

    template<typename Numeric>
    friend ExpressionVector<Numeric> pow(ExpressionVector<Numeric> left, ExpressionVector<Numeric> right);
};

template<typename NumericLeft, typename NumericRight>
ExpressionVector<NumericLeft> operator+(const ExpressionVector<NumericLeft>& u,
                                        const ExpressionVector<NumericRight>& v){
    ExpressionVector<NumericLeft> result;

    if(u.size() == v.size()){
        for(size_t i=0; i<u.size(); i++)
            result.push_back(u[i]+v[i]);
    }

    return result;
}

template<typename NumericLeft, typename NumericRight>
ExpressionVector<NumericLeft> operator-(const ExpressionVector<NumericLeft>& u,
                                        const ExpressionVector<NumericRight>& v){
    ExpressionVector<NumericLeft> result;

    if(u.size() == v.size()){
        for(size_t i=0; i<u.size(); i++)
            result.push_back(u[i]-v[i]);
    }

    return result;
}

template<typename NumericLeft, typename NumericRight>
ExpressionVector<NumericLeft> operator*(const ExpressionVector<NumericLeft>& u,
                                        const ExpressionVector<NumericRight>& v){
    ExpressionVector<NumericLeft> result;

    if(u.size() == v.size()){
        for(size_t i=0; i<u.size(); i++)
            result.push_back(u[i]*v[i]);
    }

    return result;
}

template<typename NumericLeft, typename NumericRight>
ExpressionVector<NumericLeft> operator/(const ExpressionVector<NumericLeft>& u,
                                        const ExpressionVector<NumericRight>& v){
    ExpressionVector<NumericLeft> result;

    if(u.size() == v.size()){
        for(size_t i=0; i<u.size(); i++)
            result.push_back(u[i]/v[i]);
    }

    return result;
}

template<typename Numeric>
std::ostream& operator<<(std::ostream& os, const ExpressionVector<Numeric>& a){
    os<<"[";
    for(size_t i=0; i<a.size(); i++) {
        os << a[i];
        if(i!=a.size()-1){
            os<<",";
        }
    }
    os<<"]";
    return os;
}


template<typename Numeric>
ExpressionVector<Numeric> pow(ExpressionVector<Numeric> d, double p){
    ExpressionVector<Numeric> result;

    for(size_t i=0; i<d.size(); i++)
        result.push_back(::pow(d[i], p));

    return result;
}

template<typename Numeric>
ExpressionVector<Numeric> pow(ExpressionVector<Numeric> left, ExpressionVector<Numeric> right){
    ExpressionVector<Numeric> result;
    if(left.size() == right.size()){
        for(size_t i=0; i<left.size(); i++)
            result.push_back(::pow(left[i], right[i]));
    }
    return result;
}


#endif //ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONVECTOR_H
