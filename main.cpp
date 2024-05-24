#include "btree/btree.h"
#include <iostream>

using namespace std;
using namespace btree;

int getChoise() {
    cout << "Menu" << endl;
    cout<< "====" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Search" << endl;
    cout << "3. Print" << endl;
    cout << "4. Exit" << endl;
    try {
        int choise;
        cout << "Enter your choise: ";
        cin >> choise;
        if (choise < 1 || choise > 4)
            throw "Invalid choise";
        return choise;
    } catch (const char* msg) {
        cout << msg << endl;
        return getChoise();
    }
}

int insertMenu(){
    //switch : insert manually or insert range
    cout << "1. Insert manually" << endl;
    cout << "2. Insert range" << endl;
    try {
        int choise;
        cout << "Enter your choise: ";
        cin >> choise;
        if (choise < 1 || choise > 4)
            throw "Invalid choise";
        return choise;
    } catch (const char* msg) {
        cout << msg << endl;
        return insertMenu();
    }
}
int main() {
    BTree<string, int> t = createEmptyBTree<string, int>(10);
    int choise;
    int value;
    string key;
    while ((choise = getChoise()) != 4) {
        switch (choise) {
            case 1:
                switch (insertMenu()) {
                    case 1:
                        cout << "Enter key: ";
                        cin >> key;
                        cout << "Enter value: ";
                        cin >> value;
                        try{
                            insert(t, key, value);
                        }catch (BTreeException& e){
                            cout <<  e.what() << endl;
                        }
                        break;
                    case 2:
                        int n;
                        cout << "Enter number of elements: ";
                        cin >> n;
                        for (int i = 0; i < n; i++) {
                            try{
                                insert(t, std::to_string(i) , i);
                            }catch (BTreeException& e){
                                cout << e.what() << endl;
                            }
                        }
                        break;
                }
                break;
            case 2:
                cout << "Enter key: ";
                cin >> key;
                try {
                    if (search(t, key, value))
                        cout << "Value found: " << value << endl;
                    else
                        cout << "Key not found" << endl;
                } catch (BTreeException& e) {
                    cout << e.what() << endl;
                }
                break;
            case 3:
                print(t);
                cout << endl;
                break;
        }
    }

    return 0;
}