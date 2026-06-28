#pragma once

#include "constants.hpp"

namespace Special
{
    real harmonic(real n);
	namespace DirichletSeries
	{
		real int_zeta(int s);
		real int_eta(int s);
		real real_zeta(real s);
		real real_eta(real s);
	}; // namespace DirichletSeries
	real log_gamma(real x);
	real gamma(real s);
	real beta(real x, real y);
	real lamb_w(real x);
	real atan2(real y, real x);
	real nCr(real n, real r);
	real smax(real x, real y, real bias);
	real smin(real x, real y, real bias);
}; // namespace Special