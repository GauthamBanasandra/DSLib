#include "Knapsack.h"

#include <iostream>
#include <vector>
#include <cassert>

enum CoinType {
	k5,
	k10,
	k20,
	k50,
	k100,
	k200,
	Count
};

struct Denomination {
	Denomination(CoinType type, std::size_t count);

	CoinType type;
	int value;
	std::size_t count;
};

Denomination::Denomination(const CoinType type, const std::size_t count) : type(type), count(count) {
	switch (type) {
	case k5: value = 5;
		break;
	case k10:value = 10;
		break;
	case k20:value = 20;
		break;
	case k50:value = 50;
		break;
	case k100:value = 100;
		break;
	case k200:value = 200;
		break;
	default:assert(false);
		break;
	}
}

std::vector<int> FlattenCurrency(const std::vector<Denomination> &currency)
{
	std::vector<int> flat;
	auto sum = 0;
	for (const auto &coins : currency)
	{
		sum += coins.count;
	}
	flat.resize(static_cast<std::size_t>(sum));
	std::size_t i = 0;
	for (const auto &coins : currency)
	{
		for (std::size_t j = 0; j < coins.count; ++j, ++i)
		{
			flat[i] = coins.value;
		}
	}
	return flat;
}

int main(int argc, char* argv[])
{
	const std::vector<Denomination> currency{
		{k5, 100},
		{k10, 1},
		{k20, 1},
		{k50, 2},
	};
	const auto coins = FlattenCurrency(currency);
	ChangeMaker change_maker(coins);
	const auto info = change_maker.Count(300); // Too slow, try 150
	if (info.is_possible)
	{
		std::cout << info.count << std::endl;
	}
	else
	{
		std::cout << "not possible" << std::endl;
	}
	return 0;
}
