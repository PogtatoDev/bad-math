#include "../include/hyptrig.hpp"

#include "../include/expo.hpp"
#include "../include/constants.hpp"

namespace HypTrig
{
	namespace e = Expo;

	real sinh(real x)
	{	
		real expx = e::exp(x);
		return (expx - 1.0 / expx) / 2.0;
	}

	real cosh(real x)
	{
		real expx = e::exp(x);
		return (e::exp(x) + 1.0 / expx) / 2.0;
	}

	real tanh(real x)
	{
		return sinh(x) / cosh(x);
	}
	real sech(real x)
	{
		return 1.0 / cosh(x);
	}
	real csch(real x)
	{
		return 1.0 / sinh(x);
	}
	real coth(real x)
	{
		return 1.0 / tanh(x);
	}
}; // namespace HypTrig