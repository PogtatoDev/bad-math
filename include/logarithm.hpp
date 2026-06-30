#pragma once

#include "constants.hpp"

namespace Logarithm
{
    real log(real x, real eps = 0.001);
    real alt_log(real x);
    real bisection_log(real x);
    real newton_log(real x);
    real log_base(real x);
    real log10(real x);
}