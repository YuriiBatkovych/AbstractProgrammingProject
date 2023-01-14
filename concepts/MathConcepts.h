#ifndef ABSTRACTPROGRAMMINGPROJECT_MATHCONCEPTS_H
#define ABSTRACTPROGRAMMINGPROJECT_MATHCONCEPTS_H

template <typename X>
concept Addable = requires ( X a , X b ) { a + b; };

template <typename X>
concept Subtractable = requires ( X a , X b ) { a - b; };

template <typename X>
concept Multipliable = requires ( X a , X b ) { a*b; };

template <typename X>
concept Divisible = requires ( X a , X b ) { a/b; };

template <typename X>
concept Negated = requires ( X a ) { -a; };

template <typename X>
concept AllOperators = requires (X a) { Addable<X> && Subtractable<X> && Multipliable<X> &&
        Divisible<X> && Negated<X>; };

#endif //ABSTRACTPROGRAMMINGPROJECT_MATHCONCEPTS_H
