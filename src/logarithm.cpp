#include "../include/logarithm.hpp"

#include "../include/rootfinding.hpp"
#include "../include/constants.hpp"
#include "../include/expo.hpp"
#include "../include/lookup/log_table.hpp"
#include <limits>


namespace Logarithm
{
	real halley_log(real x, real eps)
	{
		if (x < 0)
			return std::numeric_limits<real>::quiet_NaN();
		if (General::tol(x))
			return -std::numeric_limits<real>::infinity();

		if (General::is_int(x) && x < 511)
		{
			int n = static_cast<int>(x);
			return log_table[n];
		}
			
		int k;
		real m = frexp(x, &k);

		real y = m - 1;
		for (int i = 0; i < 4; i++)
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

	real log(real x)
	{
		int st1 = 1;
		if (x < 0)
			return std::numeric_limits<real>::quiet_NaN();

		if (x < 1)
		{
			x = 1.0 / x;
			st1 = -1;
		}
		if (General::tol(x))
			return -std::numeric_limits<real>::infinity();

		if (General::is_int(x) && x < 1024)
		{
			int n = round(x);
			return st1 * log_table[n];
		}
			
		int k;
		real m = frexp(x, &k);
		real constants[11] = {
			0.1,
			1.1111111111111111,
			5.625,
			17.142857142857142,
			35,
			50.4,
			52.5,
			40,
			22.5,
			10,
			2.9289682539682538
		};

		real p = -(m*(m*(m*(m*(m*(m*(m*(m*(m*(m * constants[0] - constants[1]) + constants[2]) - constants[3]) + constants[4]) - constants[5]) + constants[6]) - constants[7]) + constants[8]) - constants[9]) + constants[10]);
		return st1 * (p + k * constants::LOG2);
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
		if (General::tol(x))
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