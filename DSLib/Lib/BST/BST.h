#pragma once
#include "BinaryTree.h"

template<class T>
class Bst :public BinaryTree<T>
{
public:
	explicit Bst(bin_tree::Node<T>* root)
		: BinaryTree<T>(root)
	{
	}
	~Bst() {}

	bool search(T key);
	bin_tree::Node<T> *successor(T key);
	bin_tree::Node<T> *predecessor(T key);
	bin_tree::Node<T> *find_min();
	bin_tree::Node<T> *find_max();

	bin_tree::Node<T> * insert(T key) override;
	bool remove(T key) override;
};

template <class T>
bool Bst<T>::search(T key)
{
}

template <class T>
bin_tree::Node<T>* Bst<T>::successor(T key)
{
}

template <class T>
bin_tree::Node<T>* Bst<T>::predecessor(T key)
{
}

template <class T>
bin_tree::Node<T>* Bst<T>::find_min()
{
}

template <class T>
bin_tree::Node<T>* Bst<T>::find_max()
{
}

template <class T>
bin_tree::Node<T>* Bst<T>::insert(T key)
{
	return nullptr;
}

template <class T>
bool Bst<T>::remove(T key)
{
	return false;
}
