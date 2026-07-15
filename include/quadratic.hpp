#pragma once
#include "constants.hpp"
#include "vector2.hpp"
#include <string>

struct Quadratic
{
      private:
	void init_solutions();

      public:
	real evaluate_at(real x);
	real a, b, c;
	cmplx roots[2];

	Vector2<real> vertex();
	real y_intercept();

	Quadratic(real leading_coeff, real second_coeff, real constant)
	{
		a = leading_coeff;
		b = second_coeff;
		c = constant;

		init_solutions();
	}

    Quadratic& operator += (const Quadratic &quad);
	Quadratic& operator -= (const Quadratic &quad);
	Quadratic operator + (const Quadratic &quad);
	Quadratic operator - (const Quadratic &quad);

    std::string display();
};