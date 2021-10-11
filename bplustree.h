//
// Created by 曹瑞辰 on 2021/9/29.
//

#ifndef CMINIDB_BPLUSTREE_H
#define CMINIDB_BPLUSTREE_H
const int HEADNODE = 0;
const int LEAFNDOE =  1;
const int INTERNALNODE = 2;
const int MAX_KEY_SIZE = 4;
typedef int NODE_TYPE;
typedef int DATA_TYPE;
typedef int KEY_TYPE;


class BNode {
protected:
    NODE_TYPE nodeType;
    int keySize;
    KEY_TYPE *keyArray;
public:
    BNode();
    virtual     ~BNode();

    NODE_TYPE   getNodeType() {return nodeType;}
    int         getKeySize() {return keySize;}
    KEY_TYPE    getKeyValue(int index) {return index < keySize && index >= 0 ? keyArray[index] : 0;}
    void        setKeySize(int size) {keySize = size;}
    void        setNodeType(NODE_TYPE nType) {nodeType = nType;}
    void        setKeyValue(int index, KEY_TYPE value) {keyArray[index] = value;}
    int         getKeyIndex(KEY_TYPE key);

    //interface function
    virtual void    splitNode() = 0;
    virtual int     searchChildIndex(KEY_TYPE key) = 0;      //use linear search, need change to binary search
};
class HeadNode : public BNode{
    int         pageSize;
    BNode       **nodeArray;
    int         nodeSize;
public:
    HeadNode();
    virtual     ~HeadNode();
    int         searchChildIndex(KEY_TYPE key);
    BNode*      getChildNode(int index){return nodeArray[index];}
};
class InternalNode  : public BNode{
    int         nodeSize;
    BNode       **nodeArray;
public:
    InternalNode();
    virtual     ~InternalNode();
    int         searchChildIndex(KEY_TYPE key);
    BNode*      getChildNode(int index){return nodeArray[index];}
};
class LeafNode : public BNode {
    LeafNode    *leftNode;
    LeafNode    *rightNode;
    DATA_TYPE   **dataArray;
public:
    LeafNode();
    virtual     ~LeafNode();
    int         searchChildIndex(KEY_TYPE key);
    DATA_TYPE*  getData(int index){return dataArray[index];}
};

class BPTree {
private:
    BNode       *root;
public:
    BPTree();
    virtual     ~BPTree();
    bool        insertNode(KEY_TYPE key, DATA_TYPE data);
    bool        searchNode(KEY_TYPE key);

private:
    bool        searchNode(KEY_TYPE key, BNode *parent);
};


#endif //CMINIDB_BPLUSTREE_H
