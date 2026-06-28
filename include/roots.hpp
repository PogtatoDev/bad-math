#pragma once

#include "constants.hpp"

namespace Roots
{
	real sqrt(real x);
	real bisection_sqrt(real x, real acc);
	real log_root(real x, int n);
	real nth_root(real x, int n);
	real bisection_nth_root(real x, int n, real acc);
} // namespace Roots