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

    bool isEmpty(const Network& net){
        return btree::isEmpty(net->net);
    }

    Network createEmptyNetwork(){
        Network net = new st_Network;
        net->net = createEmptyBTree<UserIdType, User>();
        net->groups = createEmptyBTree<GroupIdType, groupStruct>();
        return net;
    }

    bool addMember(string usr_Log, Network &net){
        User u = new user;
        u->userLogin = usr_Log;
        u->friends = createEmptyBTree<string, User>();
        try{
            insert(net->net, usr_Log, u);
            return true;
        }catch (BTreeException& e){
            return false;
        }
    }

    bool becomeFriends(string usr_Log1, string usr_Log2, Network &net){
        User user1, user2;
        if(search(net->net, usr_Log1, user1) && search(net->net, usr_Log2, user2)) {
            insert(user1->friends, usr_Log2, user2);
            insert(user2->friends, usr_Log1, user1);
            return true;
        }
        return false;
    }

    bool areFriends(string usr_Log1, string usr_Log2, const Network &net){
        User user1, user2;
        if(search(net->net, usr_Log1, user1) && search(net->net, usr_Log2, user2)) {
            User tmp;
            return search(user1->friends, usr_Log2, tmp) && tmp->userLogin == usr_Log2;
        }
        return false;
    }

    bool createGroup(string usr_Log, string g_Name, Network &net){
        User creator;
        if(!search(net->net, usr_Log, creator)) {
            return false;
        }
        groupStruct g;
        g.creator = creator;
        g.members = createEmptyBTree<string, User>();
        try{
            insert(net->groups, g_Name, g);
            return true;
        }catch (BTreeException& e){
            return false;
        }
    }

    bool joinGroup(string usr_Log, string g_Name, Network &net){
        User user;
        groupStruct group;
        if(search(net->net, usr_Log, user) && search(net->groups, g_Name, group)) {
            insert(group.members, usr_Log, user);
            return true;
        }
        return false;
    }

    bool deleteMember(string usr_Log, Network &net){
        return remove(net->net, usr_Log);
    }

    bool deleteGroup(string g_Name, Network &net){
        return remove(net->groups, g_Name);
    }

    bool leaveFriendship(string usr_Log1, string usr_Log2, Network &net){
        User user1, user2;
        if(search(net->net, usr_Log1, user1) && search(net->net, usr_Log2, user2)) {
            return remove(user1->friends, usr_Log2) && remove(user2->friends, usr_Log1);
        }
        return false;
    }

    bool leaveGroup(string usr_Log, string g_Name, Network &net){

        groupStruct group;

        if(search(net->groups, g_Name, group)) {

            if(group.creator->userLogin == usr_Log) {
                return deleteGroup(g_Name, net);
            }
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
        if(search(net->net, usr_Log, v)) {
            list::List friendList = list::createEmpty();
            toList(v->friends, friendList);
            return friendList;
        }
        return list::createEmpty();
    }

    list::List memberOf(string usr_Log, const Network &net){
        list::List l = list::createEmpty();
        return l;
    }

    list::List creatorOf(string usr_Log, const Network &net){
        list::List l = list::createEmpty();
        /* for(int i = 0; i < net->groups->size; i++){
             if(net->groups->creator == usr_Log)
                 list::add(l,net->groups->creator);
         }*/
         return l;
     }

     bool makeMoreFriends(string usr_Log, Network &net){
       /*  User u;
         if(!search(net->net, usr_Log, u))
             return false;
         for(int i = 0; i < u->friends->size; i++){
             User v;
             if(search(net->net, u->friends[i], v)){
                 for(int j = 0; j < v->friends->size; j++){
                     if(v->friends[j] != usr_Log) {
                         try {
                             insert(u->friends, v->friends[j], v->friends[j]);
                         } catch (BTreeException &e) {
                             return false;
                         }
                     }
                 }
             }
         }*/
         return true;
     }

 }






