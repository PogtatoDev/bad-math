#pragma once

#include "constants.hpp"
#include <vector>

namespace ComplexMath
{
	real arg(cmplx z);
	cmplx complex_exp(cmplx z);
	cmplx complex_log(cmplx z);
	cmplx complex_sqrt(real x);
	void solve_quadratic(real a, real b, real c, cmplx solutions[2]);
	cmplx complex_square(cmplx z);
	cmplx complex_sin(cmplx z);
	cmplx complex_cos(cmplx z);
	cmplx complex_tan(cmplx z);
	cmplx complex_pow(cmplx z, cmplx w);
	cmplx complex_log_gamma(cmplx z);
	cmplx complex_gamma(cmplx z);
	cmplx eta(cmplx s);
}; // namespace ComplexMath