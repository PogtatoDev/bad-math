#include <chrono>
#include <iostream>
#include "include/constants.hpp"
#include "include/expo.hpp"
#include "include/general.hpp"

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

int main()
{
	Timer t;
	real sink = 0;
	for (real i = 0.1; i < 60.1; i++)
	{
		std::cout << Expo::exp(i) - std::exp(i) << "     " << i << std::endl;

	}
	std::cout << t.elapsed() << std::endl;
	std::cout << sink << std::endl;
}