

//controllo se iostream è già stato incluso
#ifndef SOCIALNETWORK_IOSTREAM_H
#define SOCIALNETWORK_IOSTREAM_H
#include "iostream"
using namespace std;
#endif
#ifndef SOCIALNETWORK_LIST_ARRAY_H
#include "list-array.h"
using namespace list;
#endif
#include "functional"
#ifndef SOCIALNETWORK_BTREE_H
#define SOCIALNETWORK_BTREE_H
/*
 * B+ tree implementation
 */
namespace btree {

    extern int MIN_CHILDREN;
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
            MIN_CHILDREN = minChildren;
            n = 0;
        }

        ~Node() {
            delete[] keys;
            delete[] values;
            delete[] children;
        }
    };

    struct BTreeException {
        std::string message;
        std::string function;
        BTreeException(const std::string& msg, const std::string& fun) : message(msg),function(fun) {}
        const char* what() const { return (message + " at function " + function).c_str(); }
    };

    template<typename K,typename V>
    using BTree = Node<K,V>*;

    template<typename K,typename V>
    BTree<K,V> createEmptyBTree(int minChildren = MIN_CHILDREN);

    template<typename K,typename V>
    bool isEmpty(const BTree<K,V>&);

    template<typename K,typename V>
    bool search(const BTree<K,V>&, const K&, V&);

    template<typename K,typename V>
    bool searchKeyAndValue(const BTree<K,V>&, const K&, V&);

    template<typename K,typename V>
    void insert(BTree<K,V>&, const K&, const V&, int minChildren = MIN_CHILDREN);

    template<typename K,typename V>
    bool remove(BTree<K,V>&, const K&);

    template<typename K,typename V>
    void print(BTree<K,V>& t);

    template<typename K,typename V>
    int findKey(BTree<K,V>& t, const K& key);

    template<typename K,typename V>
    void toList(BTree<K,V>& t, list::List& list);

    #include "create.inl"
    #include "read.inl"
    #include "update.inl"
    #include "delete.inl"

}

#endif //SOCIALNETWORK_BTREE_H
