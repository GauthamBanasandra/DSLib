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
			explicit binary_tree() : root(nullptr), node_count(0) {}
			virtual ~binary_tree() = default;

			// Traversal methods with visit_action as a lambda
			void preorder(std::function<void(node<T> * n)> visit_action = [](node<T> * n)->void {std::cout << n->data << '\n'; });
			void postorder(std::function<void(node<T> * n)> visit_action = [](node<T> * n)->void {std::cout << n->data << '\n'; });
			void inorder(std::function<void(node<T> * n)> visit_action = [](node<T> * n)->void {std::cout << n->data << '\n'; });

			// C++ doesn't allow a member to be used as the default value (for node as root)
			// Thus, we need expose traversal methods as wrappers of these functions
			void preorder(node<T> * n, std::function<void(node<T> *)> &&visit_action);
			void postorder(node<T> * n, std::function<void(node<T> *)> &&visit_action);
			void inorder(node<T> * n, std::function<void(node<T> *)> &&visit_action);
			long long height();
			static long long height(const node<T> *n);

			// Insert and remove methods are pure virtual (derived class must implement them)
			virtual node<T> * insert(T& key) = 0;
			virtual bool remove(T key) = 0;

		protected:
			// A utility function to get the height of the node
			static long long get_height(node<T> *n) { return n == nullptr ? 0 : n->height; }
			void replace(node<T> * current, node<T> * other);

		public:
			node<T> * root;
			big_int node_count;
		};

		template <class T>
		void binary_tree<T>::preorder(std::function<void(node<T> * n)> visit_action)
		{
			preorder(root, std::move(visit_action));
		}

		template <class T>
		void binary_tree<T>::postorder(std::function<void(node<T> * n)> visit_action)
		{
			postorder(root, std::move(visit_action));
		}

		template <class T>
		void binary_tree<T>::inorder(std::function<void(node<T> * n)> visit_action)
		{
			inorder(root, std::move(visit_action));
		}

		template <class T>
		void binary_tree<T>::preorder(node<T> * n, std::function<void(node<T> *)>&& visit_action)
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
		void binary_tree<T>::postorder(node<T> * n, std::function<void(node<T> *)>&& visit_action)
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
		void binary_tree<T>::inorder(node<T> * n, std::function<void(node<T> *)>&& visit_action)
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
		long long binary_tree<T>::height(const node<T> * n)
		{
			if (n == nullptr)
			{
				return 0;
			}

			auto left_height = binary_tree<T>::height(n->left_child);
			auto right_height = binary_tree<T>::height(n->right_child);

			return std::max(left_height, right_height) + 1;
		}

		// Replaces 'current' node with 'other'
		// This doesn't handle childrens' links which is the responsibility of the caller
		template <typename T>
		void binary_tree<T>::replace(node<T> * current, node<T> * other)
		{
			auto ancestor = current->ancestor;
			switch (current->node_type)
			{
			case node_type::k_right_child:
				ancestor->right_child = other;
				break;

			case node_type::k_left_child:
				ancestor->left_child = other;
				break;

			case node_type::k_root:
				root = other;
				break;

			default: 
				assert(false, L"Not handled for this node_type");
			}

			other->ancestor = ancestor;
			other->node_type = current->node_type;

			delete current;
		}
	}
}
