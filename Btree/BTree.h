#pragma once
#include "BTreeNode.h"
#include <iostream>

class BTree{
    BTreeNode* root;
    int degree;
public:
    BTree(){
        root = NULL;
        degree = 0;
    }

    void setDegree(int givendegree) {
        degree = givendegree;
    }

    int getDegree() const{
        return this->degree;
    }

    void print(){
        if (root != NULL) {
            root->print();
        }
    }

    void save(){
        if (root != NULL) {
            root->save();
        }
    }

    bool search(int k, int& depth) {
        return (root == NULL) ? false : root->search(k, depth);
    }

    void insert(int key);
    void remove(int key);
    void deallocate() {
        if (root != NULL) {
            root->deallocate();
        }
    }
};