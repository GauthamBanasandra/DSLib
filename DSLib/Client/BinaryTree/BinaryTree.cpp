#include "BinaryTree.h"
#include "BST.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	bin_tree::Node<int> root(0);
	bin_tree::Node<int> n1(&root, 1);
	bin_tree::Node<int> n2(&root, 2);
	bin_tree::Node<int> n3(&n1, 3);
	bin_tree::Node<int> n4(&n1, 4);
	bin_tree::Node<int> n5(&n2, 5);
	bin_tree::Node<int> n6(&n2, 6);
	
	root.left_child = &n1;
	root.right_child = &n2;
	n1.left_child = &n3;
	n1.right_child = &n4;
	n2.left_child = &n5;
	n2.right_child = &n6;

	Bst<int> bst(&root);
	std::vector<int> preorder;

	bst.preorder([&preorder](int data) {preorder.push_back(data); });

	std::cout << "Printing from calling scope" << std::endl;
	for (const auto  &item: preorder)
	{
		std::cout << item << '\t';
	}

	std::cout << std::endl;

	return 0;
}
