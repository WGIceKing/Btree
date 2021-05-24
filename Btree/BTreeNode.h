#pragma once
#include <iostream>

class BTreeNode{
    int* keys;
    int degree;
    BTreeNode** Children;
    int numOfKeys;//cur num
    bool leaf;
public:
    BTreeNode(int givendegree, bool givenleaf);
    void insertNonFull(int key);
    void splitChild(int i, BTreeNode* ogNode);
    void traverse();
    void save();
    bool searchForKey(int key, bool& done);
    int findKey(int key) const;
    void remove(int key);
    void removeFromLeaf(int index);
    void removeFromNonLeaf(int index);
    int getPred(int index) const;
    int getSucc(int index) const;
    void fill(int index);
    void borrowFromPrev(int index);
    void borrowFromNext(int index);
    void merge(int index);
    friend class BTree;
};
