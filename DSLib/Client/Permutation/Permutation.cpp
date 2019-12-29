#include <iostream>
#include <vector>
#include <ostream>

#include "Permutation.h"

int main(int argc, char* argv[])
{
	std::vector<int> numbers{ 0, 1, 2, 5, 3, 3, 0 };
	alg::permutation::next_lexicographic(numbers);

	auto separator = "";
	for (const auto& number : numbers)
	{
		std::cout << separator << number;
		separator = " ";
	}
	std::cout << std::endl;
	return 0;
}
