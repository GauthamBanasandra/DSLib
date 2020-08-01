#include <vector>
#include <utility>
#include <iostream>
#include <ostream>

#include "EulerTour.h"

int main(int argc, char* argv[])
{
	const std::vector<std::pair<EulerTour::NodeId, EulerTour::NodeId>> edge_list{
		{0, 1},
		{0, 2},
		{1, 2},
		{1, 4},
		{1, 3},
		{2, 4},
		{2, 3},
		{4, 3}
	};

	const size_t num_nodes = 5;
	EulerTour tour(num_nodes, edge_list, false);

	for (const auto& node_id : tour.Get(4))
	{
		std::cout << node_id << std::endl;
	}
	return 0;
}
