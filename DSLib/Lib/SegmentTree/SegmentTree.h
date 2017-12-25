#pragma once
#include "Node.h"
#include "BinaryTree.h"

namespace ds
{
	namespace bin_tree
	{
		struct range
		{
			std::size_t lower_bound;
			std::size_t upper_bound;
		};

		class seg_tree : public binary_tree<std::size_t>
		{
		public:
			explicit seg_tree(const void* container_cookie, std::size_t size, node<std::size_t>*(*merge_nodes)(const void*, node<std::size_t>*, node<std::size_t>*));

			node<std::size_t>* query(const range& query_segment) const;

			const void* container_cookie;
			std::size_t size;
			node<std::size_t>*(*merge_nodes)(const void*, node<std::size_t>*, node<std::size_t>*);

		private:
			node<std::size_t>* build_tree(node_type type, const range& segment) const;
			node<std::size_t>* query(node<std::size_t>* n, const range& segment, const range& query_segment) const;
		};
	}
}
