#include <iostream>
#include <vector>

#include "SegmentTree.h"

template<class T>
T merge_nodes(T d1, T d2)
{
	return d1 <= d2 ? d1 : d2;
}

template<class T>
T get_data(const void* container_cookie, std::size_t index)
{
	const auto container = static_cast<const std::vector<T>*>(container_cookie);
	return (*container)[index];
}

int main(int argc, char* argv[])
{
	std::vector<int> data{ 18, 17, 13, 19, 15, 11, 20 };
	ds::bin_tree::seg_tree<int> seg_tree(&data, data.size(), get_data<int>, merge_nodes<int>);

	const ds::bin_tree::range query_segment{ 0, 6 };
	auto min_node = seg_tree.query(query_segment);
	std::cout << "Min[" << query_segment.lower_bound << ", " << query_segment.upper_bound << "] = " << (!min_node.is_valid ? -1 : min_node.data) << std::endl;

	const auto value = 100;
	const ds::bin_tree::range update_segment{ 0, 6 };
	std::cout << "Update[" << update_segment.lower_bound << ", " << update_segment.upper_bound << "] = " << value << std::endl;
	seg_tree.update_range(update_segment, value);

	min_node = seg_tree.query(query_segment);
	std::cout << "Min[" << query_segment.lower_bound << ", " << query_segment.upper_bound << "] = " << (!min_node.is_valid ? -1 : min_node.data) << std::endl;
	return 0;
}
