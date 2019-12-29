#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Sorting
{
	TEST_CLASS(Sorting)
	{
	public:

		TEST_METHOD(TestMergeSortLargeVector)
		{
			auto random_numbers = GetRandomNumbers(10000);
			auto expected(random_numbers);

			alg::sorting::merge<int> m(random_numbers);
			m.sort();

			std::sort(expected.begin(), expected.end());
			Assert::IsTrue(random_numbers == expected);
		}

	private:
		static std::vector<int> GetRandomNumbers(size_t count);
	};

	std::vector<int> Sorting::GetRandomNumbers(const size_t count)
	{
		std::vector<int> random_numbers(count);
		std::random_device dev;
		std::mt19937 rng(dev());
		rng.seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
		const std::uniform_int_distribution<std::mt19937::result_type> distribution;

		for (size_t i = 0; i < count; ++i)
		{
			random_numbers[i] = distribution(rng);
		}
		return random_numbers;
	}
}
