#pragma once
#include "Node.h"

using big_int = unsigned long long;

template<class T>
class Bst
{
public:
	explicit Bst(tree::Node<T> *root) :root(root), height(0), node_count(0) {}
	tree::Node<T> *search(T key);
	tree::Node<T> *insert(T key);
	tree::Node<T> *successor(T key);
	tree::Node<T> *predecessor(T key);
	tree::Node<T> *find_min();
	tree::Node<T> *find_max();
	bool remove(T key);

	tree::Node<T> *root;
	big_int height;
	big_int node_count;
};