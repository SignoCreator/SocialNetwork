

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
        pred = pred->children[pred->n];
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
    BTree<K,V> child = t->children[i];
    BTree<K,V> sibling = t->children[i+1];
    child->keys[MIN_CHILDREN-1] = t->keys[i];
    child->values[MIN_CHILDREN-1] = t->values[i];
    for(int j = 0; j < MIN_CHILDREN-1; j++){
        child->keys[j+MIN_CHILDREN] = sibling->keys[j];
        child->values[j+MIN_CHILDREN] = sibling->values[j];
    }
    if(!child->isLeaf){
        for(int j = 0; j < MIN_CHILDREN; j++)
            child->children[j+MIN_CHILDREN] = sibling->children[j];
    }
    for(int j = i; j < t->n-1; j++){
        t->keys[j] = t->keys[j+1];
        t->values[j] = t->values[j+1];
    }
    for(int j = i+1; j < t->n; j++)
        t->children[j] = t->children[j+1];
    child->n = 2*MIN_CHILDREN-1;
    t->n--;
    delete sibling;

}

template<typename K,typename V>
void fill(BTree<K,V>& t, int i){

    if(i != 0 && t->children[i-1]->n >= MIN_CHILDREN){
        //case 1: the child that precedes the key has at least minChildren keys
        BTree<K,V> child = t->children[i];
        BTree<K,V> sibling = t->children[i-1];
        for( int j = child->n; j > 0; j--){
            child->keys[j] = child->keys[j-1];
            child->values[j] = child->values[j-1];
        }
        if(!child->isLeaf){
            for( int j = child->n+1; j > 0; j--)
                child->children[j] = child->children[j-1];
            child->children[0] = sibling->children[sibling->n];
        }
        child->keys[0] = t->keys[i-1];
        child->values[0] = t->values[i-1];
        t->keys[i-1] = sibling->keys[sibling->n-1];
        t->values[i-1] = sibling->values[sibling->n-1];
        sibling->n--;
        child->n++;
    }else if(i != t->n && t->children[i+1]->n >= MIN_CHILDREN){
        //case 2: the child that follows the key has at least minChildren keys
        BTree<K,V> child = t->children[i];
        BTree<K,V> sibling = t->children[i+1];
        child->keys[child->n] = t->keys[i];
        child->values[child->n] = t->values[i];
        if(!child->isLeaf)
            child->children[child->n+1] = sibling->children[0];
        t->keys[i] = sibling->keys[0];
        t->values[i] = sibling->values[0];
        for( int j = 0; j < sibling->n-1; j++){
            sibling->keys[j] = sibling->keys[j+1];
            sibling->values[j] = sibling->values[j+1];
        }
        if(!sibling->isLeaf){
            for( int j = 0; j < sibling->n; j++)
                sibling->children[j] = sibling->children[j+1];
        }
        sibling->n--;
        child->n++;
    }else{//case 3: both children have less than minChildren keys
        if(i != t->n)
            mergeTogether(t, i);
        else
            mergeTogether(t, i-1);
    }
}



template<typename K,typename V>
bool remove(BTree<K,V>& t, const K& key){
     V value;
     if(!search(t, key, value))return false;


     int i = findKey(t, key);

    if(i < t->n && t->keys[i] == key){// key is into this node
        if(t->isLeaf)//simple case: the key is in the node and the node is a leaf
            shiftRight(t, i);
        else{
            //complex case: the key is in the node and the node is not a leaf
            if(t->children[i]->n >= MIN_CHILDREN){
                //case 1: the child that precedes the key has at least minChildren keys
                //find the predecessor of the key
                BTree<K,V> pred = Predecessor(t, i);
                t->keys[i] = pred->keys[pred->n-1];
                t->values[i] = pred->values[pred->n-1];
                remove(t->children[i], t->keys[i]);
            }else if(t->children[i+1]->n >= MIN_CHILDREN){
                //case 2: the child that follows the key has at least minChildren keys
                //find the successor of the key
                BTree<K,V> succ = Successor(t, i);
                t->keys[i] = succ->keys[0];
                t->values[i] = succ->values[0];
                remove(t->children[i+1], t->keys[i]);

            }else {
                //case 3: both children have less than minChildren keys
                //I will merge the key with the child that follows it
                mergeTogether(t, i);
                remove(t->children[i], key);

            }
        }
    }else{
        if(t->isLeaf)
            return false;
        else{
            bool flag = (i == t->n);
            if(t->children[i]->n < MIN_CHILDREN) // if the child has less than minChildren keys I will fill it with keys from other children (the siblings) in order to have at least minChildren keys
                fill(t, i);
            if(flag && i > t->n) // if the key is not in the last child, I will remove it from the child that precedes it
                remove(t->children[i-1], key);
            else // if the key is in the last child, I will remove it from the child that follows it
                remove(t->children[i], key);
        }
    }
    return true;
}

