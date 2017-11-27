#pragma once
#include "BST.h"

namespace ds
{
	namespace bin_tree
	{
		enum class imbalance_config { k_ll, k_lr, k_rl, k_rr };

		template<class T>
		struct imbalance_info
		{
			// Node z is where the imbalance starts while traversing upwards from the inserted node
			std::shared_ptr<node<T>> z;
			// Node y is the child of z with a greater height
			std::shared_ptr<node<T>> y;
			// Node x is the child of y with a greater height
			std::shared_ptr<node<T>> x;
			// Denotes the configuration of z, y and x nodes
			imbalance_config config;
		};

		template<class T>
		class avl : public bst<T>
		{
		public:
			std::shared_ptr<node<T>> insert(T& key) override;

		private:
			// Performs trinode restructuring to maintain the height of the binary tree log(h)
			void restructure(const imbalance_info<T> *info);

			// Right rotation is performed for LL case - x is left child of y and y is left child of z
			void right_rotate(const std::shared_ptr<node<T>> &n);

			// Left rotation is performed for RR case - x is right child of y and y is right child of z
			void left_rotate(const std::shared_ptr<node<T>> &n);

			// Finds imbalance from the node n, imbalance info is provided as an out parameter
			bool find_imbalance(const std::shared_ptr<node<T>> &n, imbalance_info<T> *out_info);

			// Promotes child to be parent's peer
			// Parent will transfer its ancestral relationship to child
			void promote_child(const std::shared_ptr<node<T>> &parent, const std::shared_ptr<node<T>> &child);
		};

		template <class T>
		std::shared_ptr<node<T>> avl<T>::insert(T& key)
		{
			// Insert the key just like a BST
			auto n = bst<T>::insert(key);

			// If there is any imbalance, then restructure the tree
			imbalance_info<T> info;
			if (find_imbalance(n, &info))
			{
				restructure(&info);
			}

			return n;
		}

		template <class T>
		void avl<T>::restructure(const imbalance_info<T>* info)
		{
			switch (info->config)
			{
			case imbalance_config::k_ll:
				right_rotate(info->z);
				break;

			case imbalance_config::k_lr:
				left_rotate(info->y);
				right_rotate(info->z);
				break;

			case imbalance_config::k_rr:
				left_rotate(info->z);
				break;

			case imbalance_config::k_rl:
				right_rotate(info->y);
				left_rotate(info->z);
				break;

			default:
				// Only 4 configurations are possible LL, LR, RR, RL
				assert(false);
			}
		}

		// Right rotate on node n
		template <class T>
		void avl<T>::right_rotate(const std::shared_ptr<node<T>>& n)
		{
			auto child = n->left_child;
			// n is adopting "child's" right child as its left child
			n->left_child = child->right_child;
			if (n->left_child != nullptr)
			{
				n->left_child->ancestor = n;
				n->left_child->node_type = node_type::k_left_child;
			}

			promote_child(n, child);

			// 'child' will now adopt n as its right child
			child->right_child = n;
			n->ancestor = child;
			n->node_type = node_type::k_right_child;
		}

		// This is a mirror of right_rotate i.e. all 'left' will become 'right' irrespective of the context/type
		template <class T>
		void avl<T>::left_rotate(const std::shared_ptr<node<T>>& n)
		{
			auto child = n->right_child;
			n->right_child = child->left_child;
			if (n->right_child != nullptr)
			{
				n->right_child->ancestor = n;
				n->right_child->node_type = node_type::k_right_child;
			}

			promote_child(n, child);

			child->left_child = n;
			n->ancestor = child;
			n->node_type = node_type::k_left_child;
		}

		template <class T>
		bool avl<T>::find_imbalance(const std::shared_ptr<node<T>>& n, imbalance_info<T>* out_info)
		{
			if (n == nullptr)
			{
				return false;
			}

			// TODO : Need to find an optimal way to cache the node's height
			auto left_child_height = bst<T>::height(n->left_child);
			auto right_child_height = bst<T>::height(n->right_child);
			auto height_diff = left_child_height - right_child_height;

			// If the height difference between left and right children is 0, 1 or -1, there is no imbalance
			// Proceed to check if there is any imbalance in the ancestor node
			if (height_diff == 0 || height_diff == 1 || height_diff == -1)
			{
				return find_imbalance(n->ancestor.lock(), out_info);
			}

			// Otherwise, there is some imbalance
			// The node with imbalance is denoted as z
			out_info->z = n;
			if (height_diff > 0)
			{
				// Since we subtract right child's height from left child's height, 
				// if the difference is positive, then left child has a greater height compared to right child
				// Child of z with the greater height is denoted as y
				out_info->y = n->left_child;
				if (bst<T>::height(out_info->y->left_child) >= bst<T>::height(out_info->y->right_child))
				{
					// x is child of y which has the longer path
					out_info->x = out_info->y->left_child;
					out_info->config = imbalance_config::k_ll;
				}
				else
				{
					out_info->x = out_info->y->right_child;
					out_info->config = imbalance_config::k_lr;
				}
			}
			else
			{
				out_info->y = n->right_child;
				if (bst<T>::height(out_info->y->left_child) >= bst<T>::height(out_info->y->right_child))
				{
					out_info->x = out_info->y->left_child;
					out_info->config = imbalance_config::k_rl;
				}
				else
				{
					out_info->x = out_info->y->right_child;
					out_info->config = imbalance_config::k_rr;
				}
			}

			return true;
		}

		template <class T>
		void avl<T>::promote_child(const std::shared_ptr<node<T>>& parent,
			const std::shared_ptr<node<T>>& child)
		{
			// parent's ancestor will adopt 'child'
			child->ancestor = parent->ancestor;
			switch (parent->node_type)
			{
				// child will now take the place of parent
				// So, if parent was the root node, then child will be the new root
			case node_type::k_root:
				this->root = child;
				child->node_type = node_type::k_root;
				break;

				// Make 'child' the left child of parent's ancestor
			case node_type::k_left_child:
				parent->ancestor.lock()->left_child = child;
				child->node_type = node_type::k_left_child;
				break;

				// Make 'child' the right child of parent's ancestor
			case node_type::k_right_child:
				parent->ancestor.lock()->right_child = child;
				child->node_type = node_type::k_right_child;
				break;

				// Not handled for this node_type 
			default:
				assert(false);
			}
		}
	}
}
