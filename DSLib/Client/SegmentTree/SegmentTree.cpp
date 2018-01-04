#include <iostream>
#include <vector>

#include "SegmentTree.h"

template<class T>
T merge_nodes(T d1, T d2)
{
	return d1 <= d2 ? d1 : d2;
}

template<class C, class T>
T access_data(const C& container, const std::size_t index)
{
	return container[index];
}

template<class T, class U>
T update_data(const ds::bin_tree::range& segment, const T& node_data, const U& data)
{
	return data;
}

int main(int argc, char* argv[])
{
	std::vector<int> data{ 18, 17, 13, 19, 15, 11, 20 };
	ds::bin_tree::seg_tree<std::vector<int>, int, int> seg_tree(data, data.size(), access_data, merge_nodes, update_data);

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
