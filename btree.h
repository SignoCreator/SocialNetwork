

#ifndef SOCIALNETWORK_BTREE_H
#define SOCIALNETWORK_BTREE_H
/*
 * B+ tree implementation
 */
namespace btree {

    const int MAX_CHILDREN = 4;
    #define EMPTY_TREE nullptr
    template<typename K,typename V>
    struct Node {
        K keys[MAX_CHILDREN];
        V value;
        Node* children[MAX_CHILDREN]; // array of pointers to children
        int n = 0; // number of keys
        bool isLeaf = false;
    };

    template<typename K,typename V>
    using BTree = Node<K,V>*;
    // prototypes
    template<typename K,typename V>
    BTree<K,V> createEmptyBTree();

    template<typename K,typename V>
    bool isEmpty(const BTree<K,V>&);

    template<typename K,typename V>
    bool search(const BTree<K,V>&, const K&, V&);

    template<typename K,typename V>
    bool insert(BTree<K,V>&, const K&, const V&);

    template<typename K,typename V>
    bool remove(BTree<K,V>&, const K&);

    template<typename K,typename V>
    void insertNotFull(BTree<K,V>& t, const K& key, const V& value);

    template<typename K,typename V>
    void splitChild(BTree<K,V>& t, int i);

    template<typename K,typename V>
    void print(BTree<K,V>& t);
    #include "btree.inl"
}

#endif //SOCIALNETWORK_BTREE_H
