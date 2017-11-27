#pragma once
#include "BinaryTree.h"
#include <cassert>

namespace ds
{
	namespace bin_tree
	{
		template<class T>
		class bst :public binary_tree<T>
		{
		public:
			// TODO : This is redundant
			bst() :binary_tree<T>() {}
			~bst() {}

			bool search(const T &key) const;
			std::shared_ptr<node<T>> search(const T &key, std::shared_ptr<node<T>> n) const;

			std::shared_ptr<node<T>> successor(const T &key);
			std::shared_ptr<node<T>> predecessor(const T &key);
			std::shared_ptr<node<T>> find_min();
			std::shared_ptr<node<T>> find_max();

			std::shared_ptr<node<T>> insert(T& key) override;
			bool remove(T key) override;

		private: // TODO : shared_ptr could be move rather than copied
			std::shared_ptr<node<T>> successor_up(std::shared_ptr<node<T>> n);
			std::shared_ptr<node<T>> leftmost_child(std::shared_ptr<node<T>> n);
			std::shared_ptr<node<T>> predecessor_up(std::shared_ptr<node<T>> n);
			std::shared_ptr<node<T>> rightmost_child(std::shared_ptr<node<T>> n);
			std::shared_ptr<node<T>> insert(T &key, std::shared_ptr<node<T>> n);
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
		std::shared_ptr<node<T>> bst<T>::search(const T& key, std::shared_ptr<node<T>> n) const
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
		std::shared_ptr<node<T>>  bst<T>::successor(const T& key)
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
				return leftmost_child(n->right_child);
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
		std::shared_ptr<node<T>> bst<T>::predecessor(const T& key)
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
				return rightmost_child(n->left_child);
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

		// The least element in a bst is the leftmost element of the tree
		template <class T>
		std::shared_ptr<node<T>> bst<T>::find_min()
		{
			if (this->root == nullptr)
			{
				return nullptr;
			}

			return leftmost_child(this->root);
		}

		// The greatest element in a bst is the rightmost element of the tree
		template <class T>
		std::shared_ptr<node<T>> bst<T>::find_max()
		{
			if (this->root == nullptr)
			{
				return nullptr;
			}

			return rightmost_child(this->root);
		}

		template <class T>
		std::shared_ptr<node<T>> bst<T>::insert(T& key)
		{
			if (this->root == nullptr)
			{
				this->root = std::make_shared<node<T>>(key, node_type::k_root);
				return this->root;
			}

			return insert(key, this->root);
		}

		template <class T>
		bool bst<T>::remove(T key)
		{
			auto n = search(key, this->root);
			if (n == nullptr)
			{
				return false;
			}

			if (n->is_leaf())
			{
				// If n is the root node, then reset the root pointer
				if (n == this->root)
				{
					this->root = nullptr;
				}

				node<T>::remove(n);
			}
			else if (n->left_child != nullptr && n->right_child == nullptr)
			{
				// Node to remove has only a left child,
				// replace the node to be removed with its left child 
				n->replace(this->root, n->left_child);
			}
			else if (n->left_child == nullptr && n->right_child != nullptr)
			{
				// Node to remove has only a right child,
				// replace the node to be removed with its right child 
				n->replace(this->root, n->right_child);
			}
			else
			{
				// Node to remove has both the children,
				// so find the successor of the node to remove
				auto successor = leftmost_child(n->right_child);

				// Successor renounces its lineage
				auto successor_ancestor = successor->ancestor.lock();
				switch (successor->node_type)
				{
				case node_type::k_left_child:
					successor_ancestor->left_child = nullptr;
					break;

				case node_type::k_right_child:
					successor_ancestor->right_child = nullptr;
					break;

				case node_type::k_root:
					// Root node can't be a successor node
					assert(false);
					break;

				default:
					// Not handled for this node_type
					assert(false);
				}

				if (successor->is_leaf())
				{
					// Successor adopt n's children
					if (n->left_child != nullptr)
					{
						n->left_child->ancestor = successor;
						successor->left_child = n->left_child;
					}

					// The second check is important as it avoids self-loops
					if ((n->right_child != nullptr) && (n->right_child != successor))
					{
						n->right_child->ancestor = successor;
						successor->right_child = n->right_child;
					}

					n->replace(this->root, successor);
				}
				else if (successor->node_type == node_type::k_right_child)
				{
					// Successor is an internal node and is also the right child of its ancestor
					// This happens only if the successor is an immediate successor of the node to be removed
					assert(successor->left_child == nullptr);

					// Adopt n's left child if it exists
					if (n->left_child != nullptr)
					{
						n->left_child->ancestor = successor;
						successor->left_child = n->left_child;
					}

					n->replace(this->root, successor);
				}
				else
				{
					// Successor is an internal node and is the left child of its ancestor
					// Such a successor will not have a left child, if it has one, it'll be a leaf node
					assert(successor->left_child == nullptr);

					// Temporary pointer to successor's right child
					auto right_child = successor->right_child;

					// Copy the data from successor to the node to be removed and replace the successor
					// with its right child
					successor->copy_data_to(n);
					successor->right_child = nullptr;
					successor->replace(this->root, right_child);
				}
			}

			return true;
		}

		template <class T>
		std::shared_ptr<node<T>> bst<T>::successor_up(std::shared_ptr<node<T>> n)
		{
			auto &ancestor = n->ancestor.lock();
			if (ancestor == nullptr)
			{
				return nullptr;
			}

			if (n->node_type == node_type::k_left_child)
			{
				return ancestor;
			}

			return successor_up(ancestor);
		}

		template <class T>
		std::shared_ptr<node<T>> bst<T>::leftmost_child(std::shared_ptr<node<T>> n)
		{
			if (n->left_child != nullptr)
			{
				return leftmost_child(n->left_child);
			}

			return n;
		}

		template <class T>
		std::shared_ptr<node<T>> bst<T>::predecessor_up(std::shared_ptr<node<T>> n)
		{
			auto &ancestor = n->ancestor.lock();
			if (ancestor == nullptr)
			{
				return nullptr;
			}

			if (n->node_type == node_type::k_right_child)
			{
				return ancestor;
			}

			return predecessor_up(ancestor);
		}

		template <class T>
		std::shared_ptr<node<T>> bst<T>::rightmost_child(std::shared_ptr<node<T>> n)
		{
			if (n->right_child != nullptr)
			{
				return rightmost_child(n->right_child);
			}

			return n;
		}

		template <class T>
		std::shared_ptr<node<T>> bst<T>::insert(T& key, std::shared_ptr<node<T>> n)
		{
			if (key <= n->data)
			{
				if (n->left_child == nullptr)
				{
					n->left_child = std::make_shared<node<T>>(key, node_type::k_left_child);
					n->left_child->ancestor = n;
					return n->left_child;
				}

				return insert(key, n->left_child);
			}

			if (n->right_child == nullptr)
			{
				n->right_child = std::make_shared<node<T>>(key, node_type::k_right_child);
				n->right_child->ancestor = n;
				return n->right_child;
			}

			return insert(key, n->right_child);
		}
	}
}
