#include "Sequence.h"

#include <iostream>

int main(int argc, char* argv[])
{
	std::vector<int> v{ 1 };
	for (auto number : ds::seq::longest_increasing<int>(v))
	{
		std::cout << number << " ";
	}
	auto find_it = std::lower_bound(v.begin(), v.end(), 1);
	auto i_insert = std::distance(v.begin(), find_it);
	std::cout << i_insert << std::endl;
	return 0;
}
