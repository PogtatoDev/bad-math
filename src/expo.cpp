#include "../include/expo.hpp"

#include "../include/constants.hpp"
#include "../include/general.hpp"
#include <cmath>

namespace Expo
{
	real alt_exp(real x)
	{
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

	real exp(real x)
	{
		const real *FACT = constants::FACTORIAL;

		if (x < 0)
			return 1.0 / alt_exp(-x);

		int n = std::floor(x / constants::LOG2);
		real f = x - n * constants::LOG2;

		real p =
		    1 +
		    (f *
		    (1.0 +
		    f * (0.5 +
			f * (1.666666666667 +
			f * (0.041666666667 +
		    f * (0.008333333333 +
		    f * (0.001388888889 +
	        f * (1.984127e-4 +
			f * (2.480159e-5 +
			f * (2.755732e-6 +
			f * (2.755732e-7 +
			f * (2.505211e-8))))))))))));

		return General::exp2(n) * p;
	}

    real exp10(real x)
    {
        return exp(x * constants::LOG10) ;
    }
}; // namespace Expo