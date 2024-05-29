/*#include "btree/btree.h"
#include <iostream>
#include "string"
using namespace std;
using namespace btree;

int getChoise() {
    cout << "Menu" << endl;
    cout<< "====" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Search" << endl;
    cout << "3. Print" << endl;
    cout << "4. Remove" << endl;
    cout << "5. Exit" << endl;
    try {
        int choise;
        cout << "Enter your choise: ";
        cin >> choise;
        if (choise < 1 || choise > 5)
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
        if (choise < 1 || choise > 2)
            throw "Invalid choise";
        return choise;
    } catch (const char* msg) {
        cout << msg << endl;
        return insertMenu();
    }
}
int main() {
    BTree<string, int> t = createEmptyBTree<string, int>(2);
    int choise;
    int value;
    string key;
    while ((choise = getChoise()) != 5) {
        switch (choise) {
            case 1:
                switch (insertMenu()) {
                    case 1:
                        cout << "Enter key: ";
                        cin >> key;
                        cout << "Enter value: ";
                        cin >> value;
                        insert(t, key, value);
                        break;
                    case 2:
                        int n;
                        cout << "Enter number of elements: ";
                        cin >> n;
                        for (int i = 0; i < n; i++) {
                            insert(t, std::to_string(i) , i);
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
            case 4:
                // Aggiungi un nuovo caso per la rimozione
                cout << "Enter key to remove: ";
                cin >> key;
                try {
                    if (remove(t, key))
                        cout << "Key removed successfully." << endl;
                    else
                        cout << "Key not found." << endl;
                } catch (BTreeException& e) {
                    cout << e.what() << endl;
                }
                break;
            case 5:
                break;
            default:
                cout << "Invalid choise" << endl;
        }
    }

    return 0;
}

 */

#include "network.h"
#include <iostream>
#include <cassert>
#ifndef B_TREE_H
#include "btree.h"
#endif
using namespace network;

namespace btree {
    int MIN_CHILDREN = 2; // or whatever value you want to assign
}
int main() {
    try{
        // Create an empty network
        Network net = createEmptyNetwork();

        // Test isEmpty function
        assert(isEmpty(net));

        // Add members to the network
        assert(addMember("Alice", net));

        assert(addMember("Bob", net));

        assert(addMember("Charlie", net));

        // Test friendship functions
        assert(becomeFriends("Alice", "Bob", net));
        assert(areFriends("Alice", "Bob", net));
        assert(leaveFriendship("Alice", "Bob", net));

        assert(!areFriends("Alice", "Bob", net));
        // Test group functions

        assert(createGroup("Alice", "Group1", net));

        assert(joinGroup("Bob", "Group1", net));
        btree::print(net->groups);
        assert(leaveGroup("Bob", "Group1", net));

        // Test delete functions
        assert(deleteMember("Charlie", net));
        assert(deleteGroup("Group1", net));

        using namespace std;
        // Test list functions
        list::List memberList = members(net);
        cout<<size(memberList)<<endl;
        list::List groupList = groups(net);
        cout<<size(groupList)<<endl;
        list::List friendList = friends("Alice", net);
        cout<<size(friendList)<<endl;
        list::List memberOfList = memberOf("Alice", net);
        cout<<size(memberOfList)<<endl;
        list::List creatorOfList = creatorOf("Alice", net);
        cout<<size(creatorOfList)<<endl;

        // Test makeMoreFriends function
        assert(makeMoreFriends("Alice", net));

        std::cout << "All tests passed!" << std::endl;
    }catch (btree::BTreeException& e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}