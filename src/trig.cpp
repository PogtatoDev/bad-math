#include "../include/trig.hpp"

#include "../include/constants.hpp"
#include "../include/general.hpp"

#include <cmath>

namespace Trig
{
	real alt_sin(real x)
	{
		x = std::fmod(x, constants::TAU);
		x = General::min(x, constants::PI - x);
		x = General::max(x, -constants::PI - x);

		real term = x;
		real approx = x;
		for (int i = 1;; i++)
		{
			term *= -x * x / ((2.0 * i) * (2.0 * i + 1));
			approx += term;

			if (std::abs(term) < const_limits::LIM_EPS)
				break;
		}
		return approx;
	}

	real sin(real x)
	{
		x = std::fmod(x, constants::TAU);
		x = General::min(x, constants::PI - x);
		x = General::max(x, -constants::PI - x);
		x = General::min(x, constants::PI - x);
		real x2 = x * x;
		real approx = x * (0.999998916406210 +
				   x2 * (-0.166657545310621 +
					 x2 * (0.00831484997047385 +
					       x2 * (-0.000185704496035501))));
		return approx;
	}

	real cos(real x)
	{ return sin(constants::PI_2 - x); }

	real alt_cos(real x)
	{ return alt_sin(constants::PI_2 - x); }

	real tan(real x)
	{ return sin(x) / cos(x); }

	real sec(real x)
	{ return 1.0 / cos(x); }
	real csc(real x)
	{ return 1.0 / sin(x); }
	real cot(real x)
	{ return 1.0 / tan(x); }
}; // namespace Trig