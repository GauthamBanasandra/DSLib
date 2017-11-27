#include "AVL.h"
#include <vector>

int main(int argc, char* argv[])
{
	ds::bin_tree::avl<double> avl;
	std::vector<double> data{ 3, 2, 4, 5, 1, 6 };
	for (auto &item : data)
	{
		avl.insert(item);
	}

	// Before insertion
	std::cout << "Preorder:" << std::endl;
	avl.preorder();
	std::cout << "\nInorder:" << std::endl;
	avl.inorder();

	double i = 4.4;
	const auto insert = avl.insert(i);

	// After insertion
	std::cout << "\nPreorder:" << std::endl;
	avl.preorder();
	std::cout << "\nInorder:" << std::endl;
	avl.inorder();

	return 0;
}
