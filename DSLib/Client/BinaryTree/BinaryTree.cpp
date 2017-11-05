#include "BST.h"

#include <iostream>
#include <vector>

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
	std::vector<int> inorder;

	// Inorder - specifying a custom visit action
	bst.inorder([&inorder](int data) {inorder.push_back(data); });
	std::cout << "Inorder:" << std::endl;
	for (const auto  &item: inorder)
	{
		std::cout << item << std::endl;
	}

	// Preorder
	std::cout << "\nPreorder:" << std::endl;
	bst.preorder();

	// Postorder
	std::cout << "\nPostorder:" << std::endl;
	bst.postorder();

	return 0;
}
