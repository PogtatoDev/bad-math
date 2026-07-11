#include "../include/invtrig.hpp"

#include "../include/constants.hpp"
#include "../include/rootfinding.hpp"
#include "../include/trig.hpp"
#include "../include/roots.hpp"
#include <limits>


namespace InvTrig
{
	real asin(real x)
	{
		if (std::abs(x) > 1)
		{
			return std::numeric_limits<real>::quiet_NaN();
		}

		auto f = [x](real t) { return Trig::sin(t) - x; };
		auto Df = [](real t) { return Trig::cos(t); };

		real guess = x / constants::TAU;

		return RootFinding::manual_newton(f, Df, guess);
	}

	real acos(real x)
	{
		return (constants::PI_2) - asin(x);
	}

	real atan(real x)
	{
		constexpr real A = 0.0776509570923569;
		constexpr real B = -0.287434475393028;
		constexpr real C = (constants::PI_4 - A - B);

		bool st1 = (x < -1);
		bool bt1 = (x > 1);
		
		if (General::tol(x))
    		return 0;

		if (bt1 || st1)
			x = 1.0 / x;

		real x2 = x*x;
		real p = ((A*x2 + B)*x2 + C)*x;

		if (bt1)
			return constants::PI_2 - p;
		if (st1)
			return -constants::PI_2 - p;
		return p;
	}

	real asec(real x)
	{
		return acos(1.0 / x);
	}
	real acsc(real x)
	{
		return asin(1.0 / x);
	}
	real acot(real x)
	{
		return atan(1.0 / x);
	}

	real fast_asin(real x)
	{
		if (std::abs(x) > 1)
			return std::numeric_limits<real>::quiet_NaN();

		if (x == 1)
			return constants::PI_2;

		if (x == -1)
			return -constants::PI_2;
		
		return atan(x / Roots::sqrt(1 - x*x));
	}
}; // namespace InvTrig