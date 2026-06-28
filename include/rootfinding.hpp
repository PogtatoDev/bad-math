#pragma once
#include "calculus.hpp"
#include "general.hpp"
#include "constants.hpp"
#include <limits>

namespace RootFinding
{
	template <typename Func, typename dFunc>
	real manual_newton(Func f, dFunc Df, real guess, real eps = 0.001, int term_cap = 500)
	{
		if (General::abs(Df(guess)) < 0.01)
			guess++;

		real next, old = 0;
		old = guess - f(guess) / Df(guess);
		for (int i = 0; i < term_cap; i++)
		{
			next = old - f(old) / Df(old);
			if (General::abs(next - old) < eps || General::abs(f(next)) < eps)
				break;

			old = next;
		}

		return next;
	}

	template <typename Func> real auto_newton(Func f, real guess, real eps = 0.001, int term_cap = 500)
	{
		auto Df = [f](real t) { return Calculus::derivative_at(f, t); };
		if (General::abs(Df(guess)) < 0.01)
			guess++;

		real next, old = 0;
		old = guess - f(guess) / Df(guess);
		for (int i = 0; i < term_cap; i++)
		{
			next = old - f(old) / Df(old);
			if (General::abs(next - old) < eps || General::abs(f(next)) < eps)
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

		real c = a;

		while ((b - a) >= eps)
		{
			c = (a + b) / 2.0;
			if (f(c) < eps)
				break;
			if (f(c) * f(a) < 0)
				b = c;
			else
				a = c;
		}

		return c;
	}

	template <typename Func>
	real auto_bisection_method(Func f, real eps = 0.01)
	{
		real a = 1;
		real b = -1;
		int i = 1;
		while (f(a) * f(b) > 0)
		{
			a *= 2;
			b *= 2;
			i++;

			if (i > 10000)
				return std::numeric_limits<real>::quiet_NaN();
		}
		real c = a;

		while ((b - a) >= eps)
		{
			c = (a + b) / 2.0;
			if (f(c) == 0.0)
				break;
			if (f(c) * f(a) < 0)
				b = c;
			else
				a = c;
		}

		return c;
	}

	template <typename Func>
	real secant_method(Func f, real x0, real x1, real eps = 0.001, int term_cap = 500)
	{
		for (int i = 0; i < term_cap; i++)
		{
			real f0 = f(x0);
			real f1 = f(x1);
			real x = x1 - ((f1*(x0-x1))/(f0 - f1));

			if (General::abs(x-x1) < eps)
				break;

			x0 = x1;
        	x1 = x;
		}

		return x1;
	}
}; // namespace RootFinding