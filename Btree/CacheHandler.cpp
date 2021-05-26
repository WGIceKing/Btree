#include "CacheHandler.h"

CacheHandler::CacheHandler(const int givenSize, const std::string& givenInput) {
	this->cacheSize = givenSize;
	this->input = givenInput;
	this->usedCache = 0;
	this->depthSumWithCache = 0;
	this->depthSumWithoutCache = 0;
	this->done = false;
}

void CacheHandler::loadInput() {
	std::stringstream ss;
	int number;
	ss << input;

	while (!ss.eof()) {
		ss >> number;
		inputList.push_back(number);
	}
}

void CacheHandler::checkCache(BTree myTree) {
	node* inList = inputList.getHead();
	while (inList != NULL) {
		int depth = 0;
		if (cache.check_value(inList->value) == true){
			inList = inList->next;
		}
		else{
			myTree.search(inList->value, depth);
			if (usedCache < cacheSize) {
				cache.push_front(inList->value);
				usedCache++;
			}
			else {
				cache.pop_back();
				cache.push_front(inList->value);
			}
			inList = inList->next;
		}
		depthSumWithCache += depth;
	}
	std::cout << "CACHE: " << depthSumWithCache << std::endl;
}

void CacheHandler::checkWithoutCache(BTree myTree) {
	node* inList = inputList.getHead();
	while (inList != NULL) {
		int depth = 0;
		done = false;
		//myTree.searchForKey(inList->value, done, depth);
		myTree.search(inList->value, depth);
		depthSumWithoutCache += depth;
		inList = inList->next;
	}
	std::cout << "NO CACHE: " << depthSumWithoutCache << " ";
}

CacheHandler::~CacheHandler() {
	cache.deallocate();
	inputList.deallocate();
}