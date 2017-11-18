#pragma once
#include <memory>

namespace ds
{
	namespace bin_tree
	{
		enum class node_type { k_left_child, k_right_child, k_root };

		template<typename T>
		class node
		{
		public:
			virtual ~node() = default;
			explicit node(T data, const node_type node_type) : data(data), node_type(node_type)
			{
			}

			T data;
			node_type node_type;
			std::weak_ptr<node> ancestor;
			std::shared_ptr<node> left_child;
			std::shared_ptr<node> right_child;
		};
	}
}

