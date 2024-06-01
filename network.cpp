#include "btree.h"
#include "network.h"
#include <iostream>

#include "string"
using namespace std;
using namespace btree;
using namespace network;



typedef string UserIdType;
typedef string GroupIdType;
struct user;
typedef user* User;
typedef BTree<UserIdType, User> Friendships;
typedef BTree<UserIdType, User> Members;

struct user{
    UserIdType userLogin;
    Friendships friends;
};

struct groupStruct{
    User creator;
    Members members;
};

typedef BTree<GroupIdType, groupStruct> Groups;
typedef BTree<UserIdType, User> Users;

namespace network {
    struct st_Network{
        Users net;
        Groups groups;
    };
    bool validateString(string s){
        if(s == "")return false;
        for(auto c : s)
            if(!isalpha(c))return false;
        return true;
    }
    // Ritorna una network vuota
    Network createEmptyNetwork(){
        Network net = new st_Network;
        net->net = createEmptyBTree<UserIdType, User>();
        net->groups = createEmptyBTree<GroupIdType, groupStruct>();
        return net;
    }
    // Ritorna true se la network net e' vuota, false altrimenti
    bool isEmpty(const Network& net){
        return isEmpty(net->net);
    }


    // Aggiunge un membro alla network net con user_Login = usr_Log
    // Se usr_Log e' gia presente ritorna false
    // Se usr_Log e' uguale a "" ritorno false
    // Se usr_Log non contiene solo caratteri alfabetici, ritorna false
    // Altrimenti ritorna true
    bool addMember(string usr_Log, Network &net){
        if(!validateString(usr_Log))return false;
        User u = new user;
        u->userLogin = usr_Log;
        u->friends = createEmptyBTree<string, User>();
        return insert(net->net, usr_Log, u);
    }
    // Rende amici nella network net i membri con user_Login usr_Log1 e usr_Log2
    // Se usr_Log1 o usr_Log2 (o entrambi) non sono presenti in net, ritorna false
    // Se usr_Log1 e' uguale a usr_Log2, ritorna false
    // Altrimenti ritorna true (anche se sono gia amici)
    bool becomeFriends(string usr_Log1, string usr_Log2, Network &net){
        User user1, user2;
        if(usr_Log1 == usr_Log2) return false;
        if (!search(net->net, usr_Log1, user1) || !search(net->net, usr_Log2, user2)) return false;
        insert(user1->friends, usr_Log2, user2);
        insert(user2->friends, usr_Log1, user1);
        return true;
    }
    // Ritorna true se i membri con user_Login usr_Log1 e usr_Log2 nella network sono amici
    //   (chiaramente devono anche gia' essere presenti entrambi in net)
    // Altrimenti ritorna false
    bool areFriends(string usr_Log1, string usr_Log2, const Network &net){
        User user1, user2;
        return search(net->net, usr_Log1, user1) && search(user1->friends, usr_Log2, user2);
    }
    // Aggiunge un nuovo gruppo di group_Name g_Name alla network net
    // Questo gruppo ha un unico creatore che e il membro con user_Login usr_Log
    // Tutti gli amici del creatore al momento della creazione diventano membri del gruppo
    // Se non c'e' un membro in net con user_Login usr_Log, ritorna false
    // Se g_Name esiste gia', ritorna false
    // Altrimenti ritorna true
    bool createGroup(string usr_Log, string g_Name, Network &net){
        User u;
        groupStruct group;
        if(search(net->net, usr_Log, u) && !search(net->groups, g_Name, group)) {
            group.creator = u;
            group.members = createEmptyBTree<UserIdType, User>();
            insert(group.members, usr_Log, u);
            mergeTrees(group.members, u->friends);
            return insert(net->groups, g_Name, group);
        }
        return false;
    }
    // Il membro con user_Login usr_Log, diventa membro del gruppo con group_Name = g_Name
    // Ritorna true se c'e' un membro usr_Log e un gruppo g_Name
    // Altrimenti ritorna false
    bool joinGroup(string usr_Log, string g_Name, Network &net){
        User u;
        groupStruct group;
        if(search(net->net, usr_Log, u) && search(net->groups, g_Name, group))
           return insert(group.members, usr_Log, u);
        return false;
    }
    // Cancella il membro con user_Login = usr_Log dal network net
    // Cancella anche tutti i gruppi di cui questo membro e' il creatore
    // Ritorna true se tale membro esiste
    // Altrimenti ritorna false
    bool deleteMember(string usr_Log, Network &net){
        User u;
        if(search(net->net, usr_Log, u)) {
            idSelector(net->groups, [usr_Log](const GroupIdType& k, const groupStruct& g) {
                return g.creator->userLogin == usr_Log;
            }, [net](const GroupIdType& k, const groupStruct& g) {
                deleteGroup(k, net);
            });
            return remove(net->net, usr_Log);
        }
        return false;
    }
    // Cancella il gruppo con group_Name = g_Name dal network net
    // Ritorna true se un tale gruppo esiste
    // Altrimenti ritorna false
    bool deleteGroup(string g_Name, Network &net){
        return remove(net->groups, g_Name);
    }
    // Cancella l'amicizia fra il membro usr_Log1 e il membro usr_Log2
    // Se non ci sono i membri usr_Log1 o usr_Log2, ritorna false
    // Se usr_Log1 e' uguale a usr_Log2, ritorna false
    // Altrimenti ritorna true (anche se non sono amici)
    bool leaveFriendship(string usr_Log1, string usr_Log2, Network &net){
        if(usr_Log1 == usr_Log2) return false;
        User user1, user2;
        if(search(net->net, usr_Log1, user1) && search(net->net, usr_Log2, user2))
            return remove(user1->friends, usr_Log2) && remove(user2->friends, usr_Log1);
        return false;
    }
    // Il membro con user_Login = usr_Log viene rimosso dal gruppo con group_Name = g_Name
    // Se il membro e' il creatore, il gruppo vienne cancellato
    // Se non c'e' in net un membro usr_Log o un gruppo g_Name ritorna false
    // Altrimenti ritorna true (anche se il membro usr_Log non e' membro del gruppo)
    bool leaveGroup(string usr_Log, string g_Name, Network &net){
        groupStruct group;
        if(search(net->groups, g_Name, group)) {
            if(group.creator->userLogin == usr_Log)
                return deleteGroup(g_Name, net);
            return remove(group.members, usr_Log);
        }
        return false;
    }

    list::List members(const Network &net){
        list::List memberList = list::createEmpty();
        toList(net->net, memberList);
        return memberList;
    }

    list::List groups(const Network &net){
        list::List groupList = list::createEmpty();
        toList(net->groups, groupList);
        return groupList;
    }

    list::List friends(string usr_Log, const Network &net){
        User v;
        list::List friendList = list::createEmpty();
        if(search(net->net, usr_Log, v))
            toList(v->friends, friendList);
        return friendList;
    }

    list::List memberOf(string usr_Log, const Network &net){
        list::List l = list::createEmpty();
        idSelector(net->groups, [usr_Log](const GroupIdType& k, const groupStruct& g) {
            return exists(g.members, usr_Log);
        }, l);
        return l;
    }

    list::List creatorOf(string usr_Log, const Network &net){
        list::List l = list::createEmpty();
        idSelector(net->groups, [usr_Log](const GroupIdType& k, const groupStruct& g) {
            return g.creator->userLogin == usr_Log;
        }, l);
        return l;
     }

     bool makeMoreFriends(string usr_Log, Network &net){
        return true;
     }
    void printNetwork(const Network& net) {
        print(net->net);
    }
 }






