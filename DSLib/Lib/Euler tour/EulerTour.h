#pragma once

#include <vector>
#include <list>
#include <utility>

class EulerTour
{
public:
	using NodeId = size_t;
	using Edge = std::pair<NodeId, NodeId>;

	EulerTour(size_t num_nodes, const std::vector<std::pair<NodeId, NodeId>>& edge_list, bool is_directed);

	[[nodiscard]] std::list<Edge> Get(NodeId start_node_id);

private:
	struct Node
	{
		const NodeId id;
		bool use_edge{ true };

		Node(const NodeId id) :id{ id } { }
	};

	void Tour(NodeId node_id, std::list<Edge>& tour, const std::list<Edge>::iterator& tour_it);

	const size_t num_nodes_;
	std::vector<std::vector<Node>> adj_list_;
	const std::vector<std::pair<NodeId, NodeId>>& edge_list_;
};
