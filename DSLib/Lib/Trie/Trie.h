#pragma once
#include <vector>
#include <string>

namespace ds
{
	namespace trie
	{
		struct node
		{
			node();

			std::vector<node*> next;
			int value{ 0 };
			static const size_t range = 26;
		};

		class tree
		{
		public:
			void put(const std::string& key, int value);
			int get(const std::string& key) const;

		private:
			node* put(node* node, const std::string& key, int value, size_t depth) const;
			node* get(node* node, const std::string& key, size_t depth) const;

			node* root_{ new node };
		};

		inline node::node()
		{
			next.resize(range, nullptr);
		}

		inline void tree::put(const std::string& key, const int value)
		{
			root_ = put(root_, key, value, 0);
		}

		inline int tree::get(const std::string& key) const
		{
			const auto node = get(root_, key, 0);
			if (node == nullptr)
			{
				return -1;
			}
			return node->value;
		}

		inline node* tree::put(node* node, const std::string& key, const int value, const size_t depth) const
		{
			if (node == nullptr)
			{
				node = new trie::node;
			}
			if (depth == key.length())
			{
				node->value = value;
				return node;
			}
			const auto c = key[depth] - 'a';
			node->next[c] = put(node->next[c], key, value, depth + 1);
			return node;
		}

		inline node* tree::get(node* node, const std::string& key, const size_t depth) const
		{
			if (node == nullptr)
			{
				return nullptr;
			}
			if (depth == key.length())
			{
				return node;
			}
			const auto c = key[depth] - 'a';
			return get(node->next[c], key, depth + 1);
		}
	}
}
