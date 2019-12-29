#pragma once

#include <vector>
#include <algorithm>

namespace alg
{
	namespace sorting
	{
		template<typename T>
		class merge
		{
		public:
			explicit merge(std::vector<T>& data);

			std::vector<T>& sort();

		private:
			void merge_impl(size_t lo, size_t mid, size_t hi);
			void sort(size_t lo, size_t hi);

			std::vector<T>& data_;
			std::vector<T> aux_; // Auxiliary vector
		};

		template <typename T>
		merge<T>::merge(std::vector<T>& data) :data_{ data }
		{
			aux_.resize(data_.size());
		}

		template <typename T>
		std::vector<T>& merge<T>::sort()
		{
			if (data_.empty())
			{
				return aux_;
			}
			sort(0, data_.size() - 1);
			return data_;
		}

		template <typename T>
		void merge<T>::merge_impl(const size_t lo, const size_t mid, const size_t hi)
		{
			std::copy(data_.begin() + lo, data_.begin() + hi + 1, aux_.begin() + lo);

			auto i = lo;
			auto j = mid + 1;
			for (auto k = lo; k <= hi; ++k)
			{
				if (i > mid)
				{
					data_[k] = aux_[j++];
				}
				else if (j > hi)
				{
					data_[k] = aux_[i++];
				}
				else if (aux_[i] < aux_[j])
				{
					data_[k] = aux_[i++];
				}
				else
				{
					data_[k] = aux_[j++];
				}
			}
		}

		template <typename T>
		void merge<T>::sort(const size_t lo, const size_t hi)
		{
			if (hi <= lo)
			{
				return;
			}

			const auto mid = lo + (hi - lo) / 2;
			sort(lo, mid);
			sort(mid + 1, hi);
			merge_impl(lo, mid, hi);
		}
	}
}