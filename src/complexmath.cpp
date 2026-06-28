#include "../include/complexmath.hpp"

#include "../include/constants.hpp"
#include "../include/expo.hpp"
#include "../include/special.hpp"
#include "../include/trig.hpp"
#include "../include/logarithm.hpp"
#include "../include/general.hpp"
#include "../include/roots.hpp"
#include <limits>

namespace ComplexMath
{
	namespace e = Expo;
	namespace l = Logarithm;
    namespace g = General;

	real arg(cmplx z)
	{
		return Special::atan2(z.imag(), z.real());
	}
	cmplx complex_exp(cmplx z)
	{
		real a = z.real(), b = z.imag();
		if (b == 0)
			return e::exp(a);
		real exp_a = e::exp(a);
		real sin_b = Trig::sin(b), cos_b = Trig::cos(b);

		return cmplx(exp_a * cos_b, exp_a * sin_b);
	}

	cmplx complex_log(cmplx z)
	{
		return cmplx(l::log(std::abs(z)), arg(z));
	}

	cmplx complex_sqrt(real x)
	{
		cmplx result = 1;
		if (x < 0)
			result *= cmplx(0, Roots::sqrt(-x));
		else
			result *= Roots::sqrt(x);

		return result;
	}

	std::vector<cmplx> solve_quadratic(real a, real b, real c)
	{
		if (a == 0)
			return {cmplx(std::numeric_limits<real>::quiet_NaN(), 0)};
		real discriminant = g::square(b) - 4 * a * c;
		std::vector<cmplx> roots = {
		    (-cmplx(b, 0.0L) + complex_sqrt(discriminant)) /
			cmplx((2.0 * a), 0.0L),
		    (-cmplx(b, 0.0L) - complex_sqrt(discriminant)) /
			cmplx((2.0 * a), 0.0L)};
		return roots;
	}

	cmplx complex_square(cmplx z)
	{
		real a = z.real(), b = z.imag();
		return cmplx(g::square(a) - g::square(b), 2 * a * b);
	}

	cmplx complex_sin(cmplx z)
	{
		cmplx a = complex_exp(constants::i * z);
		cmplx b = 1.0 / a;

		return (a - b) / cmplx(0.0, 2);
	}

	cmplx complex_cos(cmplx z)
	{
		cmplx a = complex_exp(constants::i * z);
		cmplx b = 1.0 / a;

		return (a + b) / 2.0;
	}

	cmplx complex_tan(cmplx z)
	{
		return complex_sin(z) / complex_cos(z);
	}
	cmplx complex_pow(cmplx z, cmplx w)
	{
		cmplx logz = complex_log(z);

		return complex_exp(w * logz);
	}

	cmplx complex_log_gamma(cmplx z)
	{
		if (z.imag() == 0)
			return Special::log_gamma(z.real());

		if (z.real() > 1)
		{
			real c = 0.5 * (constants::LOG2 + constants::LOGPI);
			return (z - 0.5) * complex_log(z) - z + c +
			       1.0 / (12.0 * z);
		}

		else
		{
			if (g::is_int(z.real()))
				return std::numeric_limits<real>::quiet_NaN();

			return cmplx(constants::LOGPI, 0) -
			       complex_log(
				   complex_sin(cmplx(constants::PI, 0) * z)) +
			       complex_log_gamma(cmplx(1, 0) - z);
		}
	}

	cmplx complex_gamma(cmplx z)
	{
		return complex_exp(complex_log_gamma(z));
	}

	cmplx eta(cmplx s)
	{
		auto custom_pow = [](real t, cmplx s)
		{
			real logt = l::log(t);

			return complex_exp(s * logt);
		};

		cmplx sum(0, 0);

		for (int i = 0; i < 30; i++)
		{
			cmplx inner(0, 0);

			for (int j = 0; j <= i; j++)
			{
				real sign = (j & 1) ? -1.0 : 1.0;

				inner += sign * Special::nCr(i, j) *
					 custom_pow(j + 1, -s);
			}

			sum += inner / cmplx(g::exp2(i + 1), 0);
		}

		return sum;
	}
}; // namespace ComplexMath