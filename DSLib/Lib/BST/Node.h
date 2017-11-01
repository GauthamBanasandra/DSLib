#pragma once
namespace tree
{
	template<typename T>
	class Node
	{
	public:
		Node(Node *ancestor, Node *left_child, Node *right_child, T data) :data(data), ancestor(ancestor), left_child(left_child), right_child(right_child) {}

		T data;
		Node *ancestor;
		Node *left_child;
		Node *right_child;
	};
}
