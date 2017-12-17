#include "AVL.h"
#include <vector>

int main(int argc, char* argv[])
{
	ds::bin_tree::avl<double> avl;
	std::vector<double> data{ 3, 2, 1, 4, 3.3, 5, 4.4, 6, 4.5 };
	for (auto &item : data)
	{
		avl.insert(item);
	}

	// Before insertion
	std::cout << "Preorder:" << std::endl;
	avl.preorder();
	std::cout << "\nInorder:" << std::endl;
	avl.inorder();

	avl.remove(5);

	// After insertion
	std::cout << "\nPreorder:" << std::endl;
	avl.preorder();
	std::cout << "\nInorder:" << std::endl;
	avl.inorder();

	return 0;
}
