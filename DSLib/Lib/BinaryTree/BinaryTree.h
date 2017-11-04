#pragma once
#include "Node.h"

#include <iostream>

template<class T>
class BinaryTree
{
	using big_int = unsigned long long;

public:
	explicit BinaryTree(bin_tree::Node<T> *root) :root(root), height(0), node_count(0) {}
	virtual ~BinaryTree() = default;

	void preorder() const;
	void postorder() const;
	void inorder() const;

	virtual bin_tree::Node<T> *insert(T key) = 0;
	virtual bool remove(T key) = 0;

private:
	void preorder(bin_tree::Node<T> *n) const;

public:
	bin_tree::Node<T> *root;
	big_int height;
	big_int node_count;
};

template <class T>
void BinaryTree<T>::preorder() const
{
	preorder(root);
}

template <class T>
void BinaryTree<T>::postorder() const
{
}

template <class T>
void BinaryTree<T>::inorder() const
{
}

template <class T>
void BinaryTree<T>::preorder(bin_tree::Node<T>* n) const
{
	if (n == nullptr)
	{
		return;
	}

	std::cout << n->data << std::endl;
	preorder(n->left_child);
	preorder(n->right_child);
}
