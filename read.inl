template<typename K,typename V>
bool search(const BTree<K,V>& t, const K& key, V& value) {
    if(isEmpty(t))
        return false;
    int i = 0;
    while (i < t->n && key > t->keys[i])
        i++;
    if (i < t->n && key == t->keys[i]) {
        value = t->values[i];
        return true;
    }
    if (t->isLeaf){
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
            if (!t->isLeaf)
                print(t->children[i]);
            std::cout << " " << t->keys[i];
        }
        if (!t->isLeaf)
            print(t->children[t->n]);
    }
}


template<typename K,typename V>
void toList(BTree<K,V>& t, list::List& list) {
    if (t == nullptr) {
        return;
    }
    for (int i = 0; i < t->n; i++) {
        toList(t->children[i], list);
        list::add(list::size(list), t->keys[i], list);
    }
    toList(t->children[t->n], list);
}

void whereEqualsTo(BTree<string, int>& t, const string& key, const int& value,list::List& list) {
    //scorri tutto l'albero
    if (isEmpty(t)) {
        return;
    }
    for (int i = 0; i < t->n; i++) {
        whereEqualsTo(t->children[i], key, value, list);
        if (t->keys[i] == key && t->values[i] == value) {
            list::add(list::size(list), t->keys[i], list);
        }
    }
    whereEqualsTo(t->children[t->n], key, value, list);
}