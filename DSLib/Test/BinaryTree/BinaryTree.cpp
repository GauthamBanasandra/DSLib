#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace binary_tree
{
	TEST_CLASS(BinaryTree)
	{
	public:
		TEST_METHOD(inorder_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
			ds::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			std::vector<int> inorder;

			bst.inorder([&inorder](int data) {inorder.push_back(data); });

			std::vector<int> expected(data.begin(), data.end());
			sort(expected.begin(), expected.end());
			Assert::AreEqual(expected.size(), inorder.size());

			for (decltype(inorder.size()) i = 0; i < inorder.size(); ++i)
			{
				Assert::AreEqual(expected[i], inorder[i]);
			}
		}

		TEST_METHOD(preorder_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
			ds::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			std::vector<int> preorder;

			bst.preorder([&preorder](int data) {preorder.push_back(data); });

			std::vector<int> expected{ 3, 1, 0, 2, 5, 4, 6 };
			Assert::AreEqual(expected.size(), preorder.size());

			for (decltype(preorder.size()) i = 0; i < preorder.size(); ++i)
			{
				Assert::AreEqual(expected[i], preorder[i]);
			}
		}

		TEST_METHOD(postorder_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bst<int> bst;
			for (auto item : data)
			{
				bst.insert(item);
			}

			std::vector<int> postorder;

			bst.postorder([&postorder](int data) {postorder.push_back(data); });

			std::vector<int> expected{ 0, 2, 1, 4, 6, 5, 3 };
			Assert::AreEqual(expected.size(), postorder.size());

			for (decltype(postorder.size()) i = 0; i < postorder.size(); ++i)
			{
				Assert::AreEqual(expected[i], postorder[i]);
			}
		}
	};
}