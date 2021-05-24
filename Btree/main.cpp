#include <iostream>
#include <string>
#include <sstream>
#include "BTree.h"
#include "BTreeNode.h"
#include "TreeLoader.h"

int main() {
    BTree myTree;
    std::string command;
    std::string loadedTree;
    int givenDegree;
    int insertedValue;
    bool done;

    while (std::cin >> command) {
        if (command == "I") {
            std::cin >> givenDegree;
            myTree.setDegree(givenDegree);
        }

        if (command == "A") {
            std::cin >> insertedValue;
            myTree.insert(insertedValue);
        }

        if (command == "R") {
            std::cin >> insertedValue;
            myTree.remove(insertedValue);
        }

        if (command == "?") {
            std::cin >> insertedValue;
            done = false;
            if (myTree.searchForKey(insertedValue, done) != NULL) {
                std::cout << insertedValue << " +" << std::endl;
            }
            else {
                std::cout << insertedValue << " -" << std::endl;
            }
        }

        if (command == "P") {
            myTree.traverse();
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
            //std::cout << "( ";
            myTree.save();
             //std::cout << " )" << std::endl;
        }

        if (command == "X") {
            break;
        }
    }


    return 0;
}