#include "AVL.h"
#include <vector>

int main(int argc, char* argv[])
{
	ds::avl<double> avl;
	std::vector<double> data{ 3, 2, 4, 5, 1 };
	for (auto &item: data)
	{
		avl.insert(item);
	}
	
	double i = 0;
	avl.insert(i);
	avl.inorder();
	return 0;
}
