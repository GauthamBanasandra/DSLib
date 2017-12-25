#include <iostream>
#include <vector>

#include "SegmentTree.h"

template<class T>
ds::bin_tree::node<std::size_t>* merge_nodes(void* container_cookie, ds::bin_tree::node<std::size_t>* n1, ds::bin_tree::node<std::size_t>* n2)
{
	auto container = static_cast<std::vector<T>*>(container_cookie);
	return (*container)[n1->data] <= (*container)[n2->data] ? n1 : n2;
}

int main(int argc, char* argv[])
{
	std::vector<int> data{ 18, 17, 13, 19, 15, 11, 20 };
	ds::bin_tree::seg_tree seg_tree(&data, data.size(), merge_nodes<int>);

	const ds::bin_tree::range query_segment{ 0, data.size() - 1 };
	const auto min_node = seg_tree.query(query_segment);

	std::cout << "Min[" << query_segment.lower_bound << ", " << query_segment.upper_bound << "] = " << (min_node == nullptr ? -1 : data[min_node->data]) << std::endl;
	return 0;
}
