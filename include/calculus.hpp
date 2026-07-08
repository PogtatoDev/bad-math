#pragma once

#include "constants.hpp"
#include "general.hpp"
#include <functional>

namespace Calculus
{
	template <typename Func> real left_limit(Func f, real x, real eps)
	{
		return f(x - eps);
	}
	template <typename Func> real right_limit(Func f, real x, real eps)
	{
		return f(x + eps);
	}

	template <typename Func> real sum(Func f, real start, real end, bool alternating = false)
	{
		if (alternating)
		{
			real sum = 0;
			real sign = 1;
			for (int k = start; k <= end; k++)
			{
				sum += f(k) * sign;
				sign *= -1;
			}

			return sum;
		}
		real sum = 0;
		for (int k = start; k <= end; k++)
		{
			sum += f(k);
		}

		return sum;
	}

	template <typename Func>
	real infinite_sum(Func f, real start, bool alternating = false)
	{
		if (alternating)
		{
			real sum = 0;
			real term = 0;
			real sign = 1;
			for (int k = start;; k++)
			{
				term = f(k);
				sum += term * sign;

				sign *= -1;

				if (General::abs(term) < const_limits::LIM_EPS)
					break;

			}

			return sum;
		}

		real sum = 0;
		real term = 0;
		for (int k = start;; k++)
		{
			term = f(k);
			sum += term;
			if (General::abs(term) < const_limits::LIM_EPS)
				break;
		}

		return sum;
	}

	template <typename Func>
	real rect_riemann_sum(Func f, real start, real end, int n)
	{
		const real dx = (end - start) / n;
		real approx = 0;
		for (int i = 0; i < n; i++)
		{
			const real x = start + (i + 0.5) * dx;
			approx += f(x) * dx;
		}

		return approx;
	}

	template <typename Func>
	real simpson_integral(Func f, real start, real end, int n)
	{
		if (start == end)
			return 0.0;
		if (start > end)
			return -simpson_integral(f, end, start);
		if (n % 2 != 0)
			n += 1;
		real h = (end - start) / n;
		real approx = f(start) + f(end);

		for (int i = 1; i < n; i++)
		{
			real x = start + i * h;
			if (i % 2 == 0)
				approx += 2.0 * f(x);
			else
				approx += 4.0 * f(x);
		}

		return approx * h / 3.0;
	}

	template <typename Func> auto derivative(Func f, real eps = 0.000001)
	{
		auto Df = [f, eps](real x)
	    { return (f(x + eps) - f(x - eps)) / (2 * eps); };

		return Df;
	}

	template <typename Func> real derivative_at(Func f, real x, real eps = 0.000001)
	{
		const real h = const_limits::LIM_EPS;
		return (f(x + h) - f(x - h)) / (2 * h);
	}

	template <typename Func> real average(Func f, real start, real end)
	{
		return simpson_integral(f, start, end) / (end - start);
	}

	template <typename Func> auto taylor_polynomial(Func f, int degree)
	{
		auto taylor_f = []( real t ) 
		{ return t + 1; };

		return f;
	}
};