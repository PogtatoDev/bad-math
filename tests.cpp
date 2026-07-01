#include "include/constants.hpp"
#include "include/general.hpp"
#include "include/logarithm.hpp"
#include "include/powers.hpp"
#include "include/roots.hpp"
#include "include/special.hpp"
#include "include/trig.hpp"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>

struct benchmark
{
    real full_time;
    real sink;
    real func1_time;
    real func2_time;
    real func1_sink;
    real func2_sink;
};

class Timer
{
      private:
	using clock = std::chrono::steady_clock;
	using second = std::chrono::duration<double, std::ratio<1>>;

	std::chrono::time_point<clock> m_beg{clock::now()};

      public:
	void reset() { m_beg = clock::now(); }

	double elapsed() const
	{
		return std::chrono::duration_cast<second>(clock::now() - m_beg)
		    .count();
	}
};

template <typename Func1, typename Func2> 
benchmark bench(Func1 func1, Func2 func2, float start, float end, float increment, bool random)
{
    real sink = 0;
    Timer t;
    if (random)
    {
        for (float i = start; i < end; i += increment)
        {
            real r = rand();
            sink += General::abs(func1(r) - func2(r));
        }
    }
    else 
    {
        for (float i = start; i < end; i += increment)
        {
            sink += General::abs(func1(i) - func2(i));
        }
    }

    benchmark temp;
    temp.sink = sink;
    temp.full_time = t.elapsed();
    t.reset();
    sink = 0;
    for (float i = start; i < end; i += increment)
    {
        sink += func1(i);
    }
    
    temp.func1_sink = sink;
    temp.func1_time = t.elapsed();

    t.reset();
    sink = 0;
    for (float i = start; i < end; i += increment)
    {
        sink += func2(i);
    }

    temp.func2_sink = sink;
    temp.func2_time = t.elapsed();

    return temp;
}

int main()
{
    auto f1 = [](real t) { return std::pow(t, 1/8); };
    auto f2 = [](real t) { return Powers::rational_pow(t, 1, 8); };
    benchmark tests = bench(f1, f2, 1, 1000, 0.1, false);

    std::cout << "full time taken:     " << tests.full_time  << std::endl;
    std::cout << "full error:          " << tests.sink       << std::endl;
    std::cout << "func 1 time taken:   " << tests.func1_time << std::endl;
    std::cout << "func 2 time taken:   " << tests.func2_time << std::endl;
    std::cout << "func 1 sink:         " << tests.func1_sink << std::endl;
    std::cout << "func 2 sink:         " << tests.func2_sink << std::endl;
}