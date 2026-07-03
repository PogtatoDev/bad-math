#pragma once
#include "constants.hpp"
#include "vector2.hpp"

struct quadratic
{
	void init_solutions();
      public:
	real a;
	real b;
	real c;
	cmplx solutions[2];

	vector2 vertex();
};