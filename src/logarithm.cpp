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
		if (std::abs(x) < const_limits::LIM_EPS)
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
		bool st1 = x < 1;
		if (x < 0)
			return std::numeric_limits<real>::quiet_NaN();

		if (std::abs(x) < const_limits::LIM_EPS)
			return -std::numeric_limits<real>::infinity();

		x = st1 ? 1.0/x : x;

		if (General::is_int(x) && x < 1024)
		{
			int n = round(x);
			return st1 ? -log_table[n] : log_table[n];
		}

		
		int k;
		real m = General::frexp(x, k);

		if (m < constants::SQRT2_2)
		{
			m *= 2;
			k -= 1;
		}

		real p = m*(m*(m*(m*(m*(m*(m*(0.911814655241915 - 0.0942006339486538*m) - 3.91823414464795) + 9.83610862396699) - 15.9761942733761) + 17.6034271483863) - 13.5511837975087) + 7.89662754645609) - 2.70816511790814;
		return st1 ? -(p + k * constants::LOG2) : (p + k * constants::LOG2);
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

		real y = k*constants::LOG2;
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

	real newton_log(real x)
	{
		if (x < 0)
			return std::numeric_limits<real>::quiet_NaN();
		if (std::abs(x) < const_limits::LIM_EPS)
			return -std::numeric_limits<real>::infinity();

		auto f = [x](real t) { return Expo::exp(t) - x; };
		auto Df = [](real t) { return Expo::exp(t); };
		int k;
		General::frexp(x, k);
		int guess = k*constants::LOG2;

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