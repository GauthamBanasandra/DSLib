#include "stdafx.h"
#include "CppUnitTest.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BST
{
	TEST_CLASS(bst)
	{
	public:
		TEST_METHOD(search_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
			ds::bst<int> bst;
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
			ds::bst<int> bst;
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
			ds::bst<int> bst;
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

			ds::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const auto key = 4;
			bst.remove(key);

			std::vector<int> inorder;
			bst.inorder([&inorder](int data) {inorder.push_back(data); });

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

			ds::bst<float> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const long key = 5;
			bst.remove(key);

			std::vector<float> inorder;
			bst.inorder([&inorder](float data) {inorder.push_back(data); });

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

			ds::bst<float> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const float key = 5;
			bst.remove(key);

			std::vector<float> inorder;
			bst.inorder([&inorder](float data) {inorder.push_back(data); });

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

			ds::bst<float> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const float key = 5;
			bst.remove(key);

			std::vector<float> inorder;
			bst.inorder([&inorder](float data) {inorder.push_back(data); });

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

			ds::bst<double> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const auto key = 5;
			bst.remove(key);

			std::vector<double> inorder;
			bst.inorder([&inorder](double data) {inorder.push_back(data); });

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

			ds::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const auto key = 6;
			bst.remove(key);

			std::vector<int> inorder;
			bst.inorder([&inorder](int data) {inorder.push_back(data); });

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

			ds::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			const auto key = 3;
			bst.remove(key);

			std::vector<int> inorder;
			bst.inorder([&inorder](int data) {inorder.push_back(data); });

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
}