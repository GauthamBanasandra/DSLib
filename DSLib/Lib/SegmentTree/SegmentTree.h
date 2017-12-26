#pragma once
#include "Node.h"
#include "BinaryTree.h"

namespace ds
{
	namespace bin_tree
	{
		struct range
		{
			std::size_t lower_bound;
			std::size_t upper_bound;
		};

		template<class T>
		struct response
		{
			bool is_valid;
			T data;
		};

		template<class T>
		class seg_tree : public binary_tree<T>
		{
		public:
			explicit seg_tree(const void* container_cookie, std::size_t size, T(*get_data)(const void*, std::size_t), T(*merge_nodes)(T, T));

			response<T> query(const range& query_segment) const;

			const void* container_cookie;
			std::size_t size;
			T(*merge_nodes)(T, T);
			T(*get_data)(const void*, std::size_t);

		private:
			node<T>* build_tree(node_type type, const range& segment) const;
			response<T> query(node<T>* n, const range& segment, const range& query_segment) const;
		};

		template<class T>
		seg_tree<T>::seg_tree(const void* container_cookie, const std::size_t size, T(*get_data)(const void*, std::size_t), T(*merge_nodes)(T, T)) : container_cookie(container_cookie), size(size), merge_nodes(merge_nodes), get_data(get_data)
		{
			const range segment{ 0, size - 1 };
			this->root = build_tree(node_type::k_root, segment);
		}

		template<class T>
		response<T> seg_tree<T>::query(const range& query_segment) const
		{
			const range segment{ 0, size - 1 };
			return query(this->root, segment, query_segment);
		}

		template<class T>
		node<T>* seg_tree<T>::build_tree(const node_type type, const range& segment) const
		{
			if (segment.lower_bound == segment.upper_bound)
			{
				return new node<T>(get_data(container_cookie, segment.lower_bound), type);
			}

			range new_segment;
			new_segment.lower_bound = segment.lower_bound;
			new_segment.upper_bound = (segment.lower_bound + segment.upper_bound) >> 1;
			const auto left_child = build_tree(node_type::k_left_child, new_segment);

			new_segment.lower_bound = new_segment.upper_bound + 1;
			new_segment.upper_bound = segment.upper_bound;
			const auto right_child = build_tree(node_type::k_right_child, new_segment);

			const auto new_node = new node<T>(merge_nodes(left_child->data, right_child->data), type);
			new_node->left_child = left_child;
			new_node->right_child = right_child;
			left_child->ancestor = right_child->ancestor = new_node;
			return new_node;
		}


		template<class T>
		response<T> seg_tree<T>::query(node<T>* n, const range& segment, const range& query_segment) const
		{
			if (query_segment.lower_bound > segment.upper_bound || query_segment.upper_bound < segment.lower_bound)
			{
				return response<T>{ false };
			}

			if (segment.lower_bound >= query_segment.lower_bound && segment.upper_bound <= query_segment.upper_bound)
			{
				return response<T>{ true, n->data };
			}

			range new_segment;
			new_segment.lower_bound = segment.lower_bound;
			new_segment.upper_bound = (segment.lower_bound + segment.upper_bound) >> 1;
			const auto left_child = query(n->left_child, new_segment, query_segment);

			new_segment.lower_bound = new_segment.upper_bound + 1;
			new_segment.upper_bound = segment.upper_bound;
			const auto right_child = query(n->right_child, new_segment, query_segment);

			if (!left_child.is_valid)
			{
				return right_child;
			}

			if (!right_child.is_valid)
			{
				return left_child;
			}

			return response<T>{ true, merge_nodes(left_child.data, right_child.data) };
		}
	}
}
