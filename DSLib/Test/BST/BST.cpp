#include "stdafx.h"
#include "CppUnitTest.h"
#include <algorithm>
#include <queue>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BST
{
	template<class T>
	void do_lineage_test(ds::bin_tree::bst<T> bst)
	{
		bst.inorder([](std::shared_ptr<ds::bin_tree::node<T>>n)
		{
			const auto &ancestor = n->ancestor.lock();
			switch (n->node_type)
			{
			case ds::bin_tree::node_type::k_left_child:
				Assert::AreEqual(n->data, ancestor->left_child->data);
				break;

			case ds::bin_tree::node_type::k_right_child:
				Assert::AreEqual(n->data, ancestor->right_child->data);
				break;

			case ds::bin_tree::node_type::k_root:
				break;

			default:
				// Not handled for this node_type
				assert(false);
			}

			const auto &left_child = n->left_child;
			if (left_child != nullptr)
			{
				Assert::AreEqual(n->data, left_child->ancestor.lock()->data);
			}

			const auto &right_child = n->right_child;
			if (right_child != nullptr)
			{
				Assert::AreEqual(n->data, right_child->ancestor.lock()->data);
			}
		});
	}

	template<class T>
	void do_remove_test(ds::bin_tree::bst<T> bst, T key, std::vector<T> data)
	{
		bst.remove(key);

		std::vector<T> inorder;
		bst.inorder([&inorder](std::shared_ptr<ds::bin_tree::node<T>> n) {inorder.push_back(n->data); });

		std::vector<T> expected(data.begin(), data.end());
		expected.erase(remove(expected.begin(), expected.end(), key), expected.end());
		sort(expected.begin(), expected.end());

		Assert::AreEqual(expected.size(), inorder.size());

		for (decltype(inorder.size()) i = 0; i < inorder.size(); ++i)
		{
			auto msg = "Expected: " + std::to_string(expected[i]) + "\tActual: " + std::to_string(inorder[i]) + "\n";
			Logger::WriteMessage(msg.c_str());
			Assert::AreEqual(expected[i], inorder[i]);
		}
	}

	TEST_CLASS(bst)
	{
	public:
		TEST_METHOD(search_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
			ds::bin_tree::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			Assert::AreEqual(true, bst.search(0));
			Assert::AreEqual(true, bst.search(6));
			Assert::AreEqual(false, bst.search(-6));
			Assert::AreEqual(false, bst.search(7));
		}

		TEST_METHOD(successor_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
			ds::bin_tree::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			for (auto i = 0; i < data.size() - 1; ++i)
			{
				const auto successor_node = bst.successor(i);
				Assert::AreEqual(i + 1, successor_node->data);
			}

			if (bst.successor(data[data.size() - 1]) != nullptr)
			{
				Assert::Fail(L"Successor of the greatest element exists");
			}
		}

		TEST_METHOD(predecessor_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
			ds::bin_tree::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			for (int i = data.size() - 1; i > 0; --i)
			{
				const auto predecessor_node = bst.predecessor(i);
				Assert::AreEqual(i - 1, predecessor_node->data);
			}

			if (bst.predecessor(data[data.size() >> 1]) != nullptr)
			{
				Assert::Fail(L"Predecessor of the least element exists");
			}
		}

		TEST_METHOD(lineage_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
			ds::bin_tree::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
				do_lineage_test(bst);
			}
		}
	};

	TEST_CLASS(bst_node_removal)
	{
		TEST_METHOD(lineage_test_remove_node)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			for (auto item : data)
			{
				do_lineage_test(bst);
				bst.remove(item);
			}
		}

		TEST_METHOD(remove_left_leaf_node_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const auto key = 4;
			do_remove_test(bst, key, data);
			do_lineage_test(bst);
		}

		TEST_METHOD(remove_node_with_2_children_test)
		{
			std::vector<float> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::bst<float> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const float key = 5;
			do_remove_test(bst, key, data);
			do_lineage_test(bst);
		}

		TEST_METHOD(remove_internal_node_with_successor_as_leaf_test)
		{
			std::vector<float> data{ 3, 1, 5, 0, 2, 4, 6, 5.5 };

			ds::bin_tree::bst<float> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const float key = 5;
			do_remove_test(bst, key, data);
			do_lineage_test(bst);
		}

		TEST_METHOD(remove_internal_node_with_immediate_successor_test)
		{
			std::vector<float> data{ 3, 1, 5, 0, 2, 4, 6, 7 };

			ds::bin_tree::bst<float> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const float key = 5;
			do_remove_test(bst, key, data);
			do_lineage_test(bst);
		}

		TEST_METHOD(remove_internal_node_with_successor_having_subtree_test)
		{
			std::vector<double> data{ 3, 1, 5, 0, 2, 4, 6, 5.5, 5.9 };

			ds::bin_tree::bst<double> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const double key = 5;
			do_remove_test(bst, key, data);
			do_lineage_test(bst);
		}

		TEST_METHOD(remove_right_leaf_node_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const auto key = 6;
			do_remove_test(bst, key, data);
			do_lineage_test(bst);
		}

		TEST_METHOD(remove_root_node_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const auto key = 3;
			// TODO : This test fails when 262 - 277 is commented out
			bst.remove(key);

			std::vector<int> inorder;
			bst.inorder([&inorder](std::shared_ptr<ds::bin_tree::node<int>> n) {inorder.push_back(n->data); });

			std::vector<int> expected(data.begin(), data.end());
			expected.erase(remove(expected.begin(), expected.end(), key), expected.end());
			sort(expected.begin(), expected.end());

			Assert::AreEqual(expected.size(), inorder.size());

			for (decltype(inorder.size()) i = 0; i < inorder.size(); ++i)
			{
				Assert::AreEqual(expected[i], inorder[i]);
			}

			do_remove_test(bst, key, data);
			do_lineage_test(bst);
		}
	};

	TEST_CLASS(sequence)
	{
		TEST_METHOD(remove_sequence_test)
		{
			std::vector<int> data_queue{ 3, 1, 5, 0, 2, 4, 6 };
			for (auto j = 0; j < data_queue.size(); ++j)
			{
				std::vector<int> data(data_queue.begin() + j, data_queue.end());
				ds::bin_tree::bst<int> bst;
				for (auto item : data)
				{
					bst.insert(item);
				}

				const auto key = data_queue[j];
				do_remove_test(bst, key, data);
			}
		}

		TEST_METHOD(find_min_sequence_test)
		{
			std::vector<int> data_queue{ 3, 1, 5, 0, 2, 4, 6 };
			for (auto j = 0; j < data_queue.size(); ++j)
			{
				std::vector<int> data(data_queue.begin() + j, data_queue.end());
				ds::bin_tree::bst<int> bst;
				for (auto item : data)
				{
					bst.insert(item);
				}

				Assert::AreEqual(*min_element(data.begin(), data.end()), bst.find_min()->data);
			}
		}

		TEST_METHOD(find_max_sequence_test)
		{
			std::vector<int> data_queue{ 3, 1, 5, 0, 2, 4, 6 };
			for (auto j = 0; j < data_queue.size(); ++j)
			{
				std::vector<int> data(data_queue.begin() + j, data_queue.end());
				ds::bin_tree::bst<int> bst;
				for (auto item : data)
				{
					bst.insert(item);
				}

				Assert::AreEqual(*max_element(data.begin(), data.end()), bst.find_max()->data);
			}
		}

		TEST_METHOD(search_sequence_test)
		{
			std::vector<int> data_queue{ 3, 1, 5, 0, 2, 4, 6 };
			for (auto j = 0; j < data_queue.size(); ++j)
			{
				std::vector<int> data(data_queue.begin() + j, data_queue.end());
				ds::bin_tree::bst<int> bst;
				for (auto item : data)
				{
					bst.insert(item);
				}

				for (const auto& item : data)
				{
					Assert::AreEqual(true, bst.search(item));
				}
			}
		}
	};

}