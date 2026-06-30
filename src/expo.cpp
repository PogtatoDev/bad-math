#include "../include/expo.hpp"

#include "../include/constants.hpp"
#include "../include/general.hpp"
#include "../include/lookup/exp_table.hpp"
#include <cmath>
#include <limits>

namespace Expo
{
	real alt_exp(real x)
	{
		if (x < -710) return 0;
		if (x > 710) return std::numeric_limits<real>::infinity();
		if (x != x) return x;

		if (General::is_int(x)) 
		{
			int n = static_cast<int>(x);
			return exp_table[n + 710];
		}


		if (x < 0)
			return 1.0L / exp(-x);

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

		return sum * General::exp2(k);
	}

	// TOOO: fix this bullshit
	real exp(real x)
	{
		if (x < -710) return 0;
		if (x > 710) return std::numeric_limits<real>::infinity();
		if (x != x) return x;

		if (General::is_int(x)) 
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
					2.50521083854417e-8,};

		if (x < 0) 
			return 1.0 / exp(-x);

		int n = trunc(x * constants::INV_LOG2);
		real f = x - n * constants::LOG2;

		real p = 1.0 + f * (
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
        )))))))))));

		return General::exp2(n) * p;
	}

    real exp10(real x)
    {
        return exp(x * constants::LOG10) ;
    }

	real exp2(real x)
	{
		return exp(x * constants::LOG2);
	}

	real fast_exp(real x)
	{
		real c[4] = {0.28033708,0.425302,1.01273643,1.00020947};

	}
}; // namespace Expo