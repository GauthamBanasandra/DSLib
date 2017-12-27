#pragma once
#include "Node.h"
#include "BinaryTree.h"

#include <unordered_map>

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

			response<T> query(const range& query_segment);
			void update_range(const range& update_segment, const T data);

			const void* container_cookie;
			std::size_t size;
			T(*merge_nodes)(T, T);
			T(*get_data)(const void*, std::size_t);

		private:
			node<T>* build_tree(node_type type, const range& segment) const;
			response<T> query(node<T>* n, const range& segment, const range& query_segment);
			void update_range(node<T>* n, const range& segment, const range& update_segment, const T data);


			std::unordered_map<node<T>*, T> lazy_store_;
		};

		template<class T>
		seg_tree<T>::seg_tree(const void* container_cookie, const std::size_t size, T(*get_data)(const void*, std::size_t), T(*merge_nodes)(T, T)) : container_cookie(container_cookie), size(size), merge_nodes(merge_nodes), get_data(get_data)
		{
			const range segment{ 0, size - 1 };
			this->root = build_tree(node_type::k_root, segment);
		}

		template<class T>
		response<T> seg_tree<T>::query(const range& query_segment)
		{
			const range segment{ 0, size - 1 };
			return query(this->root, segment, query_segment);
		}

		template <class T>
		void seg_tree<T>::update_range(const range& update_segment, const T data)
		{
			const range segment{ 0, size - 1 };
			return update_range(this->root, segment, update_segment, data);
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
		response<T> seg_tree<T>::query(node<T>* n, const range& segment, const range& query_segment)
		{
			if (query_segment.lower_bound > segment.upper_bound || query_segment.upper_bound < segment.lower_bound)
			{
				return response<T>{ false };
			}

			auto find = lazy_store_.find(n);
			if (find != lazy_store_.end())
			{
				n->data = merge_nodes(n->data, find->second);
				if (segment.lower_bound != segment.upper_bound)
				{
					auto left_find = lazy_store_.find(n->left_child);
					if (left_find != lazy_store_.end())
					{
						left_find->second = merge_nodes(left_find->second, find->second);
					}
					else
					{
						lazy_store_[n->left_child] = find->second;
					}

					auto right_find = lazy_store_.find(n->right_child);
					if (right_find != lazy_store_.end())
					{
						right_find->second = merge_nodes(right_find->second, find->second);
					}
					else
					{
						lazy_store_[n->right_child] = find->second;
					}
				}

				lazy_store_.erase(find);
			}

			if (segment.lower_bound >= query_segment.lower_bound && segment.upper_bound <= query_segment.upper_bound)
			{
				return response<T>{ true, n->data };
			}

			range new_segment;
			new_segment.lower_bound = segment.lower_bound;
			new_segment.upper_bound = (segment.lower_bound + segment.upper_bound) >> 1;
			const auto left_response = query(n->left_child, new_segment, query_segment);

			new_segment.lower_bound = new_segment.upper_bound + 1;
			new_segment.upper_bound = segment.upper_bound;
			const auto right_response = query(n->right_child, new_segment, query_segment);

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

		template <class T>
		void seg_tree<T>::update_range(node<T>* n, const range& segment, const range& update_segment, const T data)
		{
			auto find = lazy_store_.find(n);
			if (find != lazy_store_.end())
			{
				n->data = find->second;
				//n->data = merge_nodes(n->data, find->second);
				if (segment.lower_bound != segment.upper_bound)
				{
					auto left_find = lazy_store_.find(n->left_child);
					if (left_find != lazy_store_.end())
					{
						left_find->second = merge_nodes(left_find->second, find->second);
					}
					else
					{
						lazy_store_[n->left_child] = find->second;
					}

					auto right_find = lazy_store_.find(n->right_child);
					if (right_find != lazy_store_.end())
					{
						right_find->second = merge_nodes(right_find->second, find->second);
					}
					else
					{
						lazy_store_[n->right_child] = find->second;
					}
				}

				lazy_store_.erase(find);
			}

			if (update_segment.lower_bound > segment.upper_bound || update_segment.upper_bound < segment.lower_bound)
			{
				return;
			}

			if (segment.lower_bound >= update_segment.lower_bound && segment.upper_bound <= update_segment.upper_bound)
			{
				n->data = data;
				//n->data = merge_nodes(n->data, data);
				if (segment.lower_bound != segment.upper_bound)
				{
					auto left_find = lazy_store_.find(n->left_child);
					if (left_find != lazy_store_.end())
					{
						left_find->second = merge_nodes(left_find->second, data);
					}
					else
					{
						lazy_store_[n->left_child] = data;
					}

					auto right_find = lazy_store_.find(n->right_child);
					if (right_find != lazy_store_.end())
					{
						right_find->second = merge_nodes(right_find->second, data);
					}
					else
					{
						lazy_store_[n->right_child] = data;
					}
				}

				return;
			}

			range new_segment;
			new_segment.lower_bound = segment.lower_bound;
			new_segment.upper_bound = (segment.lower_bound + segment.upper_bound) >> 1;
			update_range(n->left_child, new_segment, update_segment, data);

			new_segment.lower_bound = new_segment.upper_bound + 1;
			new_segment.upper_bound = segment.upper_bound;
			update_range(n->right_child, new_segment, update_segment, data);

			n->data = merge_nodes(n->left_child->data, n->right_child->data);
		}
	}
}
