#pragma once
#include "Node.h"
#include "../BinaryTree/BinaryTree.h"

namespace ds
{
	namespace bin_tree
	{
		template<class T>
		node<T> compare(const node<T>* n1, const node<T>* n2)
		{
			return n1->data <= n2->data ? n1 : n2;
		}

		struct range
		{
			std::size_t lower_bound;
			std::size_t upper_bound;
		};

		template<class T>
		class seg_tree : public binary_tree<T>
		{
			node<T>* build_tree(node_type type, const range& segment);
		};

		template <class T>
		node<T>* seg_tree<T>::build_tree(node_type type, const range& segment)
		{
			if (segment.lower_bound == segment.upper_bound)
			{
				return new node<T>(segment.lower_bound, type);
			}

			range new_segment{ segment.lower_bound, segment.lower_bound + segment.upper_bound >> 1 };
			const auto left_child = build_tree(node_type::k_left_child, new_segment);

			new_segment.lower_bound = new_segment.upper_bound + 1;
			new_segment.upper_bound = segment.upper_bound;
			const auto right_child = build_tree(node_type::k_right_child, new_segment);

			auto new_node = new node<T>(compare(left_child, right_child)->data, type);
			left_child->ancestor = right_child->ancestor = new_node;
			return new_node;
		}
	}
}
