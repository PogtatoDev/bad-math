#pragma once
#include "calculus.hpp"
#include "general.hpp"
#include "constants.hpp"

namespace RootFinding
{
	template <typename Func, typename dFunc>
	real manual_newton(Func f, dFunc Df, real guess)
	{
		if (General::abs(Df(guess)) < 0.01)
			guess++;

		real next, old = 0;
		old = guess - f(guess) / Df(guess);
		while (true)
		{
			next = old - f(old) / Df(old);
			if (abs(next - old) < const_limits::LIM_EPS)
				break;

			old = next;
		}

		return next;
	}

	template <typename Func> real auto_newton(Func f, real guess)
	{
		auto Df = [f](real t) { return Calculus::derivative_at(f, t); };
		if (General::abs(Df(guess)) < 0.01)
			guess++;

		real next, old = 0;
		old = guess - f(guess) / Df(guess);
		while (true)
		{
			next = old - f(old) / Df(old);
			if (abs(next - old) < const_limits::LIM_EPS)
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
	real auto_bisection_method(Func f, real eps = 0.01)
	{
		real a = 0;
		real b = 1;
		while (f(a) * f(b) > 0)
		{
			a--;
			b++;
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
}; // namespace RootFinding