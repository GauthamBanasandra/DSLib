#pragma once
#include <memory>
#include <cassert>

namespace ds
{
	template<typename T>
	class node
	{
	public:
		explicit node(T data) : data(data), height(1)
		{
		}

		T data;
		long long height;
	};

	namespace bin_tree
	{
		enum class node_type { k_left_child, k_right_child, k_root };

		template<typename T>
		class node : public ds::node<T>
		{
		public:
			explicit node(T data, const node_type type) : ds::node<T>(data), node_type(type), ancestor(nullptr), left_child(nullptr), right_child(nullptr)
			{
			}

			bool is_leaf() { return left_child == nullptr && right_child == nullptr; }
			void copy_data_to(node<T> *other) { other->data = this->data; }
			static void remove(node<T> *&n);

			node_type node_type;
			node<T> *ancestor;
			node<T> *left_child;
			node<T> *right_child;
		};

		template <typename T>
		void node<T>::remove(node<T> *&n)
		{
			n->left_child = n->right_child = nullptr;
			auto &ancestor = n->ancestor;
			switch (n->node_type)
			{
			case node_type::k_left_child:
				ancestor->left_child = nullptr;
				break;

			case node_type::k_right_child:
				ancestor->right_child = nullptr;
				break;

			case node_type::k_root:
				break;

			default:
				// Unhandled node type
				assert(false);
			}

			delete n;
			n = nullptr;
		}
	}
}
