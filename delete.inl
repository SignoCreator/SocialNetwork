

template<typename K,typename V>
int findKey(BTree<K,V>& t, const K& key){
    int i = 0;
    while(i < t->n && key > t->keys[i])
        i++;
    return i;
}

template<typename K,typename V>
void shiftRight(BTree<K,V>& t, int i){
    for(int j=i+1; j<t->n; j++){
        t->keys[j-1] = t->keys[j];
        t->values[j-1] = t->values[j];
    }
    t->n--;
}

template<typename K,typename V>
BTree<K,V> Predecessor(BTree<K,V>& t, unsigned int i){
    BTree<K,V> pred = t->children[i];
    while(!pred->isLeaf)
        pred = pred->children[pred->n - 1];
    return pred;
}

template<typename K,typename V>
BTree<K,V> Successor(BTree<K,V>& t, unsigned int i){
    BTree <K, V> succ = t->children[i + 1];
    while(!succ->isLeaf)
        succ = succ->children[0];
    return succ;
}

template<typename K,typename V>
void mergeTogether(BTree<K,V>& t,int i){
    // Check if i+1 is a valid index
    BTree<K,V> child = t->children[i];
    BTree<K,V> sibling = t->children[i+1];

    // Pulling a key from the current node and inserting it into (MIN_CHILDREN-1)th
    // position of child
    child->keys[MIN_CHILDREN-1] = t->keys[i];
    child->values[MIN_CHILDREN-1] = t->values[i];

    // Copying the keys from sibling to child at the end
    for (int j=0; j<sibling->n; ++j){
        child->keys[j+MIN_CHILDREN] = sibling->keys[j];
        child->values[j+MIN_CHILDREN] = sibling->values[j];
    }

    // Copying the child pointers from sibling to child
    if (!child->isLeaf){
        for(int j=0; j<=sibling->n; ++j)
            child->children[j+MIN_CHILDREN] = sibling->children[j];
    }

    // Moving all keys after i in the current node one step before -
    // to fill the gap created by moving keys[i] to child
    for (int j=i+1; j<t->n; ++j){
        t->keys[j-1] = t->keys[j];
        t->values[j-1] = t->values[j];
    }

    // Moving the child pointers after (i+1) in the current node one
    // step before
    for (int j=i+2; j<=t->n; ++j)
        t->children[j-1] = t->children[j];

    // Updating the key count of child and the current node
    child->n += sibling->n + 1;
    t->n--;
    // Freeing the memory occupied by sibling
    delete sibling;
}


template<typename K,typename V>
void borrowFromPrev(BTree<K,V>& t, int i){
    BTree<K,V> child = t->children[i];
    BTree<K,V> sibling = t->children[i-1];
    for(int j = child->n-1; j >= 0; j--){
        child->keys[j+1] = child->keys[j];
        child->values[j+1] = child->values[j];
    }
    if(!child->isLeaf){
        for(int j = child->n; j >= 0; j--)
            child->children[j+1] = child->children[j];
    }
    child->keys[0] = t->keys[i-1];
    child->values[0] = t->values[i-1];

    if(!child->isLeaf)
        child->children[0] = sibling->children[sibling->n];

    t->keys[i-1] = sibling->keys[sibling->n-1];
    t->values[i-1] = sibling->values[sibling->n-1];

    child->n++;
    sibling->n--;
}

template<typename K,typename V>
void borrowFromNext(BTree<K,V>& t, int i){
    BTree<K,V> child = t->children[i];
    BTree<K,V> sibling = t->children[i+1];
    child->keys[child->n] = t->keys[i];
    child->values[child->n] = t->values[i];
    if(!child->isLeaf)
        child->children[child->n+1] = sibling->children[0];
    t->keys[i] = sibling->keys[0];
    t->values[i] = sibling->values[0];
    for(int j = 1; j < sibling->n; j++){
        sibling->keys[j-1] = sibling->keys[j];
        sibling->values[j-1] = sibling->values[j];
    }
    if(!sibling->isLeaf){
        for(int j = 1; j <= sibling->n; j++)
            sibling->children[j-1] = sibling->children[j];
    }
    child->n++;
    sibling->n--;
}


template<typename K,typename V>
void fill(BTree<K,V>& t, int i){

    if(i != 0 && t->children[i-1]->n >= MIN_CHILDREN){

        borrowFromPrev(t, i);
    }else if(i != t->n && t->children[i+1]->n >= MIN_CHILDREN){

        borrowFromNext(t, i);
    }else{//case 3: both children have less than minChildren keys

        if(i != t->n)
            mergeTogether(t, i);
        else
            mergeTogether(t, i-1);
    }
}

template<typename K,typename V>
void removeFromNonLeaf(BTree<K,V>& t, int i){
    K key = t->keys[i];
    if(t->children[i]->n >= MIN_CHILDREN){
        BTree<K,V> pred = Predecessor(t, i);
        t->keys[i] = pred->keys[pred->n-1];
        t->values[i] = pred->values[pred->n-1];
        remove(t->children[i], t->keys[i]);
    }else if(t->children[i+1]->n >= MIN_CHILDREN){
        BTree<K,V> succ = Successor(t, i);
        t->keys[i] = succ->keys[0];
        t->values[i] = succ->values[0];
        remove(t->children[i+1], t->keys[i]);
    }else{
        mergeTogether(t, i);
        remove(t->children[i], key);
    }
}

template<typename K,typename V>
bool remove(BTree<K,V>& t, const K& key){
    int i = findKey(t, key);

    if(i < t->n && t->keys[i] == key){// key is into this node
        if(t->isLeaf)//simple case: the key is in the node and the node is a leaf
            shiftRight(t, i);
        else{
            removeFromNonLeaf(t, i);
        }
    }else{
        if(t->isLeaf)
            return false;

        bool flag = (i == t->n);

        if(t->children[i]->n < MIN_CHILDREN) // if the child has less than minChildren keys I will fill it with keys from other children (the siblings) in order to have at least minChildren keys
            fill(t, i);

        if(flag && i > t->n) // if the key is not in the last child, I will remove it from the child that precedes it
            remove(t->children[i-1], key);
        else // if the key is in the last child, I will remove it from the child that follows it
            remove(t->children[i], key);
    }
    return true;
}


