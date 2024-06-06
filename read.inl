template<typename K,typename V>
bool search(const BTree<K,V>& t, const K& key, V& value) {
    if(isEmpty(t)){
        cout<<"Tree is empty"<<endl;
        return false;
    }

    int i = 0;
    while (i < t->n && key > t->keys[i])
        i++;
    if (i < t->n && key == t->keys[i]) {
        value = t->values[i];
        return true;
    }
    if (t->isLeaf){
        cout << "Key not found" << endl;
        return false;
    }
    return search(t->children[i], key, value);
}

template<typename K,typename V>
bool searchKeyAndValue(const BTree<K,V>& t, const K& key,const V& value) {
    if(isEmpty(t))
        throw BTreeException("Tree is empty","search");
    int i = 0;
    while (i < t->n && key > t->keys[i])
        i++;
    if (i < t->n && key == t->keys[i] && value == t->values[i]) {
        return true;
    }
    if (t->isLeaf){
        throw BTreeException("Key not found","search");
    }
    return searchKeyAndValue(t->children[i], key, value);
}


template<typename K,typename V>
void print(BTree<K,V>& t) {
    if (t != nullptr) {
        for (int i = 0; i < t->n; i++) {
            // Print the subtree rooted at child i
            if (!t->isLeaf)
                print(t->children[i]);
            // Print key and value
            std::cout << "Key: " << t->keys[i] << ", Value: " << t->values[i] << std::endl;
        }
        // Print the subtree rooted at last child
        if (!t->isLeaf)
            print(t->children[t->n]);
    }
}


template<typename K,typename V>
void toList(BTree<K,V>& t, list::List& l) {
    if (t != nullptr) {
        for (int i = 0; i < t->n; i++) {
            // Add the subtree rooted at child i to the list
            if (!t->isLeaf)
                toList(t->children[i], l);
            // Add key and value to the list
            list::add(list::size(l), t->keys[i], l);
        }
        // Add the subtree rooted at last child to the list
        if (!t->isLeaf)
            toList(t->children[t->n], l);
    }
}

template<typename K, typename V, typename Condizione>
void idSelector(Node<K, V>* const& t, Condizione cond, list::List& l) {
    if (!isEmpty(t)) {
        for (int i = 0; i < t->n; i++) {
            idSelector(t->children[i], cond, l);
            if (cond(t->keys[i], t->values[i])) {
                list::add(list::size(l), t->keys[i], l);
            }
        }
        idSelector(t->children[t->n], cond, l);
    }
}
template<typename K,typename V>
bool exists(const BTree<K,V>& t, const K& key) {
    V value;
    return search(t, key, value);
}

template<typename K,typename V>
void size(const BTree<K,V>& t,int& count) {
    if (!isEmpty(t)) {
        for (int i = 0; i < t->n; i++) {
            btree::size(t->children[i], ++count);
        }
        btree::size(t->children[t->n], ++count);
    }
}
