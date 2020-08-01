#include <vector>
#include <utility>
#include <iostream>
#include <ostream>

#include "EulerTour.h"

int main(int argc, char* argv[])
{
	const std::vector<std::pair<EulerTour::NodeId, EulerTour::NodeId>> edge_list{
		/*{0, 1},
		{0, 2},
		{1, 2},
		{1, 4},
		{1, 3},
		{2, 4},
		{2, 3},
		{4, 3}*/

		{0, 4},
		{4, 1},
		{1, 2},
		{2, 4},
		{4, 3},
		{3, 0}
	};

	const size_t num_nodes = 5;
	EulerTour tour(num_nodes, edge_list, false);


	for (const auto& [u, v] : tour.Get(4))
	{
		std::cout << u << '\t' << v << std::endl;
	}
	return 0;
}
