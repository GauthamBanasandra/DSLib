#include "Sequence.h"

#include <iostream>

int main(int argc, char* argv[])
{
	const std::vector<int> numbers{ 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };

	for (auto number : ds::seq::longest_increasing_latest_elements(numbers))
	{
		std::cout << number << " ";
	}
	std::cout << std::endl;

	/*const std::vector<std::size_t> lis_indices{ 0, 2, 3 };
	const auto find_it = std::lower_bound(lis_indices.begin(), lis_indices.end(), 2, [&numbers](const std::size_t &i_lis, const int &number) -> bool
	{
		std::cout << "i_lis : " << i_lis << "\tnumbers[i_lis] : " << numbers[i_lis] << "\tnumber : " << number << std::endl;
		return numbers[i_lis] < number;
	});

	std::cout << *find_it << std::endl;*/
	return 0;
}
