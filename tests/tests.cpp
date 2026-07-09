#include "../include/full_lib.hpp"
#include "../include/linear.hpp"
#include "../include/logarithm.hpp"
#include <chrono>
#include <cmath>
#include <complex>
#include <iostream>
#include <ostream>

class Benchmark
{
      public:
	real full_time;
	real sink;
	real func1_time;
	real func2_time;
	real func1_sink;
	real func2_sink;
	real ehhhror;
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
Benchmark bench(Func1 func1, Func2 func2, real start, real end,
		real increment)
{
	real sink = 0;
	Timer t;

	for (real i = start; i < end; i += increment)
	{
		sink += General::abs(func1(i) - func2(i));
	}

	Benchmark temp;
	temp.sink = sink;
	temp.full_time = t.elapsed();
	sink = 0;
	for (real i = start; i < end; i += increment)
	{

		sink += General::abs(func1(i) - func2(i)) / func1(i);

	}
	temp.ehhhror = sink;
	t.reset();
	sink = 0;
	for (real i = start; i < end; i += increment)
	{
		sink += func1(i);
	}

	temp.func1_sink = sink;
	temp.func1_time = t.elapsed();

	t.reset();
	sink = 0;
	for (real i = start; i < end; i += increment)
	{
		sink += func2(i);
	}

	temp.func2_sink = sink;
	temp.func2_time = t.elapsed();

	return temp;
}

template <typename Func1, typename Func2>
void test(Func1 f1, std::string name1, Func2 f2, std::string name2)
{
	const real start = 2;
	const real end = 1e7;
	const real increment = 1;
	Benchmark tests = bench(f1, f2, start, end, increment);

	std::cout << "test results for " << name1 << " (func1) vs " << name2 << " (func2) from " << start << " to " << end
		  << " with increment " << increment << std::endl
		  << "	full time taken:                  " << tests.full_time
		  << std::endl
		  << "	shitty error:                     " << tests.sink
		  << std::endl
		  << "	good error:                       " << tests.ehhhror
		  << std::endl
		  << "	func 1 time taken:                " << tests.func1_time
		  << std::endl
		  << "	func 2 time taken:                " << tests.func2_time
		  << std::endl
		  << "	func 1 sink:                      " << tests.func1_sink
		  << std::endl
		  << "	func 2 sink:                      " << tests.func2_sink
		  << std::endl
		  << "	func 1 evaluated at " << end << ":        " << f1(end)
		  << std::endl
		  << "	func 2 evaluated at " << end << ":        " << f2(end)
		  << std::endl
		  << "	func 1 evaluated at " << start << ":            "
		  << f1(start) << std::endl
		  << "	func 2 evaluated at " << start << ":            "
		  << f2(start) << std::endl;
}

void test_quadratic()
{

	Quadratic quad1(5, 4, 2);
	Quadratic quad2(0.4, 9, -10);

	std::cout << "quadratic #1 info:" << std::endl
		  << "    " << quad1.display() << std::endl
		  << "    first solution:   " << quad1.roots[0] << std::endl
		  << "    second solution:  " << quad1.roots[1] << std::endl
		  << std::endl
		  << "    vertex x:         " << quad1.vertex().x << std::endl
		  << "    vertex y:         " << quad1.vertex().y << std::endl
		  << std::endl
		  << "    y-intercept:      " << quad1.y_intercept()
		  << std::endl
		  << std::endl
		  << std::endl
		  << "quadratic #2 info:" << std::endl
		  << "    " << quad2.display() << std::endl
		  << "    first solution:   " << quad2.roots[0] << std::endl
		  << "    second solution:  " << quad2.roots[1] << std::endl
		  << std::endl
		  << "    vertex x:         " << quad2.vertex().x << std::endl
		  << "    vertex y:         " << quad2.vertex().y << std::endl
		  << std::endl
		  << "    y-intercept:      " << quad2.y_intercept()
		  << std::endl
		  << std::endl
		  << std::endl;
}

void test_linear()
{
	Linear l1(5, 9);
	Linear l2(0.2, constants::E);

	std::cout << "linear #1 info:   " << std::endl
		  << "    " << l1.display() << std::endl
		  << "    x-intercept:      " << l1.x_intercept() << std::endl
		  << "    y-intercept:      " << l1.y_intercept() << std::endl
		  << std::endl
		  << std::endl
		  << "linear #2 info:   " << std::endl
		  << "    " << l2.display() << std::endl
		  << "    x-intercept:      " << l2.x_intercept() << std::endl
		  << "    y-intercept:      " << l2.y_intercept() << std::endl
		  << std::endl
		  << std::endl
		  << "solution for equation " << l1.display() << " = "
		  << l2.display() << ": " << std::endl
		  << "    x = " << solve_linear(l1, l2) << std::endl;
}

int main()
{
	auto f = [](real x) {return std::log(x);};
	auto f2 = [](real x) {return Logarithm::log(x);};
	test(f, "libm log", f2, "custom log");
}