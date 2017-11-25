#pragma once
#include "BST.h"

namespace ds
{
	template<class T>
	class avl : public ds::bst<T>
	{
	public:
		std::shared_ptr<bin_tree::node<T>> insert(T& key) override;	
	};

	template <class T>
	std::shared_ptr<bin_tree::node<T>> avl<T>::insert(T& key)
	{
		return bst<T>::insert(key);
	}
}
