#pragma once
#include <vector>

namespace ds
{
	class ufds
	{
	public:
		explicit ufds(std::size_t size);
		std::size_t find_set(std::size_t i);
		bool is_same_set(std::size_t i, std::size_t j);
		void union_set(std::size_t i, std::size_t j);

		std::size_t size;
		std::vector<std::size_t> parent_index;
		std::vector<std::size_t> rank;
	};

	inline ufds::ufds(const std::size_t size) : size(size)
	{
		rank.assign(size, 0);

		for (std::size_t i = 0; i < size; ++i)
		{
			parent_index.emplace_back(i);
		}
	}

	inline std::size_t ufds::find_set(const std::size_t i)
	{
		if (parent_index[i] == i)
		{
			return i;
		}

		parent_index[i] = find_set(parent_index[i]);
		return parent_index[i];
	}

	inline bool ufds::is_same_set(const std::size_t i, const std::size_t j)
	{
		return find_set(i) == find_set(j);
	}

	inline void ufds::union_set(const std::size_t i, const std::size_t j)
	{
		if (!is_same_set(i, j))
		{
			const auto parent_i = find_set(i);
			const auto parent_j = find_set(j);
			if (rank[parent_i] > rank[parent_j])
			{
				parent_index[parent_j] = parent_i;
			}
			else
			{
				parent_index[parent_i] = parent_j;
				if (rank[parent_i] == rank[parent_j])
				{
					++rank[parent_j];
				}
			}
		}
	}
}
