#include <iostream>
#include <ostream>

#include "Trie.h"

int main(int argc, char* argv[])
{
	ds::trie::tree trie;
	trie.put("hello", 1);
	trie.put("home", 2);
	trie.put("hey", 3);
	std::cout << trie.get("hello") << std::endl;
	for (const auto& word : trie.collect("ho"))
	{
		std::cout << word << std::endl;
	}
	return 0;
}
