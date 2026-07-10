#include "../include/invhyptrig.hpp"

#include "../include/constants.hpp"
#include "../include/general.hpp"
#include "../include/logarithm.hpp"
#include "../include/roots.hpp"

namespace InvHypTrig
{
	real asinh(real x)
	{
		return Logarithm::log(x + Roots::sqrt(x * x + 1));
	}
	real acosh(real x)
	{
		return Logarithm::log(x + Roots::sqrt(x * x - 1));
	}

	real atanh(real x)
	{
		if (std::abs(x) >= 1)
			return std::numeric_limits<real>::quiet_NaN();
		const real t = (1 + x) / (1 - x);
		return 0.5 * Logarithm::log(t);
	}

	real asech(real x)
	{
		return acosh(1.0 / x);
	}
	real acsch(real x)
	{
		return asinh(1.0 / x);
	}

	real acoth(real x)
	{
		if (std::abs(x) <= 1)
			return std::numeric_limits<real>::quiet_NaN();
		const real t = (x + 1) / (x - 1);
		return 0.5 * Logarithm::log(t);
	}
}; // namespace InvHypTrig