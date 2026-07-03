#pragma once
#include <complex>

using real = double;
using cmplx = std::complex<real>;

namespace constants
{
	constexpr long double PI = 3.141592653589793238462643383L;
	constexpr long double TAU = 2 * PI;
	constexpr long double PI_2 = 3.141592653589793238462643383L / 2.0;
	constexpr long double PI3_2 = 3 * 3.141592653589793238462643383L / 2.0;
	constexpr long double PI_4 = PI_2 / 2.0;
	constexpr long double PI_SQ = 9.869604401089358618834490999L;
	constexpr long double PI4 = 2 * TAU;

	constexpr long double E = 2.718281828459045235360287471L;
	constexpr long double GAMMA = 0.577215664901532860606512090L;
	constexpr long double OMEGA = 0.567143290409783872999968662L;
	constexpr long double ZETA3 = 1.202056903159594285399738161L;
	constexpr long double GOLDEN = 1.618033988749894848204586834L;
	constexpr long double LOG2 = 0.693147180559945309417232121L;
	constexpr long double LOG10 = 2.302585092994045684017991454L;
	constexpr long double SQRT2 = 1.414213562373095048801688724L;
	constexpr long double LOGPI =  1.144729885849400174143427351L;
	constexpr long double INV_LOG2 = 1.442695040888963407359924681L;
	constexpr int DEF_TAYLOR_ACC = 30;
	constexpr int DEF_NEWTON_ACC = 100;
	constexpr cmplx i = cmplx(0.0, 1.0);

	constexpr real BERNOULLI[] = {1,
				      0.5,
				      1.0 / 6.0,
				      0,
				      -1.0 / 30.0,
				      0,
				      1.0 / 42.0,
				      0,
				      -1.0 / 30.0,
				      0,
				      5.0 / 66.0,
				      0,
				      -691.0 / 2730.0,
				      0,
				      7.0 / 6.0,
				      0,
				      -3617.0 / 510.0,
				      0,
				      43867.0 / 798.0,
				      0,
				      -174611.0 / 330.0};

	constexpr real FACTORIAL[] = {1,
				      1,
				      2,
				      6,
				      24,
				      120,
				      720,
				      5040,
				      40320,
				      362880,
				      3628800,
				      39916800,
				      479001600,
				      6227020800,
				      87178291200,
				      1307674368000,
				      20922789888000,
				      355687428096000,
				      6402373705728000,
				      121645100408832000,
				      2432902008176640000};
} // namespace constants

namespace const_limits
{
	constexpr int LIM_INF = 1e7;
	constexpr real LIM_EPS = 1e-11;
} // namespace const_limits