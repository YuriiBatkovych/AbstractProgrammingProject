#include <iostream>
#include "compute_tests.h"
#include "function_tests.h"
#include "vector_tests.h"

using namespace std;

int main(){
    test_function_zero();
    test_compute_ordinary();
    test_compute_zero();
    test_compute_addable();
    test_compute_division();
    test_vector_ordinary();
    test_vector_multiply();
    test_vector_zero();
    test_vector_sub();
}

