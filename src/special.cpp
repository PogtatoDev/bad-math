#include "../include/special.hpp"

#include "../include/constants.hpp"
#include "../include/calculus.hpp"
#include "../include/expo.hpp"
#include "../include/logarithm.hpp"
#include "../include/powers.hpp"
#include "../include/trig.hpp"
#include "../include/invtrig.hpp"
#include "../include/rootfinding.hpp"
#include "../include/roots.hpp"

namespace Special
{
	namespace e = Expo;
    namespace g = General;
    namespace l = Logarithm;

	real harmonic(real n)
	{
		if (n == 1)
			return 1;
		if (n == 2)
			return 1.5;
		return l::log(n) + constants::GAMMA +
		       1.0 / (2.0 * n) - 1.0 / (12.0 * g::square(n)) +
		       1.0 / (120.0 * g::square(g::square(n)));
	}

	namespace DirichletSeries
	{
		real int_zeta(int s)
		{
			if (s == 2)
				return g::square(constants::PI) / 6.0;
			if (s == 3)
				return constants::ZETA3;
			if (s == 4)
				return g::square(g::square(constants::PI)) /
				       90.0;

			if (s < 1)
				return std::numeric_limits<real>::quiet_NaN();

			auto f = [s](real t)
			{ return 1.0 / General::int_pow(t, s); };

			return Calculus::infinite_sum(f, 1);
		}

		real int_eta(int s, int acc = 1000)
		{
			if (s == 1)
				return constants::LOG2;

			real approx = 0;
			real term = 0;
			auto f = [s](real t)
			{ return 1.0 / General::int_pow(t, s); };

			return Calculus::infinite_sum(f, 1, true);
		}

		real real_zeta(real s)
		{
			if (s == 2)
				return g::square(constants::PI) / 6.0;
			if (s == 3)
				return constants::ZETA3;
			if (s == 4)
				return g::square(g::square(constants::PI)) /
				       90.0;

			if (s < 1)
				return std::numeric_limits<real>::quiet_NaN();

			auto f = [s](real t)
			{ return 1.0 / Powers::log_pow(t, s); };

			return Calculus::infinite_sum(f, 1, false);
		}

		real real_eta(int s, int acc = 1000)
		{
			if (s == 1)
				return constants::LOG2;

			real approx = 0;
			real term = 0;
			auto f = [s](real t)
			{ return 1.0 / General::int_pow(t, s); };

			return Calculus::infinite_sum(f, 1, true);
		}
	}; // namespace DirichletSeries

	real log_gamma(real x)
	{
		int N = 10;

		if (x == 1)
			return 0;
		if (x == 0.5)
			return 0.5 * constants::LOGPI;
		if (x == 2)
			return 0;
		if (x > 0)
		{
			if (General::is_int(x) && x < 20)
			{
				int n = static_cast<int>(std::round(x));
				
				return l::log(General::factorial(n-1));
			}

			real c = 0.5 * (constants::LOG2 + constants::LOGPI);
			real sum = 0;
			for (int k = 1; k <= N - 1; k++)
			{
				sum += constants::BERNOULLI[2 * k] /
				       (2 * k * (2 * k - 1)) * 1.0 /
				       General::int_pow(x, 2 * k - 1);
			}

			return (x - 0.5) * l::log(x) - x + c + sum;
		}

		else
		{
			if (General::is_int(x))
				return std::numeric_limits<real>::quiet_NaN();

			return constants::LOGPI -
			       l::log(Trig::sin(constants::PI * x)) -
			       log_gamma(1 - x);
		}
	}

	real gamma(real s)
	{
		return e::exp(log_gamma(s));
	}

	real beta(real x, real y)
	{
		return (gamma(x) * gamma(y)) / gamma(x + y);
	}

	real lamb_w(real x)
	{
		namespace e = Expo;

		auto f = [x](real t) { return t * e::exp(t) - x; };
		auto Df = [](real t) { return e::exp(t) * (t + 1); };
		real guess = 0;

		if (x < constants::E)
			guess = x;
		else
		{
			real l = l::log(x);
			guess = l - l::log(l);
		}

		return RootFinding::manual_newton(f, Df, guess);
	}

	real atan2(real y, real x)
	{
		namespace i = InvTrig;
		real P = constants::PI;
		if (x > 0)
			return i::atan(y / x);
		if (x < 0 && y >= 0)
			return i::atan(y / x) + P;
		if (x < 0 && y < 0)
			return i::atan(y / x) - P;
		if (x == 0 && y > 0)
			return P / 2;
		if (x == 0 && y < 0)
			return -P / 2;

		return 0.0;
	}

	real nCr(real n, real r)
	{
		if (r < 0 || r > n)
			return 0;

		if (r > n - r)
			r = n - r;

		real result = 1;

		for (int i = 1; i <= r; i++)
		{
			result *= (n - r + i);
			result /= i;
		}

		return result;
	}

	real smax(real x, real y, real bias)
	{
		return (x + y + Roots::sqrt(General::square(x-y) + bias)) / 2.0;
	}


	real smin(real x, real y, real bias)
	{
		return (x + y - Roots::sqrt(General::square(x-y) + bias)) / 2.0;
	}
}; // namespace Special