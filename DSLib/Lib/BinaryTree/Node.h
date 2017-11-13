#pragma once
#include <memory>

namespace ds
{
	namespace bin_tree
	{
		template<typename T>
		class node
		{
		public:
			explicit node(T data) :data(data) {}

			T data;
			std::weak_ptr<node> ancestor;
			std::shared_ptr<node> left_child;
			std::shared_ptr<node> right_child;
		};
	}
}

