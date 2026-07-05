#pragma once
#include "constants.hpp"
#include <string>

struct Linear 
{
    real m, b;
    Linear(real slope, real offset) 
    {
        m = slope;
        b = offset;
    }
    real evaluate_at(real x);
    real x_intercept();
    real y_intercept();
    real distance_between(real x1, real x2);
    std::string display();
};

real solve_linear(Linear l1, Linear l2);