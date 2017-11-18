#pragma once
#include "BinaryTree.h"

namespace ds
{
	template<class T>
	class bst :public binary_tree<T>
	{
	public:
		bst() :binary_tree<T>() {}		
		~bst() {}

		bool search(const T &key) const;
		std::shared_ptr<bin_tree::node<T>> search(const T &key, std::shared_ptr<bin_tree::node<T>> n) const;

	 	std::shared_ptr<bin_tree::node<T>> successor(const T &key);
		std::shared_ptr<bin_tree::node<T>> predecessor(const T &key);
		std::shared_ptr<bin_tree::node<T>> find_min();
		std::shared_ptr<bin_tree::node<T>> find_max();

		std::shared_ptr<bin_tree::node<T>> insert(T& key) override;
		bool remove(T key) override;

	private: // TODO : shared_ptr could be move rather than copied
		std::shared_ptr<bin_tree::node<T>> successor_up(std::shared_ptr<bin_tree::node<T>> n);
		std::shared_ptr<bin_tree::node<T>> successor_down(std::shared_ptr<bin_tree::node<T>> n);
		std::shared_ptr<bin_tree::node<T>> predecessor_up(std::shared_ptr<bin_tree::node<T>> n);
		std::shared_ptr<bin_tree::node<T>> predecessor_down(std::shared_ptr<bin_tree::node<T>> n);
		std::shared_ptr<bin_tree::node<T>> insert(T &key, std::shared_ptr<bin_tree::node<T>> n);
	};

	template <class T>
	bool bst<T>::search(const T& key) const
	{
		if (search(key, this->root) == nullptr)
		{
			return false;
		}

		return true;
	}

	template <class T>
	std::shared_ptr<bin_tree::node<T>> bst<T>::search(const T& key, std::shared_ptr<bin_tree::node<T>> n) const
	{
		if (n == nullptr)
		{
			return nullptr;
		}

		if (n->data == key)
		{
			return n;
		}

		if (key < n->data)
		{
			return search(key, n->left_child);
		}

		return search(key, n->right_child);
	}

	template <class T>
	std::shared_ptr<bin_tree::node<T>>  bst<T>::successor(const T& key)
	{
		auto n = search(key, this->root);
		if (n == nullptr)
		{
			// If the key is not found, then there's no successor
			return nullptr;
		}

		// There are 2 cases 
		// If there's a right child, then recurse down to find the left most child in this path
		if (n->right_child != nullptr)
		{
			return successor_down(n->right_child);
		}

		// If there's no right child but the node has an ancestor, 
		// then traverse up till the node is a left child of its parent,
		// then the successor is the ancestor of the current node
		if (n->ancestor.lock() != nullptr)
		{
			return successor_up(n);
		}

		// If both the above cases don't work then it's the greatest element
		return nullptr;
	}

	template <class T>
	std::shared_ptr<bin_tree::node<T>> bst<T>::predecessor(const T& key)
	{
		auto n = search(key, this->root);
		if (n == nullptr)
		{
			// If the key is not found, then there's no predecessor
			return nullptr;
		}

		// There are 2 cases 
		// If there's a left child, then recurse down to find the right most child in this path
		if (n->left_child != nullptr)
		{
			return predecessor_down(n->left_child);
		}

		// If there's no left child but the node has an ancestor, 
		// then traverse up till the node is a right child of its parent,
		// then the predecessor is the ancestor of the current node
		if (n->ancestor.lock() != nullptr)
		{
			return predecessor_up(n);
		}

		// If both the above cases don't work then it's the least element
		return nullptr;
	}

	template <class T>
	std::shared_ptr<bin_tree::node<T>> bst<T>::find_min()
	{
	}

	template <class T>
	std::shared_ptr<bin_tree::node<T>> bst<T>::find_max()
	{
	}

	template <class T>
	std::shared_ptr<bin_tree::node<T>> bst<T>::insert(T& key)
	{
		if (this->root == nullptr)
		{
			this->root = std::make_shared<bin_tree::root_node<T>>(key);
			return this->root;
		}

		return insert(key, this->root);
	}

	template <class T>
	bool bst<T>::remove(T key)
	{
		return false;
	}

	template <class T>
	std::shared_ptr<bin_tree::node<T>> bst<T>::successor_up(std::shared_ptr<bin_tree::node<T>> n)
	{		
		auto &ancestor = n->ancestor.lock();
		if (ancestor == nullptr)
		{
			return nullptr;
		}

		if (n->get_node_type() == bin_tree::node_type::k_left_child)
		{
			return ancestor;
		}

		return successor_up(ancestor);
	}

	template <class T>
	std::shared_ptr<bin_tree::node<T>> bst<T>::successor_down(std::shared_ptr<bin_tree::node<T>> n)
	{
		if (n->left_child != nullptr)
		{
			return successor_down(n->left_child);
		}

		return n;
	}

	template <class T>
	std::shared_ptr<bin_tree::node<T>> bst<T>::predecessor_up(std::shared_ptr<bin_tree::node<T>> n)
	{
		auto &ancestor = n->ancestor.lock();
		if (ancestor == nullptr)
		{
			return nullptr;
		}

		if (n->get_node_type() == bin_tree::node_type::k_right_child)
		{
			return ancestor;
		}

		return predecessor_up(ancestor);
	}

	template <class T>
	std::shared_ptr<bin_tree::node<T>> bst<T>::predecessor_down(std::shared_ptr<bin_tree::node<T>> n)
	{
		if (n->right_child != nullptr)
		{
			return predecessor_down(n->right_child);
		}

		return n;
	}

	template <class T>
	std::shared_ptr<bin_tree::node<T>> bst<T>::insert(T& key, std::shared_ptr<bin_tree::node<T>> n)
	{
		if (key <= n->data)
		{
			if (n->left_child == nullptr)
			{
				n->left_child = std::make_shared<bin_tree::left_node<T>>(key);	
				n->left_child->ancestor = n;
				return n->left_child;
			}

			return insert(key, n->left_child);
		}

		if (n->right_child == nullptr)
		{
			n->right_child = std::make_shared<bin_tree::right_node<T>>(key);
			n->right_child->ancestor = n;
			return n->right_child;
		}

		return insert(key, n->right_child);
	}
}
