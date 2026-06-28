#pragma once
#include "constants.hpp"

namespace General
{   
    real identity(real x);
    real square(real x);
    real cube(real x);
    unsigned long long factorial(int n);
    real abs(real x);
    bool is_even(int x);
    bool is_int(real x);
    real int_pow(real x, int n);
    real exp2(int n);
    real log2_int(real x);
    real frexp(real x, int &e);
    real ldexp(real x, int e);
    real max(real x, real y);
    real min(real x, real y);
}