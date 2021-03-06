#include <algorithm>

#include "EulerTour.h"

EulerTour::EulerTour(const size_t num_nodes, const std::vector<std::pair<NodeId, NodeId>>& edge_list, const bool is_directed) :num_nodes_{ num_nodes }, edge_list_{ edge_list }
{
	adj_list_.resize(num_nodes_);
	for (const auto& [u, v] : edge_list)
	{
		adj_list_[u].emplace_back(v);
		if (!is_directed)
		{
			adj_list_[v].emplace_back(u);
		}
	}
}

std::list<EulerTour::Edge> EulerTour::Get(const NodeId start_node_id)
{
	std::list<Edge> tour;
	Tour(start_node_id, tour, tour.begin());
	std::reverse(tour.begin(), tour.end());
	return tour;
}

void EulerTour::Tour(const NodeId node_id, std::list<Edge>& tour, const std::list<Edge>::iterator& tour_it)
{
	for (auto& adj_node : adj_list_[node_id])
	{
		if (!adj_node.use_edge)
		{
			continue;
		}
		adj_node.use_edge = false;

		for (auto& a_node : adj_list_[adj_node.id])
		{
			if (a_node.id == node_id && a_node.use_edge)
			{
				a_node.use_edge = false;
				break;
			}
		}

		Tour(adj_node.id, tour, tour.emplace(tour_it, node_id, adj_node.id));
	}
}
