#pragma once
namespace ds
{
	namespace bin_tree
	{
		template<typename T>
		class Node
		{
		public:
			explicit Node(T data) :data(data), ancestor(nullptr), left_child(nullptr), right_child(nullptr) {}
			Node(Node *ancestor, T data) :data(data), ancestor(ancestor), left_child(nullptr), right_child(nullptr) {}
			Node(Node *ancestor, Node *left_child, Node *right_child, T data) :data(data), ancestor(ancestor), left_child(left_child), right_child(right_child) {}

			T data;
			Node *ancestor;
			Node *left_child;
			Node *right_child;
		};
	}
}
