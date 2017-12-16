#pragma once
#include <memory>
#include <cassert>

namespace ds
{
	namespace bin_tree
	{
		enum class node_type { k_left_child, k_right_child, k_root };

		template<typename T>
		class node
		{
		public:
			virtual ~node() = default;
			explicit node(T data, const node_type node_type) : data(data), height(1), node_type(node_type), ancestor(nullptr), left_child(nullptr), right_child(nullptr)
			{
			}

			bool is_leaf() { return left_child == nullptr && right_child == nullptr; }
			void replace(node<T> *root, node<T> *other);
			void copy_data_to(node<T> * other) { other->data = this->data; }			
			static void remove(node<T> *other);			

			T data;
			long long height;
			node_type node_type;
			node<T> *ancestor;
			node<T> *left_child;
			node<T> *right_child;
		};

		// Perfoms replacement of the node with other
		// This doesn't handle childrens' links which is the responsibility of the caller
		// TODO : Move this method to bst class to avoid passing root as parameter
		template <typename T>
		void node<T>::replace(node<T> * root, node<T> * other)
		{
			auto &ancestor = this->ancestor;
			switch (this->node_type)
			{
			case node_type::k_right_child:
				ancestor->right_child = other;
				break;

			case node_type::k_left_child:
				ancestor->left_child = other;
				break;

			case node_type::k_root:
				root = other;
				break;
			}

			other->ancestor = ancestor;
			other->node_type = this->node_type;			
		}

		template <typename T>
		void node<T>::remove(node<T> * n)
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
		}
	}
}
