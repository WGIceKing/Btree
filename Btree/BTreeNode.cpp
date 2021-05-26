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
        while (i >= 0 && keys[i] > key){//locates insertion place and moves greater keys +1 "forward"
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
        if (Children[i + 1]->numOfKeys == 2 * degree - 1){//check if the node is full
            BTreeSplitChild(i + 1, Children[i + 1]);//split if full
            if (keys[i + 1] < key) {//midle of C[i] moves up
                i++;
            }
        }
        Children[i + 1]->BTreeInsertNonFull(key);//if child is not full simply add a key to it
    }
}

void BTreeNode::BTreeSplitChild(int index, BTreeNode* ogNode){
    BTreeNode* new_node = new BTreeNode(ogNode->degree, ogNode->leaf);
    new_node->numOfKeys = degree - 1;

    for (int i = 0; i < degree - 1; i++) {//move (degree - 1) * keys from ogNode to the new node
        new_node->keys[i] = ogNode->keys[i + degree];
    }
    if (ogNode->leaf == false){//move last (degree)* children from ogNode to the new node
        for (int i = 0; i < degree; i++) {
            new_node->Children[i] = ogNode->Children[i + degree];
        }
    }

    ogNode->numOfKeys = degree - 1;//subtract from ogNodes number of keys

    for (int i = numOfKeys; i >= index + 1; i--) {
        Children[i + 1] = Children[i];
    }
    //insert a new node
    Children[index + 1] = new_node;
    for (int i = numOfKeys - 1; i >= index; i--) {
        keys[i + 1] = keys[i];//"move" keys to the left
    }

    keys[index] = ogNode->keys[degree - 1];//move mid key from og node to the new node
    numOfKeys += 1;
}

//// DELETION ////

int BTreeNode::BTreeGetKey(int key) const{//find a key greater or equal to key
    int index = 0;
    while (index < numOfKeys && keys[index] < key) {
        ++index;
    }
    return index;
}

void BTreeNode::BTreeDelete(int key){
    int index = BTreeGetKey(key);

    if (index < numOfKeys && keys[index] == key){//if the key was found in this node proceed to deleting it
        if (leaf) {
            BTreeDeleteFromLeaf(index);
        }
        else {
            BTreeDeleteFromNoLeaf(index);
        }

    }
    else{//if the key was not found in the current node
        bool flag;
        if (leaf){
            return;
        }
        if (index == numOfKeys) {//if the key we are looking for is within the subtree flag is true, else false
            flag = true;
        }
        else {
            flag = false;
        }
        if (Children[index]->numOfKeys < degree) {//
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

    if (Children[index]->numOfKeys >= degree){//if the predecessor of a current children has at least degree * keys 
        int prev = GetPredevessingChild(index);
        keys[index] = prev;
        Children[index]->BTreeDelete(prev);
    }
    else if (Children[index + 1]->numOfKeys >= degree){//opposite - if the succesor has at least degree * keys
        int next = GetSuccessingChild(index);
        keys[index] = next;
        Children[index + 1]->BTreeDelete(next);
    }
    else{//if couldnt take from succ and prev merge key + Children[index+1] into Children[index] -> Chgildren[index] has now 2degree-1 keys
        BTreeMerge(index);
        Children[index]->BTreeDelete(key);
    }
}

int BTreeNode::GetPredevessingChild(int index) const{//get the predecessor of keys[index]
    BTreeNode* cur = Children[index];
    while (!cur->leaf) {
        cur = cur->Children[cur->numOfKeys];
    }
    return cur->keys[cur->numOfKeys - 1];//last key of a leaf
}

int BTreeNode::GetSuccessingChild(int index) const{//get the succesor of keys[index]
    BTreeNode* cur = Children[index + 1];
    while (!cur->leaf) {
        cur = cur->Children[0];
    }
    return cur->keys[0];//first key of a leaf
}

void BTreeNode::GetFromPreviousChild(int index) {//take key from Children[index-1] and move it to Children[index]

    BTreeNode* child = Children[index];
    BTreeNode* sibling = Children[index - 1];

    // Moving all key in C[idx] one step ahead, making place for the new key
    for (int i = child->numOfKeys - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];//moving 1 pos forward
    }
    if (!child->leaf) {//if child is not a leaf move its children pointers ahead
        for (int i = child->numOfKeys; i >= 0; --i) {
            child->Children[i + 1] = child->Children[i];//moving 1 pos forward
        }
    }
    child->keys[0] = keys[index - 1];

    if (!child->leaf) {
        child->Children[0] = sibling->Children[sibling->numOfKeys];//siblings last child becomes children[index] first child
    }

    keys[index - 1] = sibling->keys[sibling->numOfKeys - 1];//taking a key from a sibling node and passing it to the parent node
    child->numOfKeys += 1;
    sibling->numOfKeys -= 1;
}

void BTreeNode::GetFromNextChild(int index) {//take a key from Children[index+1] and move it to the Children[index] as a last node

    BTreeNode* child = Children[index];
    BTreeNode* sibling = Children[index + 1];
    child->keys[(child->numOfKeys)] = keys[index];

    if (!(child->leaf)) {
        child->Children[(child->numOfKeys) + 1] = sibling->Children[0];
    }

    keys[index] = sibling->keys[0];
    for (int i = 1; i < sibling->numOfKeys; ++i) {//all keys in sibling 1 place backward
        sibling->keys[i - 1] = sibling->keys[i];
    }
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->numOfKeys; ++i) {
            sibling->Children[i - 1] = sibling->Children[i];//same for children pointers
        }
    }
    child->numOfKeys += 1;
    sibling->numOfKeys -= 1;
}

void BTreeNode::fill(int index){//filing the node when it has less than t-1 keys
    if (index != 0 and Children[index - 1]->numOfKeys >= degree) {//if prev child has >t-1 keys simply take a key from it
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

void BTreeNode::BTreeMerge(int index){//merging child with the next child (deleting the  next one)
    BTreeNode* child = Children[index];
    BTreeNode* sibling = Children[index + 1];

    child->keys[degree - 1] = keys[index];
    for (int i = 0; i < sibling->numOfKeys; ++i) {
        child->keys[i + degree] = sibling->keys[i];//moving keys from node index+1 to node index
    }
    if (!child->leaf){
        for (int i = 0; i <= sibling->numOfKeys; ++i) {
            child->Children[i + degree] = sibling->Children[i];//moving children pointers from node index+1 to children index
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