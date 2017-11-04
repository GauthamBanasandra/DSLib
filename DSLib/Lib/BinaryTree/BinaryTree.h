#pragma once
#include "Node.h"

#include <functional>
#include <iostream>

template<class T>
class BinaryTree
{
	using big_int = unsigned long long;

public:
	explicit BinaryTree(bin_tree::Node<T> *root) :root(root), height(0), node_count(0) {}
	virtual ~BinaryTree() = default;

	void preorder(std::function<void(T &data)> visit_action = [](T &data)->void {std::cout << data << '\n'; });
	void postorder(std::function<void(T &data)> visit_action = [](T &data)->void {std::cout << data << '\n'; });
	void inorder(std::function<void(T &data)> visit_action = [](T &data)->void {std::cout << data << '\n'; });

	virtual bin_tree::Node<T> *insert(T key) = 0;
	virtual bool remove(T key) = 0;

private:
	void preorder(bin_tree::Node<T> *n, std::function<void(T &data)> &&visit_action);
	void postorder(bin_tree::Node<T> *n, std::function<void(T &data)> &&visit_action);
	void inorder(bin_tree::Node<T> *n, std::function<void(T &data)> &&visit_action);

public:
	bin_tree::Node<T> *root;
	big_int height;
	big_int node_count;
};

template <class T>
void BinaryTree<T>::preorder(std::function<void(T &data)> visit_action)
{
	preorder(root, std::move(visit_action));
}

template <class T>
void BinaryTree<T>::postorder(std::function<void(T &data)> visit_action)
{
	postorder(root, std::move(visit_action));
}

template <class T>
void BinaryTree<T>::inorder(std::function<void(T &data)> visit_action)
{
	inorder(root, std::move(visit_action));
}

template <class T>
void BinaryTree<T>::preorder(bin_tree::Node<T>* n, std::function<void(T& data)> &&visit_action)
{
	if (n == nullptr)
	{
		return;
	}

	visit_action(n->data);
	preorder(n->left_child, std::move(visit_action));
	preorder(n->right_child, std::move(visit_action));
}

template <class T>
void BinaryTree<T>::postorder(bin_tree::Node<T>* n, std::function<void(T& data)>&& visit_action)
{
	if (n == nullptr)
	{
		return;
	}

	postorder(n->left_child, std::move(visit_action));
	postorder(n->right_child, std::move(visit_action));
	visit_action(n->data);
}

template <class T>
void BinaryTree<T>::inorder(bin_tree::Node<T>* n, std::function<void(T& data)>&& visit_action)
{
	if (n == nullptr)
	{
		return;
	}

	inorder(n->left_child, std::move(visit_action));
	visit_action(n->data);
	inorder(n->right_child, std::move(visit_action));
}
