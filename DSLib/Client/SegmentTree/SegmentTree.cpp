#include <iostream>

#include "SegmentTree.h"

template<class T>
ds::bin_tree::node<T>* compare(const std::vector<T>& data, ds::bin_tree::node<T>* n1, ds::bin_tree::node<T>* n2)
{
	return data[n1->data] <= data[n2->data] ? n1 : n2;
}

int main(int argc, char* argv[])
{
	const std::vector<int> data{ 18, 17, 13, 19, 15, 11, 20 };
	ds::bin_tree::seg_tree<int> seg_tree(data, compare);

	const ds::bin_tree::range query_segment{ 0, data.size()-1 };
	const auto min_node = seg_tree.query(query_segment);

	std::cout << "Min[" << query_segment.lower_bound << ", " << query_segment.upper_bound << "] = " << (min_node == nullptr ? -1 : data[min_node->data]) << std::endl;
	return 0;
}
