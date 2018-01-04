#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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

template<class C, class T>
void extensive_query(const std::vector<T> &data, ds::bin_tree::seg_tree<C, T> &seg_tree, SegmentTreeGold &seg_tree_gold)
{
	ds::bin_tree::range query_segment;
	for (std::size_t i = 0; i < data.size(); ++i)
	{
		query_segment.lower_bound = i;
		for (auto j = i; j < data.size(); ++j)
		{
			query_segment.upper_bound = j;
			auto expected = data[seg_tree_gold.rmq(i, j)];
			auto actual = seg_tree.query(query_segment);

			/*std::string msg = "Min[" + std::to_string(i) + ", " + std::to_string(j) + "] = exp: " + std::to_string(expected) + "\tact: " + std::to_string(actual.data);
			Logger::WriteMessage(msg.c_str());*/
			Assert::IsTrue(actual.is_valid, L"Query must be valid");
			Assert::AreEqual(expected, actual.data);
		}
	}
}

template<class C, class T>
void extensive_update(std::vector<T> &data, ds::bin_tree::seg_tree<C, T> &seg_tree, SegmentTreeGold& seg_tree_gold, T new_value, const bool random)
{
	auto value = new_value;
	ds::bin_tree::range update_segment;
	for (std::size_t i = 0; i < data.size(); ++i)
	{
		if (random)
		{
			value = rand();
		}

		update_segment.lower_bound = update_segment.upper_bound = i;
		seg_tree.update_range(update_segment, value);
		seg_tree_gold.update_point(i, value);
		data[i] = value;
		extensive_query(data, seg_tree, seg_tree_gold);
	}
}

std::vector<int> generate_data(const std::size_t data_size)
{
	std::vector<int> data;
	const auto seed = static_cast<unsigned>(time(nullptr));

	// Log the seed
	auto msg = "Seed: " + std::to_string(seed);
	Logger::WriteMessage(msg.c_str());

	srand(seed);
	for (std::size_t i = 0; i < data_size; ++i)
	{
		data.push_back(rand());
	}

	return data;
}
namespace SegmentTree
{
	TEST_CLASS(seg_tree)
	{
	public:
		TEST_METHOD(query_test)
		{
			std::vector<int> data{ 18, 17, 13, 19, 15, 11, 20 };
			ds::bin_tree::seg_tree<std::vector<int>, int> seg_tree(data, data.size(), access_data, merge_nodes);
			SegmentTreeGold seg_tree_gold(data);

			extensive_query(data, seg_tree, seg_tree_gold);
		}

		TEST_METHOD(update_test)
		{
			std::vector<int> data{ 18, 17, 13, 19, 15, 11, 20 };
			ds::bin_tree::seg_tree<std::vector<int>, int> seg_tree(data, data.size(), access_data, merge_nodes);
			SegmentTreeGold seg_tree_gold(data);

			extensive_update(data, seg_tree, seg_tree_gold, 1, false);
		}
	};

	TEST_CLASS(random_data)
	{
	public:
		TEST_METHOD(random_query_test)
		{
			auto data = generate_data(1000);
			ds::bin_tree::seg_tree<std::vector<int>, int> seg_tree(data, data.size(), access_data, merge_nodes);
			SegmentTreeGold seg_tree_gold(data);

			extensive_query(data, seg_tree, seg_tree_gold);
		}

		TEST_METHOD(random_update_test)
		{
			auto data = generate_data(20);
			ds::bin_tree::seg_tree<std::vector<int>, int> seg_tree(data, data.size(), access_data, merge_nodes);
			SegmentTreeGold seg_tree_gold(data);

			extensive_update(data, seg_tree, seg_tree_gold, 0, true);
		}

		TEST_METHOD(full_update_test)
		{
			auto data = generate_data(101);
			ds::bin_tree::seg_tree<std::vector<int>, int> seg_tree(data, data.size(), access_data, merge_nodes);
			SegmentTreeGold seg_tree_gold(data);
			const ds::bin_tree::range update_segment{ 0, data.size() - 1 };

			auto value = 1;
			seg_tree.update_range(update_segment, value);
			for (auto i = update_segment.lower_bound; i <= update_segment.upper_bound; ++i)
			{
				seg_tree_gold.update_point(i, value);
				data[i] = value;
			}

			value = 100;
			seg_tree.update_range(update_segment, value);
			for (auto i = update_segment.lower_bound; i <= update_segment.upper_bound; ++i)
			{
				seg_tree_gold.update_point(i, value);
				data[i] = value;
			}

			extensive_query(data, seg_tree, seg_tree_gold);
		}
	};

	TEST_CLASS(benchmark)
	{
	public:
		TEST_METHOD(benchmark_query)
		{
			const auto data = generate_data(1000000);
			//SegmentTreeGold seg_tree_gold(data);
			ds::bin_tree::seg_tree<std::vector<int>, std::size_t> seg_tree(data, data.size(), access_data, merge_nodes);
		}

		TEST_METHOD(benchmark_update)
		{
			const auto data_size = 1000000;
			const auto data = generate_data(data_size);

			/*SegmentTreeGold seg_tree_gold(data);
			seg_tree_gold.update_point(data_size >> 1, 10);*/

			ds::bin_tree::seg_tree<std::vector<int>, std::size_t> seg_tree(data, data.size(), access_data, merge_nodes);
			const ds::bin_tree::range segment{ data_size >> 1, (data_size >> 1) + 1 };
			seg_tree.update_range(segment, 10);
		}
	};
}