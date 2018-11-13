#include "Sequence.h"

#include <iostream>

int main(int argc, char* argv[])
{
	const std::vector<int> v{
		//-7, 10, 9, 2, 3, 8, 8, 6 
		//6, 1, 5, 4, 7, 3, 2, 9, 8, 10
		//15,27,14,38,26,55,46,65,85
		2, 7, 4, 3, 8
	};
	for (auto number : ds::seq::longest_increasing(v))
	{
		std::cout << number << " ";
	}
	std::cout << std::endl;
	return 0;
}
