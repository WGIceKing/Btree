#include "BTree.h"

void BTree::insert(int key){
    if (root == NULL){
        root = new BTreeNode(degree, true);
        root->keys[0] = key;
        root->numOfKeys = 1;
    }
    else{
        if (root->numOfKeys == 2 * degree - 1){//if root full - tree grows
            BTreeNode* new_node = new BTreeNode(degree, false);
            new_node->Children[0] = root;//prev root becomes a child of a new root
            new_node->BTreeSplitChild(0, root);//from prev root move a key to a new root
            int i = 0;

            if (new_node->keys[0] < key) {
                i++;
            }
            new_node->Children[i]->BTreeInsertNonFull(key);
            root = new_node;
        }
        else {//if root is not full insert to it 
            root->BTreeInsertNonFull(key);
        }
    }
}

void BTree::remove(int key){
    if (!root){
        return;
    }
    root->BTreeDelete(key);

    if (root->numOfKeys == 0){//if root empty - a child becomes a root
        BTreeNode* oldRoot = root;
        if (root->leaf) {
            root = NULL;
        }
        else {
            root = root->Children[0];
        }
        delete oldRoot;
    }
    return;
}