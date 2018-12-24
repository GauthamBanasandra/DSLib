#pragma once

#include <vector>
#include <algorithm>

struct CountInfo
{
	CountInfo() :is_possible(false), count(-1) {}
	CountInfo(const bool is_possible, const long count) : is_possible(is_possible), count(count) {}

	bool is_possible;
	long count;
};

class ChangeMaker
{
public:
	explicit ChangeMaker(const std::vector<int> &coins);
	CountInfo Count(const int change) { return Count(0, change); }
private:
	CountInfo Count(std::size_t i, int change);

	const std::vector<int> &coins_;
	std::vector<std::vector<CountInfo>> memo_;
};