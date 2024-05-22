#include "btree.h"
#include <iostream>

using namespace std;
using namespace btree;

int main() {
    // Create an empty BTree
    BTree<int, string> btree = createEmptyBTree<int, string>();

    // Check if the BTree is empty
    if (isEmpty(btree)) {
        cout << "The BTree is empty." << endl;
    } else {
        cout << "The BTree is not empty." << endl;
    }

    // Insert a key-value pair into the BTree
    if (insert(btree, 1, std::string("one"))) {
        cout << "Insertion successful." << endl;
    } else {
        cout << "Insertion failed." << endl;
    }

    // Search for a key in the BTree
    string value = "one";
    if (search(btree, 1, value)) {
        cout << "Found key 1 with value: " << value << endl;
    } else {
        cout << "Key 1 not found." << endl;
    }

    return 0;
}