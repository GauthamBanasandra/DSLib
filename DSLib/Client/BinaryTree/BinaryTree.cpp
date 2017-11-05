#include "BinaryTree.h"
#include "BST.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	ds::bin_tree::Node<int> root(3);
	ds::bin_tree::Node<int> n1(&root, 1);
	ds::bin_tree::Node<int> n2(&root, 5);
	ds::bin_tree::Node<int> n3(&n1, 0);
	ds::bin_tree::Node<int> n4(&n1, 2);
	ds::bin_tree::Node<int> n5(&n2, 4);
	ds::bin_tree::Node<int> n6(&n2, 6);
	
	root.left_child = &n1;
	root.right_child = &n2;
	n1.left_child = &n3;
	n1.right_child = &n4;
	n2.left_child = &n5;
	n2.right_child = &n6;

	ds::Bst<int> bst(&root);
	std::vector<int> inorder;

	bst.inorder([&inorder](int data) {inorder.push_back(data); });

	std::cout << "Printing from calling scope" << std::endl;
	for (const auto  &item: inorder)
	{
		std::cout << item << '\t';
	}

	std::cout << std::endl;

	return 0;
}
