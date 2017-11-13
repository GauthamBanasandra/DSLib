#include "stdafx.h"
#include "CppUnitTest.h"

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
}