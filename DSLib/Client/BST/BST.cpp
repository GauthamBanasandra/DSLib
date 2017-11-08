#include "BST.h"

#include <iostream>

int main(int argc, char* argv[])
{
	ds::bin_tree::node<int> root(3);
	ds::bin_tree::node<int> n1(&root, 1);
	ds::bin_tree::node<int> n2(&root, 5);
	ds::bin_tree::node<int> n3(&n1, 0);
	ds::bin_tree::node<int> n4(&n1, 2);
	ds::bin_tree::node<int> n5(&n2, 4);
	ds::bin_tree::node<int> n6(&n2, 6);

	root.left_child = &n1;
	root.right_child = &n2;
	n1.left_child = &n3;
	n1.right_child = &n4;
	n2.left_child = &n5;
	n2.right_child = &n6;

	ds::bst<int> bst(&root);

	// Search
	const auto find = bst.search(7);
	std::cout << "Search: " << (find ? "found" : "not found") << std::endl;

	// Successor
	const auto successor_node = bst.successor(4);
	if (successor_node != nullptr)
	{
		std::cout << "Successor: " << successor_node->data << std::endl;
	}
	else
	{
		std::cout << "No successor" << std::endl;
	}

	const auto predecessor_node = bst.predecessor(4);
	if (predecessor_node != nullptr)
	{
		std::cout << "Predecessor: " << predecessor_node->data << std::endl;
	}
	else
	{
		std::cout << "No predecessor" << std::endl;
	}

	return 0;
}
