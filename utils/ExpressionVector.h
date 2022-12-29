#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONVECTOR_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONVECTOR_H

#include <iostream>
#include <vector>

template<typename NumericType>
class ExpressionVector : public std::vector<NumericType>{
public:
    template<typename NumericLeft, typename NumericRight>
    friend ExpressionVector<NumericLeft> operator+(const ExpressionVector<NumericLeft>& u,
                                                   const ExpressionVector<NumericRight>& v);

    template<typename NumericLeft, typename NumericRight>
    friend Dual<NumericLeft> operator-(const Dual<NumericLeft>& u, const Dual<NumericRight>& v);

    template<typename NumericLeft, typename NumericRight>
    friend Dual<NumericLeft> operator*(const Dual<NumericLeft>& u, const Dual<NumericRight>& v);

    template<typename NumericLeft, typename NumericRight>
    friend Dual<NumericLeft> operator/(const Dual<NumericLeft>& u, const Dual<NumericRight>& v);

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

    template<typename Numeric>
    friend std::ostream& operator<<(std::ostream& os, const ExpressionVector<Numeric>& a);
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


#endif //ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONVECTOR_H
