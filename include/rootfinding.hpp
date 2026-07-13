#pragma once
#include "calculus.hpp"
#include "constants.hpp"
#include "general.hpp"
#include <limits>

namespace RootFinding
{
	template <typename Func, typename dFunc>
	real manual_newton(Func f, dFunc Df, real guess,
			   real eps = const_limits::LIM_EPS, int term_cap = 500)
	{
		if (General::tol(Df(guess)))
			return std::numeric_limits<real>::quiet_NaN();

		real next, old = 0;
		old = guess - f(guess) / Df(guess);
		for (int i = 0; i < term_cap; i++)
		{
			next = old - f(old) / Df(old);
			if (std::abs(next - old) < eps ||
			    std::abs(f(next)) < eps)
				break;

			old = next;
		}

		return next;
	}

	template <typename Func>
	real auto_newton(Func f, real guess, real eps = const_limits::LIM_EPS,
			 int term_cap = 500)
	{
		auto Df = Calculus::derivative(f, eps);
		if (std::abs(Df(guess)) < 0.01)
			guess++;

		real next, old = 0;
		old = guess - f(guess) / Df(guess);
		for (int i = 0; i < term_cap; i++)
		{
			next = old - f(old) / Df(old);
			if (std::abs(next - old) < eps ||
			    std::abs(f(next)) < eps)
				break;
			old = next;
		}

		return next;
	}

	template <typename Func>
	real manual_bisection_method(Func f, real a, real b, real eps = 0.01)
	{
		if (f(a) * f(b) > 0)
			return std::numeric_limits<real>::quiet_NaN();

		real fa = f(a);
		real c = a;
		while ((b - a) >= eps)
		{
			real c = (a + b) * 0.5;
			real fc = f(c);

			if (General::abs(fc) < eps)
				break;

			if (fa * fc < 0)
			{
				b = c;
			}
			else
			{
				a = c;
				fa = fc;
			}
		}

		return c;
	}

	template <typename Func>
	[[deprecated]] real auto_bisection_method(Func f, real eps = const_limits::LIM_EPS)
	{
		real a = -1;
		real b = 1;

		real fa = f(a);
		real fb = f(b);

		while(fa * fb > 0)
		{
			a += a;
			b += b;

			fa = f(a);
			fb = f(b);
		}


		while ((b - a) > eps)
		{
			real c = (a + b) / 2;
			real fc = f(c);

			if (std::abs(fc) < eps)
				return c;

			if (fa * fc < 0)
			{
				b = c;
				fb = fc;
			}
			else
			{
				a = c;
				fa = fc;
			}
		}

		return (a + b) / 2;
	}

	template <typename Func>
	real secant_method(Func f, real x0, real x1, real eps = 0.001,
			   int term_cap = 500)
	{
		for (int i = 0; i < term_cap; i++)
		{
			real f0 = f(x0);
			real f1 = f(x1);
			real x = x1 - ((f1 * (x0 - x1)) / (f0 - f1));

			if (std::abs(x - x1) < eps)
				break;

			x0 = x1;
			x1 = x;
		}

		return x1;
	}
}; // namespace RootFinding