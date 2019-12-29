#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Permutation
{
	TEST_CLASS(Permutation)
	{
	public:

		TEST_METHOD(TestLexicographic)
		{
			std::vector<int> expected{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
			std::vector<int> actual{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };

			while (std::next_permutation(expected.begin(), expected.end()))
			{
				alg::permutation::next_lexicographic(actual);
				Assert::IsTrue(actual == expected);
			}
		}
	};
}
