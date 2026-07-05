#include "../include/linear.hpp"
#include "../include/constants.hpp"
#include "../include/roots.hpp"
#include <limits>

real Linear::evaluate_at(real x)
{
    return m * x + b;
}

real Linear::x_intercept()
{
    if (m == 0)
        return std::numeric_limits<real>::quiet_NaN();

    return -b / m;
}

real Linear::y_intercept()
{
    return b;
}

real Linear::distance_between(real x1, real x2)
{
    real xdiff = x2 - x1;
    real ydiff = evaluate_at(x2) - evaluate_at(x1);
    

    return Roots::sqrt(xdiff * xdiff + ydiff * ydiff);
}

std::string Linear::display()
{
    std::ostringstream stream;
    stream << m << "x + " << b;
    return stream.str();
}


real solve_linear(Linear l1, Linear l2)
{
    real a = l1.m;
    real b = l1.b;
    real c = l2.m;
    real d = l2.b;

    if (a == c)
        return std::numeric_limits<real>::quiet_NaN();

    return (d-b) / (a-c);
}