#include "BTreeNode.h"

BTreeNode::BTreeNode(int givendegree, bool givenleaf){
    degree = givendegree;
    leaf = givenleaf;
    keys = new int[2 * degree - 1];
    Children = new BTreeNode * [2 * degree];
    numOfKeys = 0;
}

void BTreeNode::print(){
    int i;
    for (i = 0; i < numOfKeys; i++){
        if (leaf == false) {
            Children[i]->print();
        }
        std::cout << " " << keys[i];
    }

    if (leaf == false) {
        Children[i]->print();
    }
}

bool BTreeNode::search(int k, int& depth){
    depth++;
    int i = 0;
    while (i < numOfKeys && k > keys[i]) {
        i++;
    }
    if (i < numOfKeys) {
        if (keys[i] == k) {
            return true;
        }
    }
    else {
        if (keys[i - 1] == k) {
            return true;
        }
    }
    if (leaf == true) {
        return false;
    }
    return Children[i]->search(k, depth);
}

void BTreeNode::save(){
    int i;
    std::cout << " (";
    for (i = 0; i < numOfKeys; i++){
        if (leaf == false) {
            Children[i]->save();
        }
        std::cout << " " << keys[i];
    }
    if (leaf == false) {
        Children[i]->save();
    }
    else {
        std::cout << " )";
    }
}

//// INSERTION ////

void BTreeNode::BTreeInsertNonFull(int key){
    int i = numOfKeys - 1;
    if (leaf == true){
        while (i >= 0 && keys[i] > key){//locates insertion place and moves greater keys +1 above
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;//insert
        numOfKeys += 1;
    }
    else{
        while (i >= 0 && keys[i] > key) {//looking for node to insert
            i--;
        }
        if (Children[i + 1]->numOfKeys == 2 * degree - 1){
            BTreeSplitChild(i + 1, Children[i + 1]);//split if full
            if (keys[i + 1] < key) {//midle of C[i] moves up
                i++;
            }
        }
        Children[i + 1]->BTreeInsertNonFull(key);
    }
}

void BTreeNode::BTreeSplitChild(int i, BTreeNode* ogNode){
    BTreeNode* new_node = new BTreeNode(ogNode->degree, ogNode->leaf);
    new_node->numOfKeys = degree - 1;

    for (int j = 0; j < degree - 1; j++) {//move degree - 1 keys from ogNode to the new node
        new_node->keys[j] = ogNode->keys[j + degree];
    }
    if (ogNode->leaf == false){//move last children from ogNode to the new node
        for (int j = 0; j < degree; j++) {
            new_node->Children[j] = ogNode->Children[j + degree];
        }
    }

    ogNode->numOfKeys = degree - 1;

    for (int j = numOfKeys; j >= i + 1; j--) {
        Children[j + 1] = Children[j];
    }
    //insert a new node
    Children[i + 1] = new_node;
    for (int j = numOfKeys - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }

    keys[i] = ogNode->keys[degree - 1];//move mid key from og node to the new node
    numOfKeys += 1;
}

//// DELETION ////

int BTreeNode::BTreeGetKey(int key) const{
    int index = 0;
    while (index < numOfKeys && keys[index] < key) {
        ++index;
    }
    return index;
}

void BTreeNode::BTreeDelete(int key){
    int index = BTreeGetKey(key);

    if (index < numOfKeys && keys[index] == key){
        if (leaf) {
            BTreeDeleteFromLeaf(index);
        }
        else {
            BTreeDeleteFromNoLeaf(index);
        }

    }
    else{
        bool flag;
        if (leaf){
            return;
        }
        if (index == numOfKeys) {
            flag = true;
        }
        else {
            flag = false;
        }
        if (Children[index]->numOfKeys < degree) {//if is not fully filled add to it 
            fill(index);
        }
        if (flag && index > numOfKeys) {
            Children[index - 1]->BTreeDelete(key);
        }
        else {
            Children[index]->BTreeDelete(key);
        }
    }
}

void BTreeNode::BTreeDeleteFromLeaf(int index){
    for (int i = index + 1; i < numOfKeys; ++i) {
        keys[i - 1] = keys[i];//move keys 1 pos backward
    }
    numOfKeys--;
}

void BTreeNode::BTreeDeleteFromNoLeaf(int index){
    int key = keys[index];

    if (Children[index]->numOfKeys >= degree){
        int prev = GetPredevessingChild(index);
        keys[index] = prev;
        Children[index]->BTreeDelete(prev);
    }
    else if (Children[index + 1]->numOfKeys >= degree){
        int next = GetSuccessingChild(index);
        keys[index] = next;
        Children[index + 1]->BTreeDelete(next);
    }
    else{
        BTreeMerge(index);
        Children[index]->BTreeDelete(key);
    }
}

int BTreeNode::GetPredevessingChild(int index) const{//moving right
    BTreeNode* cur = Children[index];
    while (!cur->leaf) {
        cur = cur->Children[cur->numOfKeys];
    }
    return cur->keys[cur->numOfKeys - 1];//last key of a leaf
}

int BTreeNode::GetSuccessingChild(int index) const{//moving left
    BTreeNode* cur = Children[index + 1];
    while (!cur->leaf) {
        cur = cur->Children[0];
    }
    return cur->keys[0];//first key of a leaf
}

void BTreeNode::fill(int index){//filing the node
    if (index != 0 and Children[index - 1]->numOfKeys >= degree) {
        GetFromPreviousChild(index);
    }
    else if(index != numOfKeys and Children[index + 1]->numOfKeys >= degree) {
        GetFromNextChild(index);
    }
    else{
        if (index != numOfKeys) {
            BTreeMerge(index);
        }
        else {
            BTreeMerge(index - 1);
        }
    }
}

void BTreeNode::GetFromPreviousChild(int index){

    BTreeNode* child = Children[index];
    BTreeNode* sibling = Children[index - 1];

    // Moving all key in C[idx] one step ahead
    for (int i = child->numOfKeys - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];//moving 1 pos forward
    }
    if (!child->leaf){
        for (int i = child->numOfKeys; i >= 0; --i) {
            child->Children[i + 1] = child->Children[i];//moving 1 pos forward
        }
    }
    child->keys[0] = keys[index - 1];

    if (!child->leaf) {
        child->Children[0] = sibling->Children[sibling->numOfKeys];
    }

    keys[index - 1] = sibling->keys[sibling->numOfKeys - 1];
    child->numOfKeys += 1;
    sibling->numOfKeys -= 1;
}

void BTreeNode::GetFromNextChild(int index){

    BTreeNode* child = Children[index];
    BTreeNode* sibling = Children[index + 1];
    child->keys[(child->numOfKeys)] = keys[index];

    if (!(child->leaf)) {
        child->Children[(child->numOfKeys) + 1] = sibling->Children[0];
    }

    keys[index] = sibling->keys[0];
    for (int i = 1; i < sibling->numOfKeys; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    if (!sibling->leaf){
        for (int i = 1; i <= sibling->numOfKeys; ++i) {
            sibling->Children[i - 1] = sibling->Children[i];
        }
    }
    child->numOfKeys += 1;
    sibling->numOfKeys -= 1;
}

void BTreeNode::BTreeMerge(int index){//merging child with the next child (deleting the  next one)
    BTreeNode* child = Children[index];
    BTreeNode* sibling = Children[index + 1];

    child->keys[degree - 1] = keys[index];
    for (int i = 0; i < sibling->numOfKeys; ++i) {
        child->keys[i + degree] = sibling->keys[i];
    }
    if (!child->leaf){
        for (int i = 0; i <= sibling->numOfKeys; ++i) {
            child->Children[i + degree] = sibling->Children[i];
        }
    }
    for (int i = index + 1; i < numOfKeys; ++i) {
        keys[i - 1] = keys[i];
    }
    for (int i = index + 2; i <= numOfKeys; ++i) {
        Children[i - 1] = Children[i];
    }
    child->numOfKeys += sibling->numOfKeys + 1;
    numOfKeys--;
    delete(sibling);
}

//// DEALLOCATING ////

void BTreeNode::deallocate() {
    int i;
    for (i = 0; i < numOfKeys; i++) {
        if (leaf == false) {
            Children[i]->deallocate();
        }
    }

    if (leaf == false) {
        Children[i]->deallocate();
    }
    delete this;
}