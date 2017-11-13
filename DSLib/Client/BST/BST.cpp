#include "BST.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	ds::bst<int> bst;
	std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
	for (auto item : data)
	{
		bst.insert(item);
	}

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

	// Predecessor
	const auto predecessor_node = bst.predecessor(4);
	if (predecessor_node != nullptr)
	{
		std::cout << "Predecessor: " << predecessor_node->data << std::endl;
	}
	else
	{
		std::cout << "No predecessor" << std::endl;
	}

	std::cout << "Dynamic BST:" << std::endl;
	std::vector<int> numbers{ 7, 3, 1, 2, 5, 6, 4, 0 };
	ds::bst<int> bst_dyn;
	for (auto& number : numbers)
	{
		bst_dyn.insert(number);
	}

	bst_dyn.inorder();
	return 0;
}
