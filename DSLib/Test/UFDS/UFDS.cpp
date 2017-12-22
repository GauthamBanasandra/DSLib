#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UFDS
{		
	TEST_CLASS(ufds)
	{
	public:
		TEST_METHOD(same_set_test)
		{
			ds::ufds ufds(10);
			ufds.union_set(1, 9);
			ufds.union_set(9, 2);
			ufds.union_set(7, 1);

			Assert::IsTrue(ufds.is_same_set(1, 7));			
			Assert::IsFalse(ufds.is_same_set(1, 3));
		}
	};
}