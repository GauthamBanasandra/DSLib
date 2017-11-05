#pragma once
namespace ds
{
	namespace bin_tree
	{
		template<typename T>
		class node
		{
		public:
			explicit node(T data) :data(data), ancestor(nullptr), left_child(nullptr), right_child(nullptr) {}
			node(node *ancestor, T data) :data(data), ancestor(ancestor), left_child(nullptr), right_child(nullptr) {}
			node(node *ancestor, node *left_child, node *right_child, T data) :data(data), ancestor(ancestor), left_child(left_child), right_child(right_child) {}

			T data;
			node *ancestor;
			node *left_child;
			node *right_child;
		};
	}
}
