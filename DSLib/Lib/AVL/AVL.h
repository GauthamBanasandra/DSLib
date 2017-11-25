#pragma once
#include "BST.h"

namespace ds
{
	enum class imbalance_config { k_ll, k_lr, k_rl, k_rr };

	template<class T>
	struct imbalance_info
	{
		// Node z is where the imbalance starts while traversing upwards from the inserted node
		std::shared_ptr<bin_tree::node<T>> z;
		// Node y is the child of z with a greater height
		std::shared_ptr<bin_tree::node<T>> y;
		// Node x is the child of y with a greater height
		std::shared_ptr<bin_tree::node<T>> x;
		// Denotes the configuration of z, y and x nodes
		imbalance_config config;
	};

	template<class T>
	class avl : public ds::bst<T>
	{
	public:
		std::shared_ptr<bin_tree::node<T>> insert(T& key) override;

	private:
		// Finds imbalance from the node n, imbalance info is provided as an out parameter
		bool find_imbalance(const std::shared_ptr<bin_tree::node<T>> &n, imbalance_info<T> *out_info);
	};

	template <class T>
	std::shared_ptr<bin_tree::node<T>> avl<T>::insert(T& key)
	{
		return bst<T>::insert(key);
	}

	template <class T>
	bool avl<T>::find_imbalance(const std::shared_ptr<bin_tree::node<T>>& n, imbalance_info<T>* out_info)
	{
		if (n == nullptr)
		{
			return false;
		}

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
}
