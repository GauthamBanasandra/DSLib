#include "stdafx.h"
#include "CppUnitTest.h"
#include <algorithm>
#include <queue>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BST
{
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
	};

	TEST_CLASS(bst_node_removal)
	{
		TEST_METHOD(remove_left_leaf_node_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const auto key = 4;
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
		}

		TEST_METHOD(remove_node_with_2_children_test)
		{
			std::vector<float> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::bst<float> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const long key = 5;
			bst.remove(key);

			std::vector<float> inorder;
			bst.inorder([&inorder](std::shared_ptr<ds::bin_tree::node<float>> n) {inorder.push_back(n->data); });

			std::vector<float> expected(data.begin(), data.end());
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

		TEST_METHOD(remove_internal_node_with_successor_as_leaf_test)
		{
			std::vector<float> data{ 3, 1, 5, 0, 2, 4, 6, 5.5 };

			ds::bin_tree::bst<float> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const float key = 5;
			bst.remove(key);

			std::vector<float> inorder;
			bst.inorder([&inorder](std::shared_ptr<ds::bin_tree::node<float>> n) {inorder.push_back(n->data); });

			std::vector<float> expected(data.begin(), data.end());
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

		TEST_METHOD(remove_internal_node_with_immediate_successor_test)
		{
			std::vector<float> data{ 3, 1, 5, 0, 2, 4, 6, 7 };

			ds::bin_tree::bst<float> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const float key = 5;
			bst.remove(key);

			std::vector<float> inorder;
			bst.inorder([&inorder](std::shared_ptr<ds::bin_tree::node<float>> n) {inorder.push_back(n->data); });

			std::vector<float> expected(data.begin(), data.end());
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

		TEST_METHOD(remove_internal_node_with_successor_having_subtree_test)
		{
			std::vector<double> data{ 3, 1, 5, 0, 2, 4, 6, 5.5, 5.9 };

			ds::bin_tree::bst<double> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const auto key = 5;
			bst.remove(key);

			std::vector<double> inorder;
			bst.inorder([&inorder](std::shared_ptr<ds::bin_tree::node<double>> n) {inorder.push_back(n->data); });

			std::vector<double> expected(data.begin(), data.end());
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

		TEST_METHOD(remove_right_leaf_node_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const auto key = 6;
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
				bst.remove(key);

				auto msg = "j: " + std::to_string(j) + "\tremoving key: " + std::to_string(key) + "\n";
				Logger::WriteMessage(msg.c_str());

				std::vector<int> inorder;
				bst.inorder([&inorder](std::shared_ptr<ds::bin_tree::node<int>> n) {inorder.push_back(n->data); });

				std::vector<int> expected(data.begin(), data.end());
				expected.erase(remove(expected.begin(), expected.end(), key), expected.end());
				sort(expected.begin(), expected.end());

				Assert::AreEqual(expected.size(), inorder.size());
				for (decltype(inorder.size()) i = 0; i < inorder.size(); ++i)
				{
					auto inner_msg = "Expected: " + std::to_string(expected[i]) + "\tActual: " + std::to_string(inorder[i]) + "\n";
					Logger::WriteMessage(inner_msg.c_str());
					Assert::AreEqual(expected[i], inorder[i]);
				}

				Logger::WriteMessage("\n");
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