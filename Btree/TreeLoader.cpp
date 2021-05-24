#include "TreeLoader.h"

TreeLoader::TreeLoader(const std::string& givenTree) {
	this->tree = givenTree;
	this->levels = 0;
	this->index = 0;
	this->levelSizes = NULL;
	this->keyValues = NULL;
}

void TreeLoader::loadLevels() {
	int i = 0;
	while (tree[i] == '(' or tree[i] == ' ') {
		if (tree[i] == '(') {
			levels++;
		}
		i++;
	}
	keyValues = new int* [levels];
}

void TreeLoader::loadLevelSizes() {
	std::stringstream ss;
	ss << tree;

	levelSizes = new int[levels];
	index = new int[levels];

	for (int i = 0; i < levels; i++) {
		levelSizes[i] = 0;
	}

	int levelIndex = 0;
	int number;
	std::string word;

	while (!ss.eof()) {
		ss >> word;
		if (word == "(") {
			levelIndex++;
		}
		else if (word == ")") {
			levelIndex--;
		}
		else if (std::stringstream(word) >> number) {
			levelSizes[levelIndex - 1]++;
		}
	}
	
	for (int i = 0; i < levels; i++) {
		keyValues[i] = new int[levelSizes[i]];
		index[i] = 0;
	}
}

void TreeLoader::loadKeys() {

	std::stringstream ss;
	ss << tree;
	int levelIndex = 0;
	int number;
	std::string word;

	while (!ss.eof()) {
		ss >> word;
		if (word == "(") {
			levelIndex++;
		}
		else if (word == ")") {
			levelIndex--;
		}
		else if (std::stringstream(word) >> number) {
			keyValues[levelIndex - 1][index[levelIndex - 1]] = number;
			index[levelIndex - 1]++;
		}
	}
}

void TreeLoader::insertToTree(BTree& myTree) {
	loadLevels();
	loadLevelSizes();
	loadKeys();
	int insertedValue = 0;
	for (int i = 0; i < levels; i++) {
		if (index[i] == 1) {
			insertedValue = keyValues[i][0];
			myTree.insert(insertedValue);
		}
		else if (index[i] % 2 != 0) {
			for (int j = 0; j < index[i] / 2 + 1; j++) {
				if (j == (index[i] - 1) / 2) {
					insertedValue = keyValues[i][j];
					myTree.insert(insertedValue);
				}
				else {
					insertedValue = keyValues[i][j];
					myTree.insert(insertedValue);
					insertedValue = keyValues[i][index[i] - j - 1];
					myTree.insert(insertedValue);
				}
			}
		}
		else {
			for (int j = 0; j < index[i] / 2; j++) {
				insertedValue = keyValues[i][j];
				myTree.insert(insertedValue);
				insertedValue = keyValues[i][index[i] - j - 1];
				myTree.insert(insertedValue);
			}
		}
	}
}