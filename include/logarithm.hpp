#pragma once

#include "constants.hpp"

namespace Logarithm
{
    real log(real x);
    real alt_log(real x);
    real halley_log(real x, real eps = const_limits::LIM_EPS);
    real bisection_log(real x);
    real newton_log(real x);
    real log_base(real x);
    real log10(real x);
}