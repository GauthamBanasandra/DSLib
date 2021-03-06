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
			node<T> *z;
			// Node y is the child of z with a greater height
			node<T> *y;
			// Node x is the child of y with a greater height
			node<T> *x;
			// Denotes the configuration of z, y and x nodes
			imbalance_config config;
		};

		template<class T>
		class avl : public bst<T>
		{
		public:
			node<T> *insert(T& key) override;

		private:
			node<T> *insert(node<T> *n, node_info<T> &node_info);

			// Performs trinode restructuring to maintain the height of the binary tree log(h)
			// Returns the root of the restructured sub-tree
			node<T> *restructure(const imbalance_info<T> &info);

			// Right rotation is performed for LL case - x is left child of y and y is left child of z
			void right_rotate(node<T> *n);

			// Left rotation is performed for RR case - x is right child of y and y is right child of z
			void left_rotate(node<T> *n);

			// Finds imbalance from the node n, imbalance info is provided as an out parameter
			imbalance_info<T> find_imbalance(node<T> *n, const long long height_diff);

			// Promotes child to be parent's peer
			// Parent will transfer its ancestral relationship to child
			void promote_child(node<T> *parent, node<T> *child);
		};

		template <class T>
		node<T> *avl<T>::insert(T& key)
		{
			if (this->root == nullptr)
			{
				this->root = new node<T>(key, node_type::k_root);
				return this->root;
			}

			node_info<T> node_info{};
			node_info.key = &key;
			return insert(this->root, node_info);
		}

		template <class T>
		node<T> *avl<T>::insert(node<T> *n, node_info<T> &node_info)
		{
			// Insert the key just like a BST
			if (n == nullptr)
			{
				auto new_node = new node<T>(*node_info.key, node_info.type);
				new_node->ancestor = node_info.ancestor;
				switch (node_info.type) {
				case node_type::k_left_child:
					node_info.ancestor->left_child = new_node;
					break;

				case node_type::k_right_child:
					node_info.ancestor->right_child = new_node;
					break;

				case node_type::k_root:
					assert(false);
					break;

				default:
					assert(false);
				}

				return new_node;
			}

			node_info.ancestor = n;
			if (*node_info.key <= n->data)
			{
				node_info.type = node_type::k_left_child;
				insert(n->left_child, node_info);
			}
			else
			{
				node_info.type = node_type::k_right_child;
				insert(n->right_child, node_info);
			}

			n->height = std::max(get_height(n->left_child), get_height(n->right_child)) + 1;

			const auto height_diff = get_height(n->left_child) - get_height(n->right_child);

			// If the height difference between left and right children is 0, 1 or -1, there is no imbalance
			// Proceed to check if there is any imbalance in the ancestor node
			if (!(height_diff == 0 || height_diff == 1 || height_diff == -1))
			{
				// If there is any imbalance, then restructure the tree
				const auto info = find_imbalance(n, height_diff);
				n = restructure(info);
			}

			return n;
		}

		template <class T>
		node<T> *avl<T>::restructure(const imbalance_info<T> &info)
		{
			if (info.config == imbalance_config::k_ll)
			{
				right_rotate(info.z);
				return info.y;
			}

			if (info.config == imbalance_config::k_lr)
			{
				left_rotate(info.y);
				right_rotate(info.z);
				return info.x;
			}

			if (info.config == imbalance_config::k_rr)
			{
				left_rotate(info.z);
				return info.y;
			}

			// Only 4 rotations are possible LL, LR, RR and RL
			assert(info.config == imbalance_config::k_rl);
			right_rotate(info.y);
			left_rotate(info.z);
			return info.x;
		}

		// Right rotate on node n
		template <class T>
		void avl<T>::right_rotate(node<T> *n)
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

			// Update the heights of the rotated nodes
			n->height = std::max(get_height(n->left_child), get_height(n->right_child)) + 1;
			child->height = std::max(get_height(child->left_child), get_height(child->right_child)) + 1;
		}

		// This is a mirror of right_rotate i.e. all 'left' will become 'right' irrespective of the context/type
		template <class T>
		void avl<T>::left_rotate(node<T> *n)
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

			n->height = std::max(get_height(n->left_child), get_height(n->right_child)) + 1;
			child->height = std::max(get_height(child->left_child), get_height(child->right_child)) + 1;
		}

		template <class T>
		imbalance_info<T> avl<T>::find_imbalance(node<T> *n, const long long height_diff)
		{
			imbalance_info<T> info;
			// Otherwise, there is some imbalance
			// The node with imbalance is denoted as z
			info.z = n;
			if (height_diff > 0)
			{
				// Since we subtract right child's height from left child's height, 
				// if the difference is positive, then left child has a greater height compared to right child
				// Child of z with the greater height is denoted as y
				info.y = n->left_child;
				// TODO : Check if node's height member can be used here
				if (get_height(info.y->left_child) >= get_height(info.y->right_child))
				{
					// x is child of y which has the longer path
					info.x = info.y->left_child;
					info.config = imbalance_config::k_ll;
				}
				else
				{
					info.x = info.y->right_child;
					info.config = imbalance_config::k_lr;
				}
			}
			else
			{
				info.y = n->right_child;
				if (get_height(info.y->left_child) >= get_height(info.y->right_child))
				{
					info.x = info.y->left_child;
					info.config = imbalance_config::k_rl;
				}
				else
				{
					info.x = info.y->right_child;
					info.config = imbalance_config::k_rr;
				}
			}

			return info;
		}

		template <class T>
		void avl<T>::promote_child(node<T> *parent, node<T> *child)
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
				parent->ancestor->left_child = child;
				child->node_type = node_type::k_left_child;
				break;

				// Make 'child' the right child of parent's ancestor
			case node_type::k_right_child:
				parent->ancestor->right_child = child;
				child->node_type = node_type::k_right_child;
				break;

				// Not handled for this node_type 
			default:
				assert(false);
			}
		}
	}
}
