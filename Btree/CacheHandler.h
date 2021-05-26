#pragma once
#include "BTree.h"
#include "LinkedList.h"
#include <string>
#include <sstream>

class CacheHandler {
	int cacheSize;
	int usedCache;
	int depthSumWithCache;
	int depthSumWithoutCache;
	std::string input;
	LinkedList cache;
	LinkedList inputList;
	bool done;
public:
	CacheHandler(const int givenSize, const std::string& givenInput);
	void loadInput();
	void checkCache(BTree myTree);
	void checkWithoutCache(BTree myTree);
	~CacheHandler();
};
