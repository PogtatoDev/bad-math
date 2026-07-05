#pragma once

template<typename T>
struct Vector3
{
    T x, y, z;
    Vector3(T ix, T iy, T iz)
    {
        x = ix;
        y = iy;
        z = iz;
    }
};