#pragma once
#include "Node.h"

#include <functional>
#include <iostream>

namespace ds
{
	template<class T>
	class binary_tree
	{
		using big_int = unsigned long long;

	public:
		explicit binary_tree() : height(0), node_count(0) {}
		virtual ~binary_tree() = default;

		// Traversal methods with visit_action as a lambda
		void preorder(std::function<void(T &data)> visit_action = [](T &data)->void {std::cout << data << '\n'; });
		void postorder(std::function<void(T &data)> visit_action = [](T &data)->void {std::cout << data << '\n'; });
		void inorder(std::function<void(T &data)> visit_action = [](T &data)->void {std::cout << data << '\n'; });

		// C++ doesn't allow a member to be used as the default value (for node as root)
		// Thus, we need expose traversal methods as wrappers of these functions
		void preorder(bin_tree::node<T> *n, std::function<void(T &data)> &&visit_action);
		void postorder(bin_tree::node<T> *n, std::function<void(T &data)> &&visit_action);
		void inorder(bin_tree::node<T> *n, std::function<void(T &data)> &&visit_action);

		// Insert and remove methods are pure virtual (derived class must implement them)
		virtual std::shared_ptr<bin_tree::node<T>> insert(T& key) = 0;
		virtual bool remove(T key) = 0;

		std::shared_ptr<bin_tree::node<T>> root;
		big_int height;
		big_int node_count;
	};

	template <class T>
	void binary_tree<T>::preorder(std::function<void(T &data)> visit_action)
	{
		preorder(root.get(), std::move(visit_action));
	}

	template <class T>
	void binary_tree<T>::postorder(std::function<void(T &data)> visit_action)
	{
		postorder(root.get(), std::move(visit_action));
	}

	template <class T>
	void binary_tree<T>::inorder(std::function<void(T &data)> visit_action)
	{
		inorder(root.get(), std::move(visit_action));
	}

	template <class T>
	void binary_tree<T>::preorder(bin_tree::node<T>* n, std::function<void(T& data)> &&visit_action)
	{
		if (n == nullptr)
		{
			return;
		}

		visit_action(n->data);
		preorder(n->left_child.get(), std::move(visit_action));
		preorder(n->right_child.get(), std::move(visit_action));
	}

	template <class T>
	void binary_tree<T>::postorder(bin_tree::node<T>* n, std::function<void(T& data)>&& visit_action)
	{
		if (n == nullptr)
		{
			return;
		}

		postorder(n->left_child.get(), std::move(visit_action));
		postorder(n->right_child.get(), std::move(visit_action));
		visit_action(n->data);
	}

	template <class T>
	void binary_tree<T>::inorder(bin_tree::node<T>* n, std::function<void(T& data)>&& visit_action)
	{
		if (n == nullptr)
		{
			return;
		}

		inorder(n->left_child.get(), std::move(visit_action));
		visit_action(n->data);
		inorder(n->right_child.get(), std::move(visit_action));
	}
}
