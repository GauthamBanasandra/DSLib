#pragma once

#include <algorithm>
#include <vector>
#include <cassert>

namespace alg
{
	namespace permutation
	{
		template<typename T>
		void next_lexicographic(std::vector<T>& v)
		{
			auto pivot_it = std::is_sorted_until(v.rbegin(), v.rend());
			if (pivot_it == v.rend())
			{
				std::reverse(v.begin(), v.end());
				return;
			}

			auto swap_it = std::lower_bound(v.rbegin(), pivot_it, *pivot_it);
			assert(swap_it != pivot_it);
			std::swap(*pivot_it, *swap_it);
			std::reverse(v.rbegin(), pivot_it);
		}
	}
}
