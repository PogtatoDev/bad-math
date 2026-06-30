#include "../include/logarithm.hpp"

#include "../include/rootfinding.hpp"
#include "../include/constants.hpp"
#include "../include/expo.hpp"
#include "../include/lookup/log_table.hpp"


namespace Logarithm
{
	real log(real x, real eps)
	{
		if (x < 0)
			return std::numeric_limits<real>::quiet_NaN();
		if (General::is_int(x) && x < 511)
		{
			int n = static_cast<int>(x);
			return log_table[n];
		}
			
		int k;
		real m = frexp(x, &k);

		real y = m - 1;
		for (int i = 0; i < 8; i++)
		{
			real exp_y = Expo::exp(y);
			real r = m / exp_y;

			real delta = 2 * (r - 1) / (r + 1);

			y += delta;

			if (std::abs(delta) < eps)
				break;
		}

		return y + k * constants::LOG2;
	}

	real alt_log(real x)
	{
		if (x < 0)
			return std::numeric_limits<real>::quiet_NaN();

		if (General::is_int(x) && x < 511)
		{
			int n = static_cast<int>(x);
			return log_table[n];
		}
		int k;
		real m = frexp(x, &k);

		real y = m - 1;
		for (int i = 0; i < 8; i++)
		{
			real exp_y = Expo::alt_exp(y);
			real r = m / exp_y;

			real delta = 2 * (r - 1) / (r + 1);

			y += delta;

			if (std::abs(delta) < const_limits::LIM_EPS)
				break;
		}

		return y + k * constants::LOG2;
	}

	real bisection_log(real x, real bisection_acc = 0.01)
	{
		if (x < 0)
			return std::numeric_limits<real>::quiet_NaN();
		auto f = [x](real t) { return Expo::exp(t) - x; };

		return RootFinding::auto_bisection_method(f, bisection_acc);
	}

	real newton_log(real x)
	{
		if (x < 0)
			return std::numeric_limits<real>::quiet_NaN();
		if (x == 0)
			return -std::numeric_limits<real>::infinity();

		auto f = [x](real t) { return Expo::exp(t) - x; };
		auto Df = [](real t) { return Expo::exp(t); };

		int guess = General::log2_int(std::round(x));

		return RootFinding::manual_newton(f, Df, guess);
	}

	real log_base(real x, real base)
	{
		return Logarithm::log(x) / log(base);
	}
	real log10(real x)
	{
		return log(x) / constants::LOG10;
	}
}; // namespace Logarithm