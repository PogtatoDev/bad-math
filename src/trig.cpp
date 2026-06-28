#include "../include/trig.hpp"

#include "../include/constants.hpp"
#include "../include/general.hpp"


namespace Trig
{
	real sin(real x)
	{
		x = std::fmod(x, 2 * constants::PI);
		real term = x;
		real approx = x;
		for (int i = 1;; i++)
		{
			term *= -x * x / ((2.0 * i) * (2.0 * i + 1));
			approx += term;

			if (General::abs(term) < const_limits::LIM_EPS)
				break;
		}
		return approx;
	}

	real cos(real x)
	{
		return sin(constants::PI / 2 - x);
	}
	real tan(real x)
	{
		return sin(x) / cos(x);
	}

	real sec(real x)
	{
		return 1.0 / cos(x);
	}
	real csc(real x)
	{
		return 1.0 / sin(x);
	}
	real cot(real x)
	{
		return 1.0 / tan(x);
	}
}; // namespace Trig