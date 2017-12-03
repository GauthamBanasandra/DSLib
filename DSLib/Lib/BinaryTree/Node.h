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
			explicit node(T data, const node_type node_type) : data(data), height(1), node_type(node_type)
			{
			}

			bool is_leaf() { return left_child == nullptr && right_child == nullptr; }
			void replace(std::shared_ptr<node<T>> &root, std::shared_ptr<node<T>> &other);
			void copy_data_to(std::shared_ptr<node<T>> other) { other->data = this->data; }			
			static void remove(std::shared_ptr<node<T>> &other);			

			T data;
			long long height;
			node_type node_type;
			std::weak_ptr<node> ancestor;
			std::shared_ptr<node> left_child;
			std::shared_ptr<node> right_child;
		};

		// Perfoms replacement of the node with other
		// This doesn't handle childrens' links which is the responsibility of the caller
		// TODO : Move this method to bst class to avoid passing root as parameter
		template <typename T>
		void node<T>::replace(std::shared_ptr<node<T>>& root, std::shared_ptr<node<T>>& other)
		{
			auto &ancestor = this->ancestor.lock();
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
		void node<T>::remove(std::shared_ptr<node<T>>& n)
		{
			n->left_child = n->right_child = nullptr;
			auto &ancestor = n->ancestor.lock();
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

			n.reset();
		}
	}
}
