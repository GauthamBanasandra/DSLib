#include "AVL.h"
#include <vector>

int main(int argc, char* argv[])
{
	ds::bin_tree::avl<double> avl;
	std::vector<double> data{ 3.3, 2, 4.4, 1, 3, 4, 5, 4.3 };
	for (auto &item : data)
	{
		avl.insert(item);
	}

	// Before insertion
	std::cout << "Preorder:" << std::endl;
	avl.preorder();
	std::cout << "\nInorder:" << std::endl;
	avl.inorder();

	avl.remove(3.3);

	// After insertion
	std::cout << "\nPreorder:" << std::endl;
	avl.preorder();
	std::cout << "\nInorder:" << std::endl;
	avl.inorder();

	return 0;
}
