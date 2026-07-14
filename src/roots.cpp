
#include "../include/roots.hpp"

#include "../include/constants.hpp"
#include "../include/expo.hpp"
#include "../include/general.hpp"
#include "../include/logarithm.hpp"
#include "../include/lookup/sqrt_table.hpp"
#include "../include/rootfinding.hpp"

namespace Roots
{
	namespace e = Expo;
	namespace l = Logarithm;
	real sqrt(real x)
	{
		if (x < 0)
			return std::numeric_limits<real>::quiet_NaN();
		if (x == 0)
			return 0;

		if (General::is_int(x) && x < 2048)
		{
			int n = round(x);
			return sqrt_table[n];
		}

		int k;
		real m = General::frexp(x, k);

		m *= 1 + (k & 1);
		k -= (k & 1);

		real y = 0.41731 + 0.59016 * m;

		y = 0.5 * (y + m / y);
		y = 0.5 * (y + m / y);
		y = 0.5 * (y + m / y);

		return General::ldexp(y, k / 2);
	}

	real log_root(real x, int n)
	{
		if (General::is_even(n) && x < 0)
			return std::numeric_limits<real>::quiet_NaN();
		return e::exp(1.0 / n * l::log(x));
	}

	real nth_root(real x, int n)
	{
		if (General::is_even(n) && x < 0)
			return std::numeric_limits<real>::quiet_NaN();
		if (std::abs(x) < const_limits::LIM_EPS)
			return 0;
		double guess = General::exp2(General::log2_int(x) / n);
		auto f = [x, n](real t) { return General::int_pow(t, n) - x; };
		auto Df = [n](real t)
		{ return n * General::int_pow(t, n - 1); };
		return RootFinding::manual_newton(f, Df, guess);
	}
} // namespace Roots