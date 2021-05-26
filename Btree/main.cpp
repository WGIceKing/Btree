#include <iostream>
#include <string>
#include <sstream>
#include "BTree.h"
#include "BTreeNode.h"
#include "TreeLoader.h"
#include "CacheHandler.h"

int main() {
    BTree myTree;
    std::string command;
    std::string loadedTree;
    std::string input;
    int givenDegree;
    int insertedValue;
    bool done;
    bool changesOccured = false;//if input tree was changed then it is true

    while (std::cin >> command) {
        if (command == "I") {
            std::cin >> givenDegree;
            myTree.setDegree(givenDegree);
        }

        if (command == "A") {
            changesOccured = true;
            std::cin >> insertedValue;
            myTree.insert(insertedValue);
        }

        if (command == "R") {
            changesOccured = true;
            std::cin >> insertedValue;
            myTree.remove(insertedValue);
        }

        if (command == "?") {
            std::cin >> insertedValue;
            done = false;
            int depth = 0;
            if (myTree.search(insertedValue, depth) != NULL) {
                std::cout << insertedValue << " +" << std::endl;
            }
            else {
                std::cout << insertedValue << " -" << std::endl;
            }
        }

        if (command == "P") {
            myTree.print();
        }

        if (command == "L") {
            std::cin >> givenDegree;
            myTree.setDegree(givenDegree);
            std::cin.ignore();
            std::getline(std::cin, loadedTree);
            TreeLoader loader(loadedTree);
            loader.insertToTree(myTree);
        }

        if (command == "S") {
            std::cout << myTree.getDegree() << std::endl;
            if (!changesOccured) {
                std::cout << loadedTree << std::endl;
            }
            else{
                myTree.save();
            }
        }

        if (command == "C") {
            std::cin >> insertedValue;
            std::cin.ignore();
            std::getline(std::cin, input);
            CacheHandler cache(insertedValue, input);
            cache.loadInput();
            cache.checkWithoutCache(myTree);
            cache.checkCache(myTree);
        }

        if (command == "X") {
            break;
        }
    }

    myTree.deallocate();
    return 0;
}