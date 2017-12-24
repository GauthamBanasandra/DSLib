#include "SegmentTree.h"

int main(int argc, char* argv[])
{
	const std::vector<int> data{ 18, 17, 13, 19, 15, 11, 20 };
	ds::bin_tree::seg_tree<int> seg_tree(data);

	return 0;
}
