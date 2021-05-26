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
    void BTreeInsertNonFull(int key);
    void BTreeSplitChild(int i, BTreeNode* ogNode);
    bool search(int k, int& depth);
    void print();
    void save();
    int BTreeGetKey(int key) const;
    void BTreeDelete(int key);
    void BTreeDeleteFromLeaf(int index);
    void BTreeDeleteFromNoLeaf(int index);
    int GetPredevessingChild(int index) const;
    int GetSuccessingChild(int index) const;
    void fill(int index);
    void GetFromPreviousChild(int index);
    void GetFromNextChild(int index);
    void BTreeMerge(int index);
    void deallocate();
    friend class BTree;
};
