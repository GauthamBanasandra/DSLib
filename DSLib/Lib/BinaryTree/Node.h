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
			explicit node(T data) :data(data) {}

			virtual node_type get_node_type() = 0;

			T data;
			std::weak_ptr<node> ancestor;
			std::shared_ptr<node> left_child;
			std::shared_ptr<node> right_child;
		};

		template<typename T>
		class root_node : public node<T>
		{
		public:
			explicit root_node(const T& data)
				: node<T>(data), node_type(node_type::k_root)
			{
			}

			node_type get_node_type() override { return node_type; }

			node_type node_type;
		};

		template<typename T>
		class right_node : public node<T>
		{
		public:
			explicit right_node(const T& data)
				: node<T>(data), node_type(node_type::k_right_child)
			{
			}

			node_type get_node_type() override { return node_type; }

			node_type node_type;
		};

		template<typename T>
		class left_node : public node<T>
		{
		public:
			explicit left_node(const T& data)
				: node<T>(data), node_type(node_type::k_left_child)
			{
			}

			node_type get_node_type() override { return node_type; }

			node_type node_type;
		};
	}
}

