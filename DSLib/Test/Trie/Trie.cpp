#include "pch.h"
#include "CppUnitTest.h"
#include "Trie.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Trie
{
	TEST_CLASS(Trie)
	{
	public:

		TEST_METHOD(TestPositive)
		{
			ds::trie::tree trie;
			trie.put("hello", 1);
			Assert::AreEqual(1, trie.get("hello"));
		}

		TEST_METHOD(TestNegative)
		{
			ds::trie::tree trie;
			trie.put("hello", 1);
			Assert::AreEqual(-1, trie.get("trie"));
		}
	};
}
