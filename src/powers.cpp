#include "../include/powers.hpp"

#include "../include/constants.hpp"
#include "../include/expo.hpp"
#include "../include/roots.hpp"
#include "../include/logarithm.hpp"
#include "../include/general.hpp"

namespace Powers
{
    namespace e = Expo;
    namespace l = Logarithm;

	real log_pow(real x, real y)
	{
		if (y == 0)
			return 1;
		if (y < 0)
			return 1.0 / log_pow(x, -y);

		real logx = l::log(x);

		return e::exp(y * logx);
	}

	real rational_pow(real x, int a, int b)
	{
		if (a == 0)
			return 1;
		return Roots::nth_root(General::int_pow(x, a), b);
	}
} // namespace Powers