#include "FenwickTree.h"

#include <iostream>

int main(int argc, char* argv[])
{
	std::vector<std::size_t> data = { 1, 2, 3, 4, 5, 6, 7 };
	ds::fen_tree f(data.size());
	for (std::size_t i = 0; i < data.size(); ++i)
	{
		f.update_point(i + 1, data[i]);
	}

	std::cout << f.sum(data.size()) << std::endl;
	return 0;
}
