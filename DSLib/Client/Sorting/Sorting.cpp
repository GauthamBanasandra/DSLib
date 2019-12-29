#include <random>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Merge-sort.h"
#include "Quick-sort.h"

int main(int argc, char* argv[])
{
	std::vector<int> numbers{ 5, 2, 6, 9, 2, 3, 2 };

	alg::sorting::merge<int> m(numbers);
	std::cout << "Merge sort:" << std::endl;
	auto separator = "";
	for (const auto& number : m.sort())
	{
		std::cout << separator << number;
		separator = " ";
	}
	std::cout << std::endl;

	std::shuffle(numbers.begin(), numbers.end(), std::mt19937(std::random_device()()));

	alg::sorting::quick<int> q(numbers);
	std::cout << "\nQuick sort:" << std::endl;
	separator = "";
	for (const auto& number : q.sort())
	{
		std::cout << separator << number;
		separator = " ";
	}
	return 0;
}
