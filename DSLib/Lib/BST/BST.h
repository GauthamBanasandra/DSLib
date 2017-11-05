#pragma once
#include "BinaryTree.h"

namespace ds
{
	template<class T>
	class bst :public binary_tree<T>
	{
	public:
		explicit bst(bin_tree::node<T>* root)
			: binary_tree<T>(root)
		{
		}
		~bst() {}

		bool search(const T &key) const;
		bin_tree::node<T> *search(const T &key, bin_tree::node<T> *n) const;

		bin_tree::node<T> *successor(T key);
		bin_tree::node<T> *predecessor(T key);
		bin_tree::node<T> *find_min();
		bin_tree::node<T> *find_max();

		bin_tree::node<T> * insert(T key) override;
		bool remove(T key) override;
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
	bin_tree::node<T>* bst<T>::search(const T& key, bin_tree::node<T>* n) const
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
	bin_tree::node<T>* bst<T>::successor(T key)
	{
	}

	template <class T>
	bin_tree::node<T>* bst<T>::predecessor(T key)
	{
	}

	template <class T>
	bin_tree::node<T>* bst<T>::find_min()
	{
	}

	template <class T>
	bin_tree::node<T>* bst<T>::find_max()
	{
	}

	template <class T>
	bin_tree::node<T>* bst<T>::insert(T key)
	{
		return nullptr;
	}

	template <class T>
	bool bst<T>::remove(T key)
	{
		return false;
	}
}
