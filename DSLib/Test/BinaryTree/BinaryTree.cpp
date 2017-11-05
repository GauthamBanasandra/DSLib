#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryTree
{	
	static std::vector<int> data;
	static ds::bin_tree::Node<int> *root;
	static std::vector<ds::bin_tree::Node<int> *> nodes;

	TEST_CLASS(BinaryTree)
	{
	public:
		TEST_CLASS_INITIALIZE(data_alloc)
		{
			data = std::vector<int>{ 3, 1, 5, 0, 2, 4, 6 };

			const auto root = new ds::bin_tree::Node<int>(data[0]);
			const auto n1 = new ds::bin_tree::Node<int>(root, data[1]);
			const auto n2 = new ds::bin_tree::Node<int>(root, data[2]);
			const auto n3 = new ds::bin_tree::Node<int>(n1, data[3]);
			const auto n4 = new ds::bin_tree::Node<int>(n1, data[4]);
			const auto n5 = new ds::bin_tree::Node<int>(n2, data[5]);
			const auto n6 = new ds::bin_tree::Node<int>(n2, data[6]);

			root->left_child = n1;
			root->right_child = n2;
			n1->left_child = n3;
			n1->right_child = n4;
			n2->left_child = n5;
			n2->right_child = n6;

			nodes = std::vector<ds::bin_tree::Node<int> *>{ root, n1, n2, n3, n4, n5, n6 };
		}

		TEST_CLASS_CLEANUP(data_clean)
		{
			for (auto node : nodes)
			{
				delete node;
			}
		}

		TEST_METHOD(inorder_test)
		{
			ds::Bst<int> bst(root);
			std::vector<int> inorder;

			bst.inorder([&inorder](int data) {inorder.push_back(data); });

			std::vector<int> expected(data.begin(), data.end());
			sort(expected.begin(), expected.end());
			for (decltype(inorder.size()) i = 0; i < inorder.size(); ++i)
			{				
				Assert::AreEqual(expected[i], inorder[i]);
			}
		}
	};
}