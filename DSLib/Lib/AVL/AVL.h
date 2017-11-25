#pragma once
#include "BST.h"

namespace ds
{
	enum class imbalance_config { k_ll, k_lr, k_rl, k_rr };

	template<class T>
	struct imbalance_info
	{
		std::shared_ptr<bin_tree::node<T>> z;
		std::shared_ptr<bin_tree::node<T>> y;
		std::shared_ptr<bin_tree::node<T>> x;
		imbalance_config config;
	};

	template<class T>
	class avl : public ds::bst<T>
	{
	public:
		std::shared_ptr<bin_tree::node<T>> insert(T& key) override;

	private:
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
		if (height_diff == 0 || height_diff == 1 || height_diff == -1)
		{
			return find_imbalance(n->ancestor, out_info);
		}

		out_info->z = n;
		if (height_diff > 0)
		{
			out_info->y = n->left_child;
			if (bst<T>::height(out_info->y->left_child) >= bst<T>::height(out_info->y->right_child))
			{
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
