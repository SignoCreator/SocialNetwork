/**
 *  This file contains the implementation of the create operations of the BTree and the auxiliary functions.
 */


/*
 *  Create a new empty BTree with a given minimum number of children.
 */
template<typename K,typename V>
BTree<K,V> createEmptyBTree(int minChildren) {
    return new Node<K,V>(minChildren);
}

/*
 *  Check if a BTree is empty.
 */
template<typename K,typename V>
bool isEmpty(const BTree<K,V>& t) {
    return t == nullptr;
}

/*
 *  Insert a key-value pair in the BTree. If the key already exists, an exception is thrown.
 */
template<typename K, typename V>
void insert(BTree<K, V>& t, const K& key, const V& value, int minChildren) {

    const int MAX_CHILDREN = 2 * minChildren;
    // If the tree is empty, create a new node with the key-value pair.
    if (isEmpty(t)) {
        t = new Node<K, V>(minChildren);
        t->keys[0] = key;
        t->values[0] = value;
        t->n = 1;
    } else { // If the tree is not empty, insert the key-value pair in the tree.
        if (t->n == MAX_CHILDREN - 1) { // If the node is full, split the node.
            BTree<K,V> s = new Node<K, V>(minChildren); // Create a new node with the minimum number of children.
            s->children[0] = t;
            s->isLeaf = false; // The new node is not a leaf.
            splitChild(s, 0, minChildren);
            // Choose the child to insert the key-value pair.
            int i = 0;
            if (s->keys[0] < key)
                i++;
            insertNonFull(s->children[i], key, value, minChildren); // Insert the key-value pair in the child.
            t = s;
        } else
            insertNonFull(t, key, value, minChildren); // Insert the key-value pair in the node t.
    }
}
/*
 *  This is an auxiliary function to insert a key-value pair in a non-full node of the BTree.
 *  The function is called recursively until the key-value pair is inserted in a leaf node.
 *  Its job is to find the leaf node where the key-value pair should be inserted and to split the node if it is full.
 */
template<typename K, typename V>
void splitChild(BTree<K, V>& t, int i, int minChildren) {
    // The node t has 2 * minChildren - 1 keys, so it is full.
    BTree<K,V> y = t->children[i]; // The child to split.
    BTree<K,V> z = new Node<K, V>(minChildren); // Create a new node with the minimum number of children.
    z->isLeaf = y->isLeaf; // The new node is a leaf if the child is a leaf.
    z->n = minChildren - 1;
    // Copy the last minChildren - 1 keys and values of y to z.
    for (int j = 0; j < minChildren - 1; j++) {
        z->keys[j] = y->keys[j + minChildren];
        z->values[j] = y->values[j + minChildren];
    }
    // Copy the children of y to z if y is not a leaf.
    if (!y->isLeaf)
        for (int j = 0; j < minChildren; j++)
            z->children[j] = y->children[j + minChildren];
    // Update the number of keys of y.
    y->n = minChildren - 1;
    // Move the children of t to the right to make space for z.
    for (int j = t->n; j >= i + 1; j--)
        t->children[j + 1] = t->children[j];
    // Insert z as a child of t.
    t->children[i + 1] = z;
    // Move the keys of t to the right to make space for the key of y.
    for (int j = t->n - 1; j >= i; j--) {
        t->keys[j + 1] = t->keys[j];
        t->values[j + 1] = t->values[j];
    }
    // Insert the key of y in t.
    t->keys[i] = y->keys[minChildren - 1];
    t->values[i] = y->values[minChildren - 1];
    t->n++;
}


/*
 * This is an auxiliary function to insert a key-value pair in a non-full node of the BTree.
 * The function is called recursively until the key-value pair is inserted in a leaf node.
 */
template<typename K, typename V>
void insertNonFull(BTree<K, V>& t, const K& key, const V& value, int minChildren) {
    const int MAX_CHILDREN = 2 * minChildren;
    int i = t->n - 1;

    if (t->isLeaf) {
        while (i >= 0 && t->keys[i] > key) {

            t->keys[i + 1] = t->keys[i];
            t->values[i + 1] = t->values[i];
            i--;
        }
        // Check if the key already exists in the node
        if (i >= 0 && t->keys[i] == key)
            throw BTreeException("Key already exists","insertNonFull");
        t->keys[i + 1] = key;
        t->values[i + 1] = value;
        t->n++;
    } else {
        while (i >= 0 && t->keys[i] > key)
            i--;
        // Check if the key already exists in the node
        if (i >= 0 && t->keys[i] == key)
            throw BTreeException("Key already exists","insertNonFull");
        if (t->children[i + 1]->n == MAX_CHILDREN - 1) {
            splitChild(t, i + 1, minChildren);
            if (t->keys[i + 1] < key)
                i++;
        }
        insertNonFull(t->children[i + 1], key, value, minChildren);
    }
}













