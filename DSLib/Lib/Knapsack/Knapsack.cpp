#include "Knapsack.h"

#include <numeric>

ChangeMaker::ChangeMaker(const std::vector<int>& coins) : coins_(coins)
{
	memo_.resize(coins_.size(), std::vector<CountInfo>(std::accumulate(coins_.begin(), coins_.end(), 0) + 1));
}

// Using Knapsack to compute the minimum number of coins, when the availability of coins are limited
CountInfo ChangeMaker::Count(const std::size_t i, const int change)
{
	// A valid state is represented as {true, 0}
	// This means that the sequence of operations that have been carried out will yield change == 0
	if (change == 0)
	{
		return { true, 0 };
	}

	// An invalid state is represented as {false, -2}
	// This means that the sequence of operations that have been carried out will not yield a change == 0
	if (i >= coins_.size())
	{
		return { false, -2 };
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
	// Included this coin[i], so incrementing its count
	++include.count;

	if (!exclude.is_possible && !include.is_possible)
	{
		// Need to memoize if the sequence of operations could not yield change == 0 to avoid recomputation
		return memo = { false, -2 };
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
