#include "UFDS.h"
#include <iostream>

int main(int argc, char* argv[])
{
	ds::ufds ufds(10);
	ufds.union_set(1, 8);
	ufds.union_set(8, 9);
	ufds.union_set(8, 3);

	const auto is_same_set = ufds.is_same_set(1, 4);
	std::cout << "is same set (1, 4): " << is_same_set << std::endl;
	return 0;
}
