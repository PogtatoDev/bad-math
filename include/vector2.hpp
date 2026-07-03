#pragma once
#include "constants.hpp"

template<typename T>
struct Vector2
{
    T x, y;
    Vector2(T ix, T iy)
    {
        x = ix;
        y = iy;
    }
    
};