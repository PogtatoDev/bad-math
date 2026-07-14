#include "../include/expo.hpp"

#include "../include/constants.hpp"
#include "../include/general.hpp"
#include "../include/lookup/exp_table.hpp"
#include <bit>
#include <cmath>
#include <cstdint>
#include <limits>

namespace Expo
{
	real alt_exp(real x)
	{
		bool st0 = false;
		if (x < -710)
			return 0;
		if (x > 710)
			return std::numeric_limits<real>::infinity();
		if (std::isnan(x))
			return x;

		if (General::is_int(x) && x < 1420)
		{
			int n = static_cast<int>(x);
			return exp_table[n + 710];
		}

		if (x < 0)
			st0 = true;

		int k = std::floor(x / constants::LOG2);
		real r = x - (k * constants::LOG2);
		real term = 1;
		real sum = 1;

		for (int i = 1;; i++)
		{
			term *= r / i;
			sum += term;

			if (std::abs(term) <
			    const_limits::LIM_EPS * std::abs(sum))
				break;
		}

		return st0 ? 1.0 / General::ldexp(sum, k)
			   : General::ldexp(sum, k);
	}

	real exp(real x)
	{
		if (x < -710)
			return 0;
		if (x > 710)
			return std::numeric_limits<real>::infinity();
		if (std::isnan(x))
			return x;

		if (General::is_int(x) && std::abs(x) < 710)
		{
			int n = static_cast<int>(x);
			return exp_table[n + 710];
		}

		if (x < 0)
			return 1.0 / exp(-x);

		int k = std::round(x * constants::INV_LOG2);
		real r = x - k * constants::LOG2;

		real p =
		    r * (r * (r * (r * (r * (r * (r * (2.50726499359848e-5 * r +
						       0.00020097762801442) +
						  0.00138880322459888) +
					     0.00833259882407862) +
					0.0416666766759372) +
				   0.166666737586158) +
			      0.499999999636699) +
			 0.999999998355752) +
		    1.00000000000182;

		return General::ldexp(p, k);
	}

	real fast_exp(real x)
	{
		if (General::is_int(x) && x < 1420)
		{
			int n = static_cast<int>(x);
			return exp_table[710 + n];
		}

		constexpr double a = (1LL << 52) / 0.6931471805599453;
		constexpr double b = (1LL << 52) * (1023 - 0.04367744890362246);
		x = a * x + b;

		return std::bit_cast<double>(static_cast<uint64_t>(x));
	}

	real exp10(real x)
	{ return exp(x * constants::LOG10); }

	real exp2(real x)
	{ return exp(x * constants::LOG2); }
}; // namespace Expo