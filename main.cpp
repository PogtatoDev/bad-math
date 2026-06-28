#include "include/special.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	std::cout << Special::max(std::stof(argv[1]), std::stof(argv[2])) << std::endl;
	return 0;
}