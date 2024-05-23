template<typename K,typename V>
bool search(const BTree<K,V>& t, const K& key, V& value) {
    if(isEmpty(t))
        throw BTreeException("Tree is empty","search");
    int i = 0;
    while (i < t->n && key > t->keys[i])
        i++;
    if (i < t->n && key == t->keys[i]) {
        value = t->values[i];
        return true;
    }
    if (t->isLeaf){
        throw BTreeException("Key not found","search");
    }
    return search(t->children[i], key, value);
}

template<typename K,typename V>
void print(BTree<K,V>& t) {
    if (t != nullptr) {
        for (int i = 0; i < t->n; i++) {
            if (!t->isLeaf)
                print(t->children[i]);
            std::cout << " " << t->keys[i];
        }
        if (!t->isLeaf)
            print(t->children[t->n]);
    }
}
