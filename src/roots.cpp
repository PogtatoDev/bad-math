
#include "../include/roots.hpp"

#include "../include/constants.hpp"
#include "../include/expo.hpp"
#include "../include/general.hpp"
#include "../include/rootfinding.hpp"
#include "../include/logarithm.hpp"

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

		int k;
		real m = General::frexp(x, k);

		m *= 1 + (k & 1);
		k -= (k & 1);

		real y = 0.41731 + 0.59016 * m;

		y = 0.5 * (y + m/y);
    	y = 0.5 * (y + m/y);
		y = 0.5 * (y + m/y);

		return General::ldexp(m, k/2);
	}

	real bisection_sqrt(real x, real acc = 0.01)
	{
		auto f = [x](real t) { return General::square(t) - x; };

		return RootFinding::auto_bisection_method(f, acc);
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
		double guess = x / n;
		auto f = [x, n](real t) { return General::int_pow(t, n) - x; };
		auto Df = [n](real t)
		{ return n * General::int_pow(t, n - 1); };
		return RootFinding::manual_newton(f, Df, x / n);
	}

	real bisection_nth_root(real x, int n, real acc = 0.01)
	{
		auto f = [x, n](real t) { return General::int_pow(t, n) - x; };

		return RootFinding::auto_bisection_method(f, acc);
	}
} // namespace Roots