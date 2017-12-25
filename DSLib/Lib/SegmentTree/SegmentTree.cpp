#include "SegmentTree.h"

namespace ds
{
	namespace bin_tree
	{
		seg_tree::seg_tree(const void* container_cookie, const std::size_t size, node<std::size_t>* (*merge_nodes)(const void*, node<std::size_t>*, node<std::size_t>*)) : container_cookie(container_cookie), merge_nodes(merge_nodes), size(size)
		{
			const range segment{ 0, size - 1 };
			this->root = build_tree(node_type::k_root, segment);
		}

		node<std::size_t>* seg_tree::query(const range& query_segment) const
		{
			const range segment{ 0, size - 1 };
			return query(this->root, segment, query_segment);
		}

		node<std::size_t>* seg_tree::build_tree(const node_type type, const range& segment) const
		{
			if (segment.lower_bound == segment.upper_bound)
			{
				return new node<std::size_t>(segment.lower_bound, type);
			}

			range new_segment;
			new_segment.lower_bound = segment.lower_bound;
			new_segment.upper_bound = (segment.lower_bound + segment.upper_bound) >> 1;
			const auto left_child = build_tree(node_type::k_left_child, new_segment);

			new_segment.lower_bound = new_segment.upper_bound + 1;
			new_segment.upper_bound = segment.upper_bound;
			const auto right_child = build_tree(node_type::k_right_child, new_segment);

			const auto new_node = new node<std::size_t>(merge_nodes(container_cookie, left_child, right_child)->data, type);
			new_node->left_child = left_child;
			new_node->right_child = right_child;
			left_child->ancestor = right_child->ancestor = new_node;
			return new_node;
		}


		node<std::size_t>* seg_tree::query(node<std::size_t>* n, const range& segment, const range& query_segment) const
		{
			if (query_segment.lower_bound > segment.upper_bound || query_segment.upper_bound < segment.lower_bound)
			{
				return nullptr;
			}

			if (segment.lower_bound >= query_segment.lower_bound && segment.upper_bound <= query_segment.upper_bound)
			{
				return n;
			}

			range new_segment;
			new_segment.lower_bound = segment.lower_bound;
			new_segment.upper_bound = (segment.lower_bound + segment.upper_bound) >> 1;
			const auto left_child = query(n->left_child, new_segment, query_segment);

			new_segment.lower_bound = new_segment.upper_bound + 1;
			new_segment.upper_bound = segment.upper_bound;
			const auto right_child = query(n->right_child, new_segment, query_segment);

			if (left_child == nullptr)
			{
				return right_child;
			}

			if (right_child == nullptr)
			{
				return left_child;
			}

			return merge_nodes(container_cookie, left_child, right_child);
		}
	}
}
