#pragma once

#include "constants.hpp"
#include <vector>

namespace NumberTheory
{
	real rising_factorial(real x, int n);
	real termial(real x);
	std::vector<int> prime_factors(int n);
	bool is_prime(int n);
	int nth_prime(int n);
}; // namespace NumberTheory