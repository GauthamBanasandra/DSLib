#pragma once
#include <algorithm>
#include <vector>

namespace alg
{
	namespace sorting
	{
		template<typename T>
		class quick
		{
		public:
			explicit quick(std::vector<T>& data) :data_{ data } {}

			std::vector<T>& sort();

		private:
			void sort(int lo, int hi);
			int partition(int lo, int hi);

			std::vector<T>& data_;
		};

		template <typename T>
		std::vector<T>& quick<T>::sort()
		{
			if (data_.empty())
			{
				return data_;
			}
			std::random_shuffle(data_.begin(), data_.end());
			sort(0, data_.size() - 1);
			return data_;
		}

		template <typename T>
		void quick<T>::sort(const int lo, const int hi)
		{
			if (hi <= lo)
			{
				return;
			}
			const auto p = partition(lo, hi);
			sort(lo, p - 1);
			sort(p + 1, hi);
		}

		template <typename T>
		int quick<T>::partition(int lo, const int hi)
		{
			auto i = lo;
			auto j = hi + 1;
			while (true)
			{
				while (data_[++i] < data_[lo])
				{
					if (i == hi)
					{
						break;
					}
				}

				while (data_[lo] < data_[--j])
				{
					if (j == lo)
					{
						break;
					}
				}

				if (i >= j)
				{
					break;
				}
				std::swap(data_[i], data_[j]);
			}
			std::swap(data_[lo], data_[j]);
			return j;
		}
	}
}