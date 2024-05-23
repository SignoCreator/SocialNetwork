template<typename K,typename V>
BTree<K,V> createEmptyBTree(int minChildren) {
    BTree<K,V> t = new Node<K,V>(minChildren);
    return t;
}

template<typename K,typename V>
bool isEmpty(const BTree<K,V>& t) {
    return t == EMPTY_TREE;
}

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
    if (t->isLeaf)
        return false;
    return search(t->children[i], key, value);
}

template<typename K, typename V>
void splitChild(BTree<K, V>& t, int i, int minChildren) {

    // Init of the new node z
    BTree<K,V> y = t->children[i];
    BTree<K,V> z = new Node<K, V>(minChildren);
    // z is a leaf if y is a leaf
    z->isLeaf = y->isLeaf;
    // z has minChildren - 1 keys because we split y in two
    z->n = minChildren - 1;

    // copy of the last minChildren - 1 keys of y in z
    for (int j = 0; j < minChildren - 1; j++) {
        z->keys[j] = y->keys[j + minChildren];
        z->values[j] = y->values[j + minChildren];
    }
    if (!y->isLeaf)
        for (int j = 0; j < minChildren; j++)
            z->children[j] = y->children[j + minChildren];


    y->n = minChildren - 1;

    for (int j = t->n; j >= i + 1; j--)
        t->children[j + 1] = t->children[j];

    t->children[i + 1] = z;

    for (int j = t->n - 1; j >= i; j--) {
        t->keys[j + 1] = t->keys[j];
        t->values[j + 1] = t->values[j];
    }

    t->keys[i] = y->keys[minChildren - 1];
    t->values[i] = y->values[minChildren - 1];
    t->n++;
}


template<typename K, typename V>
void insertNonFull(BTree<K, V>& t, const K& key, const V& value, int minChildren) {
    int i = t->n - 1;

    if (t->isLeaf) {
        while (i >= 0 && t->keys[i] > key) {
            t->keys[i + 1] = t->keys[i];
            t->values[i + 1] = t->values[i];
            i--;
        }
        t->keys[i + 1] = key;
        t->values[i + 1] = value;
        t->n++;
    } else {
        while (i >= 0 && t->keys[i] > key)
            i--;
        if (t->children[i + 1]->n == 2 * minChildren - 1) {
            splitChild(t, i + 1, minChildren);
            if (t->keys[i + 1] < key)
                i++;
        }
        insertNonFull(t->children[i + 1], key, value, minChildren);
    }
}


template<typename K, typename V>
void insert(BTree<K, V>& t, const K& key, const V& value, int minChildren) {
    if (isEmpty(t)) {
        t = new Node<K, V>(minChildren);
        t->keys[0] = key;
        t->values[0] = value;
        t->n = 1;
    } else {
        if (t->n == 2 * minChildren - 1) {
            BTree<K,V> s = new Node<K, V>(minChildren);
            s->children[0] = t;
            s->isLeaf = false;
            splitChild(s, 0, minChildren);
            int i = 0;
            if (s->keys[0] < key)
                i++;
            insertNonFull(s->children[i], key, value, minChildren);
            t = s;
        } else {
            insertNonFull(t, key, value, minChildren);
        }
    }
}



template<typename K,typename V>
bool remove(BTree<K,V>& t, const K& key) {
    // TODO : implementare la funzione insert,
    //  ma prima creare un documento dove si spiega
    //  come funziona la funzione remove
    return true;
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