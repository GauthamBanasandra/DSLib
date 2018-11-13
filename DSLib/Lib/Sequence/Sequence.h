#pragma once
#include <algorithm>
#include <vector>
#include <iterator>

namespace ds
{
	class seq
	{
	public:
		template<typename T>
		static std::vector<T> longest_increasing(const std::vector<T> &numbers);
	};

	template <typename T>
	std::vector<T> seq::longest_increasing(const std::vector<T>& numbers)
	{
		const auto numbers_len = numbers.size();
		std::vector<T> lis;
		std::vector<T> s;
		lis.reserve(numbers_len);
		s.reserve(numbers_len);

		for (const auto &number : numbers)
		{
			auto find_it = std::lower_bound(s.begin(), s.end(), number);
			auto i_insert = std::distance(s.begin(), find_it);

			if (find_it != s.end())
			{
				*find_it = number;
			}
			else
			{
				s.emplace_back(number);
			}

			const auto lis_len = lis.size();
			if (i_insert == lis_len)
			{
				lis.emplace_back(number);
			}
			else if (i_insert == lis_len - 1)
			{
				lis[i_insert] = number;
			}
		}
		return lis;
	}
}