#include "btree.h"
#include <iostream>

using namespace std;
using namespace btree;

int main() {
    // Create an empty BTree
    BTree<int, string> mybtree = createEmptyBTree<int, string>(4);

    // Check if the BTree is empty
    if (isEmpty(mybtree)) {
        cout << "The BTree is empty." << endl;
    } else {
        cout << "The BTree is not empty." << endl;
    }
    cout<< "start inserting\n";
    // Insert some key-value pairs into the BTree
    for (int i = 1; i <= 1000000; i++) {
        btree::insert(mybtree, i, "value" + to_string(i));
        cout << "Insertion of key " << i << " successful." << endl;
    }
    cout<< "start printing the btree\n";
    // Print the BTree
    print(mybtree);
    //search
    string value = "122";
    int key = stoi(value);
    int operations = 0;
    cout<< "Searching for key "<<value<<"..." << endl;
    bool found = search(mybtree, key, value, operations);
    if (found) {
        cout << "Key "<<key<<" found with value: " << value << endl;
    } else {
        cout << "Key "<<key<<" not found." << endl;
    }
    cout << "Number of operations: " << operations << endl;

    return 0;
}