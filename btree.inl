template<typename K,typename V>
BTree<K,V> btree::createEmptyBTree() {
    BTree<K,V> t = new Node<K,V>;
    t->isLeaf = true;
    return t;
}

template<typename K,typename V>
bool btree::isEmpty(const BTree<K,V>& t) {
    return t->n == 0;
}

template<typename K,typename V>
bool btree::search(const BTree<K,V>& t, const K& key, V& value) {
    // TODO : implementare la funzione insert,
    //  ma prima creare un documento dove si spiega
    //  come funziona la funzione search
    return true;
}
template<typename K,typename V>
void btree::insertNotFull(BTree<K,V>& t, const K& key, const V& value) {
    int i = t->n - 1;
    if (t->isLeaf) {
        while (i >= 0 && key < t->keys[i]) {
            t->keys[i + 1] = t->keys[i];
            i--;
        }
        t->keys[i + 1] = key;
        t->value = value;
        t->n++;
    } else {
        while (i >= 0 && key < t->keys[i])
            i--;
        i++;
        if (t->children[i]->n == MAX_CHILDREN) {
            splitChild(t, i);
            if (key > t->keys[i])
                i++;
        }
        insertAux(t->children[i], key, value);
    }
}
template<typename K,typename V>
void btree::splitChild(int i, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    if (y->leaf == false)
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];
    C[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1];
    n = n + 1;
}

template<typename K,typename V>
bool btree::insert(BTree<K,V>& t, const K& key, const V& value) {
    // If tree is empty
    if (isEmpty(t)) {
        t->keys[0] = key;
        t->value = value;
        t->n = 1;
        return true;
    }
    // If tree is not empty
    if (t->n == MAX_CHILDREN) {
        // Split the root
        BTree<K,V> s = new Node<K,V>;
        BTree<K,V> r = t;
        t = s;
        s->isLeaf = false;
        s->children[0] = r;
        splitChild(s, 0);
        insertAux(s, key, value);
    } else
        insertAux(t, key, value);
    return true;
}

template<typename K,typename V>
bool btree::remove(BTree<K,V>& t, const K& key) {
    // TODO : implementare la funzione insert,
    //  ma prima creare un documento dove si spiega
    //  come funziona la funzione remove
    return true;
}

template<typename K,typename V>
void btree::print(BTree<K,V>& t) {
    // TODO : implementare la funzione insert,

    if (t->isLeaf) {
        for (int i = 0; i < t->n; i++)
            cout << t->keys[i] << " ";
    } else {
        for (int i = 0; i < t->n; i++) {
            print(t->children[i]);
            cout << t->keys[i] << " ";
        }
        print(t->children[t->n]);
    }
}