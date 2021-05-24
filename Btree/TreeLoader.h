#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "BTree.h"

class TreeLoader{
	std::string tree;
	int levels;
	int* levelSizes;
	int* index;
	int** keyValues;//array of arrays (levels of a tree and its keys)
public:
	TreeLoader(const std::string& givenTree);
	void loadLevels();
	void loadLevelSizes();
	void loadKeys();
	void insertToTree(BTree& myTree);
};
