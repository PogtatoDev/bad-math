#include "../include/full_lib.hpp"
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
benchmark bench(Func1 func1, Func2 func2, float start, float end, float increment)
{
    real sink = 0;
    Timer t;

    for (float i = start; i < end; i += increment)
    {
        sink += General::abs(func1(i) - func2(i));
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

template <typename Func1, typename Func2> void test(Func1 f1, Func2 f2)
{
    benchmark tests = bench(f1, f2, -10000000, 10000000, 1);

    std::cout
    << "full time taken:     " << tests.full_time  << std::endl
    << "full error:          " << tests.sink       << std::endl
    << "func 1 time taken:   " << tests.func1_time << std::endl
    << "func 2 time taken:   " << tests.func2_time << std::endl
    << "func 1 sink:         " << tests.func1_sink << std::endl
    << "func 2 sink:         " << tests.func2_sink << std::endl;
}

void test_quadratic()
{
    Timer t;
    Quadratic quad1(5, 4, 2);
    Quadratic quad2(0.4, 9, -10);

    std::cout
    << "quadratic #1 info:"                                                              << std::endl 
    << "    " << quad1.display()                                                         << std::endl
    << "    first solution:   "     << quad1.solutions[0]                                << std::endl 
    << "    second solution:  "     << quad1.solutions[1]                                << std::endl << std::endl
    << "    vertex x:         "     << quad1.vertex().x                                  << std::endl
    << "    vertex y:         "     << quad1.vertex().y                                  << std::endl << std::endl
    << "    y-intercept:      "     << quad1.y_intercept()                               << std::endl << std::endl << std::endl
    << "quadratic #2 info:"                                                              << std::endl 
    << "    " << quad2.display()                                                         << std::endl
    << "    first solution:   "     << quad2.solutions[0]                                << std::endl 
    << "    second solution:  "     << quad2.solutions[1]                                << std::endl << std::endl
    << "    vertex x:         "     << quad2.vertex().x                                  << std::endl
    << "    vertex y:         "     << quad2.vertex().y                                  << std::endl << std::endl
    << "    y-intercept:      "     << quad2.y_intercept()                               << std::endl << std::endl << std::endl
    << "program executed in " << t.elapsed() << "s"                                      << std::endl;
}

int main()
{
    test_quadratic();
    return 0;
}