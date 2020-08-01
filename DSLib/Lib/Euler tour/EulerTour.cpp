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

std::vector<std::pair<EulerTour::NodeId, EulerTour::NodeId>> EulerTour::Get(const NodeId start_node_id)
{
	std::vector<std::pair<NodeId, NodeId>> tour;
	tour.reserve(edge_list_.size());
	Tour(start_node_id, tour);
	return tour;
}

void EulerTour::Tour(const NodeId node_id, std::vector<std::pair<NodeId, NodeId>>& tour)
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

		tour.emplace_back(node_id, adj_node.id);
		Tour(adj_node.id, tour);
	}
}
