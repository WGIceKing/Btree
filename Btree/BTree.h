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

    void traverse(){
        if (root != NULL) {
            root->traverse();
        }
    }

    void save(){
        if (root != NULL) {
            root->save();
        }
    }

    bool searchForKey(int key, bool& done) {
        return (root == NULL) ? false : root->searchForKey(key, done);
    }

    void insert(int key);
    void remove(int key);
};