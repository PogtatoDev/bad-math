#include "../include/numbertheory.hpp"

#include "../include/constants.hpp"
#include "../include/general.hpp"
#include "../include/roots.hpp"

namespace NumberTheory
{
	real rising_factorial(real x, int n)
	{
		real prod = 1;

		for (int i = 0; i <= n - 1; i++)
		{
			prod *= (x + i);
		}

		return prod;
	}

	real termial(real x)
	{ return x * (x + 1) / 2.0; }

	std::vector<int> prime_factors(int n)
	{
		real root_n = Roots::sqrt(n);

		std::vector<int> factors = {};
		for (int i = 2; i <= root_n; i++)
		{
			while (n % i == 0)
			{
				factors.push_back(i);
				n = n / i;
			}
		}

		return factors;
	}

	bool is_prime(int n)
	{
		if (n < 2)
			return false;

		if (General::is_even(n))
			return n == 2;

		for (int i = 3; i <= n / i; i += 2)
		{
			if (n % i == 0)
				return false;
		}

		return true;
	}

	int nth_prime(int n)
	{
		int count = 0;
		int k = 1;

		while (count < n)
		{
			k++;
			if (is_prime(k))
			{
				count++;
			}
		}
		return k;
	}

}; // namespace NumberTheory