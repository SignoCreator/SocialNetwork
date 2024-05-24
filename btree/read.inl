
#define TROVATO true
template<typename K,typename V>
bool search(const BTree<K,V>& t, const K& key, V& value) {
    if(isEmpty(t))
        throw BTreeException("Tree is empty","search");
    int i = 0;
    while (i < t->n && key > t->keys[i])
        i++;
    if (i < t->n && key == t->keys[i]) {
        value = t->values[i];
        return TROVATO;
    }
    return (t->isLeaf) ? false : search(t->children[i], key, value);
}

template<typename K,typename V>
bool exists(const BTree<K,V>& t, const K& key) {
    V value;
    return search(t, key, value);
}



template<typename K,typename V>
void print(BTree<K,V>& t) {
    if (t != EMPTY_TREE) {
        for (int i = 0; i < t->n; i++) {
            if (!t->isLeaf)
                print(t->children[i]);
            std::cout << " " << t->keys[i];
        }
        if (!t->isLeaf)
            print(t->children[t->n]);
    }
}
