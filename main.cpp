/*#include "btree.h"
#include <iostream>
#include <string>
#include "list-array.h"
using namespace std;
using namespace btree;

int getChoise() {
    cout << "Menu" << endl;
    cout<< "====" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Search" << endl;
    cout << "3. Print" << endl;
    cout << "4. Remove" << endl;
    cout << "5. Select" << endl;
    cout << "6. Exit" << endl;
    int choise;
    cout << "Enter your choise: ";
    cin >> choise;
    if (choise < 1 || choise > 6) {
        cout << "Invalid choise" << endl;
        return -1;
    }
    return choise;
}

int insertMenu(){
    //switch : insert manually or insert range
    cout << "1. Insert manually" << endl;
    cout << "2. Insert range" << endl;
    int choise;
    cout << "Enter your choise: ";
    cin >> choise;
    if (choise < 1 || choise > 2) {
        cout << "Invalid choise" << endl;
        return -1;
    }
    return choise;
}


namespace btree {
    int MIN_CHILDREN = 2; // or whatever value you want to assign
}
int main() {
    BTree<string, int> t = createEmptyBTree<string, int>(2);
    int choise;
    int value;
    string key;
    while ((choise = getChoise()) != 6) {
        if (choise == -1) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }
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
                //select data
               cout<<"select interval";
                cout<<"aaa";
                cin>>key;

                auto cond = [key](string k) { return k >= key; };

                idSelector(t, cond, l);
                cout<<"query result:"<<endl;
                cout<<list::toString(l);
                break;
                list::List l = list::createEmpty();
                btree::idSelector(t, [](string k) { return k >= "3"; }, l);
                cout<<list::toString(l);
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
        Network netw = createEmptyNetwork();
        // Test isEmpty function
        assert(isEmpty(netw));

        // Add members to the network
        std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Helen", "Ivan", "Judy", "Kevin", "Laura", "Mike", "Nancy", "Oscar", "Paul", "Quincy", "Rachel", "Steve", "Tina"};

        // Add members to the network
        for (const auto& name : names) {
            assert(addMember(name, netw));
        }
        //print
        printNetwork(netw);
        // Test friendship functions
        assert(becomeFriends("Alice", "Bob", netw));

        assert(areFriends("Alice", "Bob", netw));

        assert(leaveFriendship("Alice", "Bob", netw));


        assert(!areFriends("Alice", "Bob", netw));
        // Test group functions

        assert(createGroup("Alice", "Group1", netw));

        assert(joinGroup("Bob", "Group1", netw));
       // assert(leaveGroup("Bob", "Group1", net));

        // Test delete functions
        assert(deleteMember("Charlie", netw));
        //assert(deleteGroup("Group1", net));


        // Test list functions
    /*    list::List memberList = members(net);
        cout<<"stampo"<<endl;
        toString(memberList);
        list::List groupList = groups(net);
        cout<<size(groupList)<<endl;
        list::List friendList = friends("Alice", net);
        cout<<size(friendList)<<endl;
        list::List memberOfList = memberOf("Alice", net);
        cout<<size(memberOfList)<<endl;*/
        list::List creatorOfList = creatorOf("Alice", netw);
        cout<<size(creatorOfList)<<endl;

        // Test makeMoreFriends function
        assert(makeMoreFriends("Alice", netw));

        std::cout << "All tests passed!" << std::endl;
    }catch (btree::BTreeException& e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}
