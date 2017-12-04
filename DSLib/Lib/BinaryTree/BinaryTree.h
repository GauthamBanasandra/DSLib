#pragma once
#include "Node.h"

#include <functional>
#include <iostream>
#include <algorithm>

namespace ds
{
	namespace bin_tree
	{
		template<class T>
		class binary_tree
		{
			using big_int = unsigned long long;

		public:
			explicit binary_tree() : node_count(0) {}
			virtual ~binary_tree() = default;

			// Traversal methods with visit_action as a lambda
			void preorder(std::function<void(std::shared_ptr<node<T>> n)> visit_action = [](std::shared_ptr<node<T>> n)->void {std::cout << n->data << '\n'; });
			void postorder(std::function<void(std::shared_ptr<node<T>> n)> visit_action = [](std::shared_ptr<node<T>> n)->void {std::cout << n->data << '\n'; });
			void inorder(std::function<void(std::shared_ptr<node<T>> n)> visit_action = [](std::shared_ptr<node<T>> n)->void {std::cout << n->data << '\n'; });

			// C++ doesn't allow a member to be used as the default value (for node as root)
			// Thus, we need expose traversal methods as wrappers of these functions
			void preorder(std::shared_ptr<node<T>> n, std::function<void(std::shared_ptr<node<T>>)> &&visit_action);
			void postorder(std::shared_ptr<node<T>> n, std::function<void(std::shared_ptr<node<T>>)> &&visit_action);
			void inorder(std::shared_ptr<node<T>> n, std::function<void(std::shared_ptr<node<T>>)> &&visit_action);
			long long height();
			static long long height(const std::shared_ptr<node<T>> &n);

			// Insert and remove methods are pure virtual (derived class must implement them)
			virtual std::shared_ptr<node<T>> insert(T& key) = 0;
			virtual bool remove(T key) = 0;

		protected:
			// A utility function to get the height of the node
			static long long get_height(std::shared_ptr<node<T>> n) { return n == nullptr ? 0 : n->height; }

		public:
			std::shared_ptr<node<T>> root;
			big_int node_count;
		};

		template <class T>
		void binary_tree<T>::preorder(std::function<void(std::shared_ptr<node<T>> n)> visit_action)
		{
			preorder(root, std::move(visit_action));
		}

		template <class T>
		void binary_tree<T>::postorder(std::function<void(std::shared_ptr<node<T>> n)> visit_action)
		{
			postorder(root, std::move(visit_action));
		}

		template <class T>
		void binary_tree<T>::inorder(std::function<void(std::shared_ptr<node<T>> n)> visit_action)
		{
			inorder(root, std::move(visit_action));
		}

		template <class T>
		void binary_tree<T>::preorder(std::shared_ptr<node<T>> n, std::function<void(std::shared_ptr<node<T>>)>&& visit_action)
		{
			if (n == nullptr)
			{
				return;
			}

			visit_action(n);
			preorder(n->left_child, std::move(visit_action));
			preorder(n->right_child, std::move(visit_action));
		}

		template <class T>
		void binary_tree<T>::postorder(std::shared_ptr<node<T>> n, std::function<void(std::shared_ptr<node<T>>)>&& visit_action)
		{
			if (n == nullptr)
			{
				return;
			}

			postorder(n->left_child, std::move(visit_action));
			postorder(n->right_child, std::move(visit_action));
			visit_action(n);
		}

		template <class T>
		void binary_tree<T>::inorder(std::shared_ptr<node<T>> n, std::function<void(std::shared_ptr<node<T>>)>&& visit_action)
		{
			if (n == nullptr)
			{
				return;
			}

			inorder(n->left_child, std::move(visit_action));
			visit_action(n);
			inorder(n->right_child, std::move(visit_action));
		}

		template <class T>
		long long binary_tree<T>::height()
		{
			return binary_tree<T>::height(this->root);
		}

		template <class T>
		long long binary_tree<T>::height(const std::shared_ptr<node<T>>& n)
		{
			if (n == nullptr)
			{
				return 0;
			}

			auto left_height = binary_tree<T>::height(n->left_child);
			auto right_height = binary_tree<T>::height(n->right_child);

			return std::max(left_height, right_height) + 1;
		}
	}
}
