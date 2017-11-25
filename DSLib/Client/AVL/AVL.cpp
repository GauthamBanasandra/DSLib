#include "AVL.h"
#include <vector>

int main(int argc, char* argv[])
{
	ds::avl<double> avl;
	std::vector<double> data{ 3, 2, 4, 5, 1 };
	for (auto &item : data)
	{
		avl.insert(item);
	}

	double i = 4.7;
	const auto insert = avl.insert(i);
	avl.inorder();
	/*ds::imbalance_info<double> info;
	if (avl.find_imbalance(insert, &info))
	{
		std::cout << "Imbalance:" << std::endl;
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

		std::cout << std::endl;
	}*/

	return 0;
}
