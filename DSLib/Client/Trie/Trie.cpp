#include <iostream>
#include <ostream>

#include "Trie.h"

int main(int argc, char* argv[])
{
	ds::trie::tree trie;
	trie.put("hello", 1);
	std::cout << trie.get("hello") << std::endl;
	return 0;
}
