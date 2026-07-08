#include "../include/expo.hpp"

#include "../include/constants.hpp"
#include "../include/general.hpp"
#include "../include/lookup/exp_table.hpp"
#include <cmath>
#include <limits>
#include <bit>
#include <cstdint>
namespace Expo
{
	real alt_exp(real x)
	{
		bool st0 = false;
		if (x < -710) return 0;
		if (x > 710) return std::numeric_limits<real>::infinity();
		if (std::isnan(x)) return x;

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

			if (General::abs(term) <
			    const_limits::LIM_EPS * General::abs(sum))
				break;
		}

		if (st0)
			return 1.0 / General::ldexp(sum, k);
		
		return General::ldexp(sum, k);
	}

	// TODO: fix this bullshit
	real exp(real x)
	{
		if (x < -710) return 0;
		if (x > 710) return std::numeric_limits<real>::infinity();
		if (x != x) return x;

		int N = 1;

		if (General::is_int(x) && General::abs(x) < 710) 
		{
			int n = static_cast<int>(x);
			return exp_table[n + 710];
		}

		const real coeff[11] = {
					1.00000000000000,
					0.500000000000000,
					0.166666666666667,
					0.0416666666666667,
					0.00833333333333333,
					0.00138888888888889,
					0.000198412698412698,
					0.0000248015873015873,
					2.75573192239859e-6,
					2.75573192239859e-7,
					2.50521083854417e-8};

		if (x < 0) 
			return 1.0 / exp(-x);

		int n = round(x * constants::INV_LOG2);
		real f = x - n * constants::LOG2;


		real p =
			coeff[0] + f * (
			coeff[1] + f * (
			coeff[2] + f * (
			coeff[3] + f * (
			coeff[4] + f * (
			coeff[5] + f * (
			coeff[6] + f * (
			coeff[7] + f * (
			coeff[8] + f * (
			coeff[9] + f * (
			coeff[10]
			))))))))));


		return General::ldexp(p, n);
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
    {
        return exp(x * constants::LOG10) ;
    }

	real exp2(real x)
	{
		return exp(x * constants::LOG2);
	}
}; // namespace Expo