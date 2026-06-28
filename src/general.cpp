#include "../include/general.hpp"

#include <cmath>
#include <bit>

namespace General
{
	real identity(real x)
	{
		return x;
	}

	real square(real x)
	{
		return x * x;
	}

	real cube(real x)
	{
		return x * x * x;
	}

	unsigned long long int factorial(int n)
	{
		if (n < 20)
			return constants::FACTORIAL[n];

		long long int prod = 1;
		for (int k = 1; k <= n; k++)
		{
			prod *= k;
		}

		return prod;
	}

	real abs(real x)
	{
		if (x < 0)
			return -x;
		return x;
	}

	bool is_even(int x)
	{
		if (x % 2 == 0)
			return true;
		return false;
	}

	bool is_int(real x)
	{
		if (General::abs(x - round(x)) < const_limits::LIM_EPS)
			return true;
		return false;
	}

	real int_pow(real x, int n)
	{
		if (n == 0)
			return 1;
		else if (n == 1)
			return x;
		else if (n < 0)
			return 1.0 / int_pow(x, -n);
		else if (is_even(n))
			return int_pow(square(x), n / 2);
		else
			return x * int_pow(square(x), (n - 1) / 2);
	}

	real exp2(int n)
	{
		uint64_t bits = uint64_t(n + 1023) << 52;
		return std::bit_cast<double>(bits);
	}

	real log2_int(real x)
	{
		unsigned int n = std::round(x);
		return std::bit_width(n) - 1;
	}

	real frexp(real x, int &e)
	{
		union
		{
			real d;
			uint64_t u;
		} v{x};

		uint64_t bits = v.u;

		uint64_t k = (bits >> 52) & 0x7FF;
		if (k == 0)
		{
			e = 0;
			return x;
		}

		bits &= ~(0x7FFULL << 52);
		bits |= (1022ULL << 52);
		v.u = bits;
		e = (int)k - 1022;

		return v.d;
	}

	real ldexp(real x, int e)
	{
		union
		{
			real d;
			uint64_t u;
		} v{ x };

		uint64_t k = (v.u >> 52) & 0x7FF;

		if (k == 0 || k == 0x7FF)
			return x;

		k += e;

		if (k >= 0x7FF)
		{
			v.u |= (0x7FFULL << 52);
			return v.d;
		}

		if ((int64_t)k <= 0)
		{
			return 0.0;
		}

		v.u &= ~(0x7FFULL << 52);
		v.u |= k << 52;

		return v.d;
	}
	
}; // namespace General