#pragma once
#include "Node.h"
#include "BinaryTree.h"

#include <unordered_map>

namespace ds
{
	namespace bin_tree
	{
		// Represents start and end of a segment
		struct range
		{
			std::size_t lower_bound;
			std::size_t upper_bound;
		};

		// Response of a query call
		template<class T>
		struct response
		{
			bool is_valid;
			T data;
		};

		template<class T, class U>
		struct seg_data
		{
			seg_data() :is_lazy(false) {}

			T data;
			bool is_lazy;
			U lazy_data;
		};

		template<class C, class T, class U>
		class seg_tree : public binary_tree<seg_data<T, U>>
		{
		public:
			// container is a void pointer to the container
			// access_data - function pointer which returns the data from the container for the given index
			// merge_nodes - function pointer which performs the operation on 2 data points (min, max, sum etc.) and returns the result
			explicit seg_tree(const C& container, std::size_t size,
				T(*access_data)(const C&, std::size_t),
				T(*merge_nodes)(T, T),
				T(*update_data)(const range& segment, const T& node_data, const U& data));

			// Returns the result of the operation on the specified segment
			response<T> query(const range& query_segment);

			// Updates the values in the specified segment
			void update_range(const range& update_segment, const U& data);
			void update_point(std::size_t idx, const T& data);

			C container;
			std::size_t size;
			T(*merge_nodes)(T, T);
			T(*access_data)(const C&, std::size_t);
			T(*update_data)(const range& segment, const T& node_data, const U& data);

		private:
			node<seg_data<T, U>>* build_tree(node_type type, const range& segment) const;
			response<T> query(node<seg_data<T, U>>* n, const range& segment, const range& query_segment);
			void update_range(node<seg_data<T, U>>* n, const range& segment, const range& update_segment, const U& data);
			void propagate_laziness(node<seg_data<T, U>>* n, const U& data);
			void update_point(node<seg_data<T, U>>* n, const range& segment, std::size_t idx, const U& data);

			static range left(const range& segment) { return range{ segment.lower_bound, (segment.lower_bound + segment.upper_bound) >> 1 }; }
			static range right(const range& segment) { return range{ ((segment.lower_bound + segment.upper_bound) >> 1) + 1, segment.upper_bound }; }

			// Stores the data which will needs to get updated in the next query/update in each node
			std::unordered_map<node<seg_data<T, U>>*, U> lazy_store_;
		};

		template<class C, class T, class U>
		seg_tree<C, T, U>::seg_tree(const C& container, const std::size_t size,
			T(*access_data)(const C&, const std::size_t),
			T(*merge_nodes)(T, T),
			T(*update_data)(const range& segment, const T& node_data, const U& data)) :
			container(container), size(size), merge_nodes(merge_nodes), access_data(access_data), update_data(update_data)
		{
			const range segment{ 0, size - 1 };
			this->root = build_tree(node_type::k_root, segment);
		}

		template<class C, class T, class U>
		response<T> seg_tree<C, T, U>::query(const range& query_segment)
		{
			const range segment{ 0, size - 1 };
			return query(this->root, segment, query_segment);
		}

		template<class C, class T, class U>
		void seg_tree<C, T, U>::update_range(const range& update_segment, const U& data)
		{
			const range segment{ 0, size - 1 };
			return update_range(this->root, segment, update_segment, data);
		}

		template <class C, class T, class U>
		void seg_tree<C, T, U>::update_point(std::size_t idx, const T& data)
		{
			const range segment{ 0, size - 1 };
			update_point(this->root, segment, idx, data);
		}

		template<class C, class T, class U>
		node<seg_data<T, U>>* seg_tree<C, T, U>::build_tree(const node_type type, const range& segment) const
		{
			// Leaf node
			if (segment.lower_bound == segment.upper_bound)
			{
				// Store the c[i] value in the leaf node
				seg_data<T, U> node_data;
				node_data.data = access_data(container, segment.lower_bound);
				return new node<seg_data<T, U>>(node_data, type);
			}

			const auto left_child = build_tree(node_type::k_left_child, left(segment));
			const auto right_child = build_tree(node_type::k_right_child, right(segment));

			// Perform operation on the 2 nodes and store its result in the parent node
			seg_data<T, U> node_data;
			node_data.data = merge_nodes(left_child->data.data, right_child->data.data);
			node<seg_data<T, U>>* new_node = new node<seg_data<T, U>>(node_data, type);

			new_node->left_child = left_child;
			new_node->right_child = right_child;
			left_child->ancestor = right_child->ancestor = new_node;
			return new_node;
		}

		template<class C, class T, class U>
		response<T> seg_tree<C, T, U>::query(node<seg_data<T, U>>* n, const range& segment, const range& query_segment)
		{
			// Outside query range
			if (query_segment.lower_bound > segment.upper_bound || query_segment.upper_bound < segment.lower_bound)
			{
				return response<T>{ false };
			}

			// Check if the current node is lazy
			auto find = lazy_store_.find(n);
			if (find != lazy_store_.end())
			{
				// Current node has some lazy data pending, update it first
				n->data.data = update_data(segment, n->data.data, find->second);

				// If the current node isn't a leaf node, then propagate laziness to its children
				propagate_laziness(n, find->second);

				// Get rid of the laziness!
				lazy_store_.erase(find);
			}

			// Completely within the query range
			if (segment.lower_bound >= query_segment.lower_bound && segment.upper_bound <= query_segment.upper_bound)
			{
				return response<T>{ true, n->data.data };
			}

			const auto left_response = query(n->left_child, left(segment), query_segment);
			const auto right_response = query(n->right_child, right(segment), query_segment);

			if (!left_response.is_valid)
			{
				return right_response;
			}

			if (!right_response.is_valid)
			{
				return left_response;
			}

			return response<T>{ true, merge_nodes(left_response.data, right_response.data) };
		}

		template<class C, class T, class U>
		void seg_tree<C, T, U>::update_range(node<seg_data<T, U>>* n, const range& segment, const range& update_segment, const U& data)
		{
			auto find = lazy_store_.find(n);
			if (find != lazy_store_.end())
			{
				// If the current node is lazy, need to update the node with the lazy value, if it exists
				n->data.data = update_data(segment, n->data.data, find->second);

				// If the current node isn't a leaf node, mark its children as lazy
				propagate_laziness(n, find->second);

				lazy_store_.erase(find);
			}

			// Completely outside query range
			if (update_segment.lower_bound > segment.upper_bound || update_segment.upper_bound < segment.lower_bound)
			{
				return;
			}

			// Completely within query range
			if (segment.lower_bound >= update_segment.lower_bound && segment.upper_bound <= update_segment.upper_bound)
			{
				n->data.data = update_data(segment, n->data.data, data);

				// If the current node isn't a leaf node, mark its children as lazy
				propagate_laziness(n, data);
				return;
			}

			update_range(n->left_child, left(segment), update_segment, data);
			update_range(n->right_child, right(segment), update_segment, data);

			n->data.data = merge_nodes(n->left_child->data.data, n->right_child->data.data);
		}

		// Induces/updates the laziness associated with the current node to its children
		template<class C, class T, class U>
		void seg_tree<C, T, U>::propagate_laziness(node<seg_data<T, U>>* n, const U& data)
		{
			if (n->left_child == nullptr || n->right_child == nullptr)
			{
				return;
			}

			// Mark its  children as lazy, with the lazy data
			lazy_store_[n->left_child] = data;
			lazy_store_[n->right_child] = data;
		}

		template <class C, class T, class U>
		void seg_tree<C, T, U>::update_point(node<seg_data<T, U>>* n, const range& segment, std::size_t idx, const U& data)
		{
			const auto i = idx;
			const auto j = idx;
			if (i > segment.upper_bound || j < segment.lower_bound)
			{
				return;
			}

			if (i == segment.lower_bound && j == segment.upper_bound)
			{
				n->data.data = update_data(segment, n->data.data, data);
				return;
			}

			update_point(n->left_child, left(segment), idx, data);
			update_point(n->right_child, right(segment), idx, data);

			n->data.data = merge_nodes(n->left_child->data.data, n->right_child->data.data);
		}
	}
}
