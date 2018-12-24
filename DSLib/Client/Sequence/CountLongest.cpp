#include "Sequence.h"

#include <vector>
#include <iostream>

struct pair
{
	pair() :l(0), m(0) {}
	pair(const int l, const int m) : l(l), m(m) {}

	bool operator<(const pair &other) const
	{
		return l <= other.l && m <= other.m;
	}

	int l;
	int m;
};

void count_longest_seq()
{
	const std::vector<pair> pairs{
		/*{4, 2},
		{2, 4},
		{3, 3},
		{1, 1},
		{5, 5}*/

		{2, 3},
		{1, 1},
		{3, 2}
	};

	std::cout << ds::seq::count_longest(pairs) << std::endl;
}