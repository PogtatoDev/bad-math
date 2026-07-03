#include "../include/quadratic.hpp"
#include "../include/complexmath.hpp"
#include "../include/vector2.hpp"

void quadratic::init_solutions() 
{
    ComplexMath::solve_quadratic(a, b, c, solutions);
}

vector2 quadratic::vertex()
{
    auto f = [this](real t)
    { return a * (t*t) + b*t + c; };

    vector2 vertex;
    vertex.x = -b / (2 * a);
    vertex.y = f(-b / (2 * a));

    return vertex;
}