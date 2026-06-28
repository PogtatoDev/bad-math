#include "include/trig.hpp"
#include <cstdint>
#include <iostream>
#include <chrono>

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
    for (uint64_t k=0; k < 99999999; k++)
        sink += Trig::fast_sin(k);
    std::cout << sink << std::endl;
    std::cout << t.elapsed() << std::endl;
}