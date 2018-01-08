#pragma once
#include <vector>

namespace ds
{
	class fen_tree
	{
	public:
		explicit fen_tree(const std::size_t size) :size_(size + 1)
		{
			f_.assign(size + 1, 0);
		}

		void update_point(std::size_t i, std::size_t value);
		std::size_t sum(std::size_t i) const;
		std::size_t range_sum(std::size_t i, std::size_t j) const;

	private:
		std::vector<std::size_t> f_;
		std::size_t size_;
	};

	inline void fen_tree::update_point(std::size_t i, const std::size_t value)
	{
		while (i < size_)
		{
			f_[i] += value;
			i += i & -i;
		}
	}

	inline std::size_t fen_tree::sum(std::size_t i) const
	{
		std::size_t s = 0;
		while (i > 0)
		{
			s += f_[i];
			i -= i & -i;
		}

		return s;
	}

	inline std::size_t fen_tree::range_sum(std::size_t i, std::size_t j) const
	{
		return sum(j) - (i == 1 ? 0 : sum(i - 1));
	}
}
