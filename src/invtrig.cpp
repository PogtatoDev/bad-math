#include "../include/invtrig.hpp"

#include "../include/constants.hpp"
#include "../include/rootfinding.hpp"
#include "../include/trig.hpp"
#include <limits>


namespace InvTrig
{
	real asin(real x)
	{
		if (General::abs(x) > 1)
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
		return (constants::PI / 2.0) - asin(x);
	}

	real atan(real x)
	{
		if (x > 1)
			return constants::PI / 2 - atan(1.0 / x);
		if (x < -1)
			return -constants::PI / 2 - atan(1.0 / x);

		real term = x;
		real sum = x;
		real x2 = x * x;

		for (int i = 1; i < 50; i++)
		{
			term *= -x2;
			real add = term / (2 * i + 1);
			sum += add;

			if (General::abs(add) < const_limits::LIM_EPS)
				break;
		}

		return sum;
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
}; // namespace InvTrig