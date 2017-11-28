#include "BST.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	ds::bin_tree::bst<int> bst;
	std::vector<int> data{ 3, 1, 2, 4, 5, 0, 6 };
	for (auto item : data)
	{
		bst.insert(item);
	}

	std::vector<int> inorder;

	// Inorder - specifying a custom visit action
	bst.inorder([&inorder](std::shared_ptr<ds::bin_tree::node<int>> n) {inorder.push_back(n->data); });
	std::cout << "Inorder:" << std::endl;
	for (const auto &item : inorder)
	{
		std::cout << item << std::endl;
	}

	// Preorder
	std::cout << "\nPreorder:" << std::endl;
	bst.preorder();

	// Postorder
	std::cout << "\nPostorder:" << std::endl;
	bst.postorder();

	// Height of the tree
	std::cout << "\nHeight: " << bst.height() << std::endl;
	return 0;
}
