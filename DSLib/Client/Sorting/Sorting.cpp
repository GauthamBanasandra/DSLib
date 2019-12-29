#include <vector>
#include <iostream>

#include "Merge-sort.h"

int main(int argc, char* argv[])
{
	std::vector<int> numbers{ 5, 2, 6, 9, 2, 3, 2 };
	alg::sorting::merge<int> m(numbers);

	auto separator = "";
	for (const auto& number : m.sort())
	{
		std::cout << separator << number;
		separator = " ";
	}
	return 0;
}
