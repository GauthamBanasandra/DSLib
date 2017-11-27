#include "AVL.h"
#include <vector>

int main(int argc, char* argv[])
{
	ds::avl<double> avl;
	std::vector<double> data{ 3, 2, 4, 5, 1, 6 };
	for (auto &item : data)
	{
		avl.insert(item);
	}

	double i = 4.4;
	const auto insert = avl.insert(i);
	std::cout << "Preorder:" << std::endl;
	avl.preorder();
	std::cout << "\nInorder:" << std::endl;
	avl.inorder();
	ds::imbalance_info<double> info;
	if (avl.find_imbalance(insert, &info))
	{
		std::cout << "\nImbalance:" << std::endl;
		std::cout << "z: " << info.z->data << std::endl;
		std::cout << "y: " << info.y->data << std::endl;
		std::cout << "x: " << info.x->data << std::endl;
		std::cout << "Imbalance config: ";
		switch (info.config) {
		case ds::imbalance_config::k_ll:
			std::cout << "ll";
			break;
		case ds::imbalance_config::k_lr:
			std::cout << "lr";
			break;
		case ds::imbalance_config::k_rl:
			std::cout << "rl";
			break;
		case ds::imbalance_config::k_rr:
			std::cout << "rr";
			break;
		}

		std::cout << "\nRight rotation" << std::endl;
		avl.right_rotate(info.y);
		std::cout << "\nLeft rotation" << std::endl;
		avl.left_rotate(info.z);
		std::cout << "\nPreorder:" << std::endl;
		avl.preorder();
		std::cout << "\nInorder:" << std::endl;
		avl.inorder();
	}

	return 0;
}
