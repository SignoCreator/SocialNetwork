

//controllo se iostream è già stato incluso
#ifndef SOCIALNETWORK_IOSTREAM_H
#define SOCIALNETWORK_IOSTREAM_H
#include "iostream"
#endif
#ifndef SOCIALNETWORK_BTREE_H
#define SOCIALNETWORK_BTREE_H
/*
 * B+ tree implementation
 */
namespace btree {

    const int MIN_CHILDREN = 2;
    #define EMPTY_TREE nullptr
    template<typename K,typename V>
    struct Node {
       K *keys;
       V *values;
       Node<K,V> **children;
       int n;
       bool isLeaf = false;
       Node(int minChildren = MIN_CHILDREN) {
            keys = new K[2 * minChildren - 1];
            values = new V[2 * minChildren - 1];
            children = new Node<K, V>*[2 * minChildren];
            isLeaf = true;
            n = 0;
        }

        ~Node() {
            delete[] keys;
            delete[] values;
            delete[] children;
        }
    };

    template<typename K,typename V>
    using BTree = Node<K,V>*;
    // prototypes
    template<typename K,typename V>
    BTree<K,V> createEmptyBTree(int minChildren = MIN_CHILDREN);

    template<typename K,typename V>
    bool isEmpty(const BTree<K,V>&);

    template<typename K,typename V>
    bool search(const BTree<K,V>&, const K&, V&,);

    template<typename K,typename V>
    void insert(BTree<K,V>&, const K&, const V&, int minChildren = MIN_CHILDREN);

    template<typename K,typename V>
    void insertNonFull(BTree<K,V>& t, const K& key, const V& value, int minChildren);

    template<typename K,typename V>
    void splitChild(BTree<K,V>& t, int i, int minChildren);

    template<typename K,typename V>
    bool remove(BTree<K,V>&, const K&);

    template<typename K,typename V>
    void print(BTree<K,V>& t);


    #include "btree.inl"

}

#endif //SOCIALNETWORK_BTREE_H
