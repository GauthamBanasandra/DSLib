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

			ds::bin_tree::node<int> root(data[0]);
			ds::bin_tree::node<int> n1(&root, data[1]);
			ds::bin_tree::node<int> n2(&root, data[2]);
			ds::bin_tree::node<int> n3(&n1, data[3]);
			ds::bin_tree::node<int> n4(&n1, data[4]);
			ds::bin_tree::node<int> n5(&n2, data[5]);
			ds::bin_tree::node<int> n6(&n2, data[6]);

			root.left_child = &n1;
			root.right_child = &n2;
			n1.left_child = &n3;
			n1.right_child = &n4;
			n2.left_child = &n5;
			n2.right_child = &n6;

			ds::bst<int> bst(&root);
			Assert::AreEqual(true, bst.search(0));
			Assert::AreEqual(true, bst.search(6));
			Assert::AreEqual(false, bst.search(-6));
			Assert::AreEqual(false, bst.search(7));
		}

		TEST_METHOD(successor_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::node<int> root(data[0]);
			ds::bin_tree::node<int> n1(&root, data[1]);
			ds::bin_tree::node<int> n2(&root, data[2]);
			ds::bin_tree::node<int> n3(&n1, data[3]);
			ds::bin_tree::node<int> n4(&n1, data[4]);
			ds::bin_tree::node<int> n5(&n2, data[5]);
			ds::bin_tree::node<int> n6(&n2, data[6]);

			root.left_child = &n1;
			root.right_child = &n2;
			n1.left_child = &n3;
			n1.right_child = &n4;
			n2.left_child = &n5;
			n2.right_child = &n6;

			ds::bst<int> bst(&root);
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
	};
}