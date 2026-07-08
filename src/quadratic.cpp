#include "../include/quadratic.hpp"
#include "../include/complexmath.hpp"
#include "../include/vector2.hpp"
#include <string>
#include <sstream>


void Quadratic::init_solutions()
{
	ComplexMath::solve_quadratic(a, b, c, roots);
}

real Quadratic::evaluate_at(real x)
{
	return a * (x * x) + b * x + c;
}

Vector2<real> Quadratic::vertex()
{
    if (a == 0)
		return Vector2(std::numeric_limits<real>::quiet_NaN(), std::numeric_limits<real>::quiet_NaN());
	real x = -b / (2 * a);
	real y = evaluate_at(-b / (2 * a));
	Vector2<real> vertex(x, y);

	return vertex;
}

real Quadratic::y_intercept()
{
	return c;
}

Quadratic& Quadratic::operator+=(const Quadratic &quad)
{
    a += quad.a;
    b += quad.b;
    c += quad.c;

    return (*this);
}

Quadratic& Quadratic::operator-=(const Quadratic &quad)
{
    a -= quad.a;
    b -= quad.b;
    c -= quad.c;

    return (*this);
}

Quadratic Quadratic::operator+(const Quadratic &quad)
{
    Quadratic temp(*this);
	temp += quad;
	return temp;
}
Quadratic Quadratic::operator-(const Quadratic &quad)
{
    Quadratic temp(*this);
	temp -= quad;
	return temp;
}
std::string Quadratic::display()
{
    std::ostringstream stream;
    stream << a << "x^2 + " << b << "x + " << c;
    return stream.str();
}