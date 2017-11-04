#pragma once
#include "Node.h"

template<class T>
class BinaryTree
{
	using big_int = unsigned long long;

public:
	explicit BinaryTree(bin_tree::Node<T> *root) :root(root), height(0), node_count(0) {}
	
	void preorder() const;
	void postorder() const;
	void inorder() const;

	bin_tree::Node<T> *root;
	big_int height;
	big_int node_count;
};

template <class T>
void BinaryTree<T>::preorder() const
{
}

template <class T>
void BinaryTree<T>::postorder() const
{
}

template <class T>
void BinaryTree<T>::inorder() const
{
}
