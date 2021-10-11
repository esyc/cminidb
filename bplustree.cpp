//
// Created by 曹瑞辰 on 2021/9/29.
//

#include "bplustree.h"
//BNode
BNode::BNode() {

}
int BNode::getKeyIndex(KEY_TYPE key) {
    int t_index = 0;
    for(t_index = 0; t_index < keySize; t_index ++ ) {
        int t_key = keyArray[t_index];
        if(t_key >= key){
            break;
        }
    }
    return t_index;
}
// Head Node
int HeadNode::searchChildIndex(KEY_TYPE key) {
    return getKeyIndex(key);
}

// Internal Node
int InternalNode::searchChildIndex(KEY_TYPE key) {
    return getKeyIndex(key);
}

//Leaf Node
int LeafNode::searchChildIndex(KEY_TYPE key) {
    int t_index = 0;
    for(t_index = 0; t_index < keySize; t_index ++ ) {
        int t_key = keyArray[t_index];
        if(t_key == key) {
            return t_index;
        }
    }
    return -1;
}



//BPTree
bool BPTree::searchNode(KEY_TYPE key) {
    return searchNode(key, root);
}
bool BPTree::searchNode(KEY_TYPE key, BNode *parent) {

    int t_index = parent->searchChildIndex(key);
    // to judge node type to recursion
    if(parent->getNodeType() == HEADNODE) {
        return searchNode(key, static_cast<HeadNode*>(parent)->getChildNode(t_index));
    } else if(parent->getNodeType() == INTERNALNODE) {
        return searchNode(key, static_cast<InternalNode*>(parent)->getChildNode(t_index));
    } else //if  parent->getNodeType() == LEAFNDOE
        return static_cast<InternalNode*>(parent)->searchChildIndex(key) == -1;
}