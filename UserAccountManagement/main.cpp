
// File:        a5simpledriver.cpp
// Author:      Geoffrey Tien
// Date:        March 26, 2016
// Description: Simple test driver and UI for CMPT 225 assignment 5

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "slinkedlist.hpp"
#include "hashtable.hpp"

using namespace std;

// forward function declarations
void PrintMenu(bool loginstatus, int ulevel);
void LLTest(); //linked list test
void HTTest(); //hash table test

// program entry point
int main(){
    cout << "Entering linked list test..." << endl;
    LLTest();
    cout << "Entering hash table test..." << endl;
    HTTest();
    cout << endl;
    
    int choice = 0;
    string inputchoice;
    string inputname = "";    // currently logged in user
    string inputnewname = ""; // for adding or removing user
    string inputoldpassword1 = "";
    string inputoldpassword2 = "";
    string inputnewpassword = "";
    bool passwordmismatch = true;
    string inputlevel = "";
    int ilevel = 1;
    
    bool loggedin = false;
    int level = REGULAR_;
    
    HashTable ht;
    // insert a default admin account
    ht.Insert(UserAccount("admin", ADMIN_));
    
    while (choice != 7){
        PrintMenu(loggedin, level);
        // get the menu choice from standard input
        getline(cin, inputchoice);
        choice = atoi(inputchoice.c_str());
        
        switch (choice){
            case 1:// log in, log out
                if (!loggedin){
                    cout << "Enter username: ";
                    getline(cin, inputname);
                    cout << "Enter password: ";
                    getline(cin, inputoldpassword1);
                    if (!ht.Search(UserAccount(inputname, 0))){
                        cout << "Invalid username.\n" << endl;
                    }else{
                        UserAccount* ua = ht.Retrieve(UserAccount(inputname, 0)); // will not return NULL
                        if (inputoldpassword1 != ua->GetPassword()){
                            cout << "Invalid password.\n" << endl;
                        }else{
                            loggedin = true;
                            level = ua->GetUserLevel();
                        }
                    }
                }else{
                    cout << "Logged out.\n" << endl;
                    loggedin = false;
                    level = REGULAR_;
                    // clear local variables for next login
                    inputname = "";
                    inputnewname = "";
                    inputoldpassword1 = "";
                    inputoldpassword2 = "";
                    inputnewpassword = "";
                    passwordmismatch = true;
                }
                break;
            case 2:// change password
                if (loggedin){
                    passwordmismatch = true;
                    while (passwordmismatch && inputoldpassword1 != "quit"){
                        cout << "Enter old password or type quit to exit: ";
                        getline(cin, inputoldpassword1);
                        if (inputoldpassword1 != "quit"){
                            cout << "Enter old password again: ";
                            getline(cin, inputoldpassword2);
                            passwordmismatch = (inputoldpassword1 != inputoldpassword2);
                        }else{
                            passwordmismatch = false;
                        }
                    }
                    if (inputoldpassword1 != "quit"){
                        cout << "Enter new password: ";
                        getline(cin, inputnewpassword);
                        if (ht.Retrieve(UserAccount(inputname, 0))->SetPassword(inputoldpassword1, inputnewpassword))
                            cout << "Password updated.\n" << endl;
                        else
                            cout << "Error updating password.\n" << endl;
                    }
                }
                break;
            case 3:// admin-only, add new user
                if (loggedin && level == ADMIN_){
                    cout << "Enter new username (lowercase only): ";
                    getline(cin, inputnewname);
                    cout << "Enter access level (0 = ADMIN, 1 = REGULAR): ";
                    getline(cin, inputlevel);
                    ilevel = atoi(inputlevel.c_str());
                    if (ht.Insert(UserAccount(inputnewname, ilevel)))
                        cout << "New user " << inputnewname << " added.\n" << endl;
                    else
                        cout << "Error adding user.\n" << endl;
                }
                break;
            case 4:// admin-only, reset user password
                if (loggedin && level == ADMIN_){
                    cout << "Enter username for password reset: ";
                    getline(cin, inputnewname);
                    if (!ht.Search(UserAccount(inputnewname, 0))){
                        cout << "Invalid username.\n" << endl;
                    }else{
                        UserAccount* uap = ht.Retrieve(UserAccount(inputnewname, 0));
                        uap->SetPassword(uap->GetPassword(), "password");
                        cout << "Password for user " << uap->GetUsername() << " reset to default.\n" << endl;
                    }
                }
                break;
            case 5:// admin-only, edit user level
                if (loggedin && level == ADMIN_){
                    cout << "Enter username for access level edit: ";
                    getline(cin, inputnewname);
                    if (inputnewname == "admin"){
                        cout << "Cannot edit access level of admin.\n" << endl;
                    }else if (!ht.Search(UserAccount(inputnewname, 0))){
                        cout << "Invalid username.\n" << endl;
                    }else{
                        cout << "Enter new access level (0 = ADMIN, 1 = REGULAR): ";
                        getline(cin, inputlevel);
                        ilevel = atoi(inputlevel.c_str());
                        UserAccount* uap = ht.Retrieve(UserAccount(inputnewname, 0));
                        if (uap->SetUserLevel(ilevel))
                            cout << "Access level for user " << uap->GetUsername() << " successfully changed.\n" << endl;
                        else
                            cout << "Error setting access level for user " << uap->GetUsername() << ".\n" << endl;
                    }
                }
                break;
            case 6:// admin-only, remove user
                if (loggedin && level == ADMIN_){
                    cout << "Enter username to remove: ";
                    getline(cin, inputnewname);
                    if (inputnewname == "admin"){
                        cout << "Cannot remove admin.\n" << endl;
                    }else if (ht.Remove(UserAccount(inputnewname, 0))){
                        cout << "User " << inputnewname << " removed.\n" << endl;
                    }else{
                        cout << "Error removing user " << inputnewname << ".\n" << endl;
                    }
                }
                break;
            case 7:
                // do nothing, causes while loop to exit
                break;
            default:
                break;
        }
    }
    
    return 0;
}

void PrintMenu(bool loginstatus, int ulevel){
    if (!loginstatus){
        cout << "****************************************************\n"
        << "* Please select an option:                         *\n"
        << "* 1. Login                     7. Quit             *\n"
        << "****************************************************\n" << endl;
        cout << "Enter your choice: ";
    }else{
        if (ulevel == ADMIN_){
            cout << "****************************************************\n"
            << "* Please select an option:                         *\n"
            << "* 1. Logout                    6. Remove a user    *\n"
            << "* 2. Change password                               *\n"
            << "* 3. Add a new user                                *\n"
            << "* 4. Reset user password                           *\n"
            << "* 5. Edit user level           7. Quit             *\n"
            << "****************************************************\n" << endl;
            cout << "Enter your choice: ";
        }else{
            cout << "****************************************************\n"
            << "* Please select an option:                         *\n"
            << "* 1. Logout                    7. Quit             *\n"
            << "* 2. Change password                               *\n"
            << "****************************************************\n" << endl;
            cout << "Enter your choice: ";
        }
    }
}

void destructorTest(){
    SLinkedList<int> llx;
    
    llx.InsertBack(2);
    llx.InsertFront(1);
    llx.InsertBack(3);
    llx.InsertBack(4);
    llx.InsertBack(5);
    llx.InsertBack(10);
    llx.InsertBack(20);
}

void LLTest(){
    SLinkedList<int> lla;
    
    lla.InsertBack(2);
    lla.InsertFront(1);
    lla.InsertBack(3);
    lla.InsertBack(4);
    lla.InsertBack(5);
    lla.InsertBack(10);
    lla.InsertBack(20);
    
    //destructorTest();
    
//    lla.RemoveAll();
//    lla.Contains(5); //check to see 5 is in lla
//    
    vector<int> v1 = lla.Dump(); //get lla list in v1
//    lla.InsertBack(2);
//    lla.InsertFront(1);
//    lla.IsEmpty(); //Returns whether the list is empty
//    lla.Remove(3); 
//    lla.Retrieve(1);// Returns a pointer to the in-place list item or NULL if item not found
//    lla.Size();
    SLinkedList<int> lld;
    SLinkedList<int> lle(lld);
    vector<int> v5 = lle.Dump();
    vector<int> v4 = lld.Dump();
    
    SLinkedList<int> llb(lla);
    vector<int> v2 = llb.Dump();
    SLinkedList<int> llc = lla;
    vector<int> v3 = llc.Dump();
}

void HTTest(){
    HashTable ht1; //hash table of size 101
    HashTable ht2(5);//hash table of 10?

    
    ht2.Insert(UserAccount("admin", ADMIN_));
    ht2.Insert(UserAccount("bob", REGULAR_));
    ht2.Insert(UserAccount("cat", REGULAR_));
    ht2.Insert(UserAccount("kai", REGULAR_));
    ht2.Insert(UserAccount("kevin", REGULAR_));
    ht2.Insert(UserAccount("june", REGULAR_));
    ht2.Insert(UserAccount("henry", REGULAR_));
    ht2.Insert(UserAccount("ken", REGULAR_));
    
    bool targetfound = ht2.Search(UserAccount("bob", ADMIN_));
    cout << "target bob found before resize is "<< targetfound << endl;
    
    ht2.Insert(UserAccount("erne", REGULAR_));
    
    bool targetfound1 = ht2.Search(UserAccount("bob", ADMIN_));
    cout << "target bob found after resize is "<< targetfound1 << endl;
    
    ht2.Insert(UserAccount("john", REGULAR_));
    ht2.Insert(UserAccount("mircea", REGULAR_));
    ht2.Insert(UserAccount("jordan", REGULAR_));
    ht2.Insert(UserAccount("engadget", REGULAR_));
    ht2.Insert(UserAccount("grapes", REGULAR_));
    ht2.Insert(UserAccount("camvy", REGULAR_));
    ht2.Insert(UserAccount("transient", REGULAR_));
    ht2.Insert(UserAccount("oranges", REGULAR_));
    
    bool targetfound2 = ht2.Search(UserAccount("transient", ADMIN_));
    cout << "is tranisent found?  "<< targetfound2 << endl;
    
    //bool targetfound = ht1.Search(UserAccount("steven", ADMIN_));
    //cout << "target found is "<< targetfound << endl;
    //UserAccount* userfound = ht1.Retrieve(UserAccount("bob", REGULAR_));
    
    ht2.Size();
    ht2.MaxSize();//size of underlying array
    ht2.ListAt(0);
    ht2.LoadFactor();
    ht2.Insert(UserAccount("admin", ADMIN_));
    ht2.Remove(UserAccount("bob", REGULAR_));
    
    bool targetfound3 = ht2.Search(UserAccount("bob", REGULAR_));
    cout << "target bob found after removal is "<< targetfound3 << endl;
    
    HashTable ht3 = ht1;
}