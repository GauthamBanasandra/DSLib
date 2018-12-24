#include "Knapsack.h"

#include <numeric>

ChangeMaker::ChangeMaker(const std::vector<int>& coins) : coins_(coins)
{
	memo_.resize(coins_.size(), std::vector<CountInfo>(std::accumulate(coins_.begin(), coins_.end(), 0) + 1));
}

CountInfo ChangeMaker::Count(const std::size_t i, const int change)
{
	if (change == 0)
	{
		return { true, 0 };
	}

	if (i >= coins_.size())
	{
		return { false, -1 };
	}

	auto &memo = memo_[i][change];
	if (memo.count != -1)
	{
		return memo;
	}

	if (coins_[i] > change)
	{
		return Count(i + 1, change);
	}

	const auto exclude = Count(i + 1, change);
	auto include = Count(i + 1, change - coins_[i]);
	++include.count;

	if (!exclude.is_possible && !include.is_possible)
	{
		return memo = { false, -1 };
	}

	if (!exclude.is_possible && include.is_possible)
	{
		return memo = include;
	}

	if (exclude.is_possible && !include.is_possible)
	{
		return memo = exclude;
	}

	if (exclude.count < include.count)
	{
		return memo = exclude;
	}
	return memo = include;
}
