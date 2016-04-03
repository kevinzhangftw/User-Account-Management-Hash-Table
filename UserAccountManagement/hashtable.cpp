//
//  hashtable.cpp
//  UserAccountManagement
//
//  Created by Kevin Zhang on 2016-03-26.
//  Copyright © 2016 Kevin Zhang. All rights reserved.
//

#include "hashtable.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

//private:
    //SLinkedList<UserAccount>* table;  // array of separately chained binary search trees
    //int size;    // number of items stored
    //int maxsize; // size of underlying array
    
    // hash function, uses Horner's method
    // Assume input string consists only of lower-case a to z
int HashTable::Hash(string input) const{
    int hashValue = 0;
    for (int i= 0; i < input.length(); i++) {
        int asc = input[i] - 96;
        hashValue = (hashValue*32 + asc) % maxsize;
    }
    return hashValue;
}
    
    // helper function to find smallest prime number greater than supplied parameter
int HashTable:: SmallestPrime(int n) const{
    int i = n +1;
    while (1) {
        if (IsPrime(i)) {
            return i;
        }else{
            i++;
        }
    }
    return 0;
}
    
    // helper function to determine whether a number is prime
bool HashTable:: IsPrime(int n) const{
    bool isPrime = true;
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            isPrime = false;
            return isPrime;
        }
    }
    return isPrime;
}
    
    // Resizes the hashtable into a larger array.
    // Return false if n is smaller than current array size or if n is negative.
    // Else, set array size to the smallest prime number larger than n
    //   and re-hash all contents into the new array, delete the old array and return true.
bool HashTable:: Resize(int n){
    if (n < maxsize or n < 0) {
        return false;
    }else{
        for (int i = 0; i<maxsize; i++) { //we are going to access all linkedlists
            vector<UserAccount> vectorForTableiPosition = table[i].Dump(); //vector taking a dump
            
            for (int j=0 ; j<vectorForTableiPosition.size(); j++) { //for every single acct in
                Insert(vectorForTableiPosition[j]); //rehash to new table
                size++;
            }
        }
        int newmaxsize = SmallestPrime(n); //set array size to the smallest prime number larger than n
        SLinkedList<UserAccount>* newtable= new SLinkedList<UserAccount>[newmaxsize];
        SLinkedList<UserAccount>* temp = table;
        table = newtable;
        delete[] temp;
        return true;
    }
}
    
    // write your own private member functions in the following file
//#include "hashtableprivate.hpp"

//public:
    // default constructor
    // creates an array of size 101
HashTable:: HashTable(){
    size = 0;
    maxsize = 101;
    table = new SLinkedList<UserAccount>[maxsize];
}
    
    // parameterized constructor
    // creates an array of size = smallest prime number > 2n
HashTable:: HashTable(int n){
    size = 0;
    maxsize = SmallestPrime(2*n);
    table = new SLinkedList<UserAccount>[maxsize];
}
    
    // copy constructor
    // Creates deep copy of sourceht
HashTable:: HashTable(const HashTable& sourceht){
    size = sourceht.size;
    maxsize = sourceht.maxsize;
    table = new SLinkedList<UserAccount>[maxsize];
    copy(sourceht.table, sourceht.table+sourceht.maxsize, table);
}
    
    // destructor
HashTable::~HashTable(){
    delete[] table;
}
    
    // overloaded assignment operator
HashTable& HashTable::operator=(const HashTable& sourceht){
    //TODO:
    return *this;
}
    
    // Insertion
    // If item does not already exist, inserts at back of hashed list and returns true
    //   otherwise returns false
    // If load factor (before insertion) is above 2/3, expand into a new
    //   table of smallest prime number size at least double the present table size
    //   and then insert the item.
bool HashTable::Insert(UserAccount acct){
    // If item does not already exist,
    if (Search(acct)==true) {
        return false;
    }else{
        if (LoadFactor() > 2/3) Resize(2*maxsize);
        size++; //we will insert without fail here
        //string username = acct.GetUsername();
        int arrayindex = Hash(acct.GetUsername());
        
        if (table[arrayindex].IsEmpty()) {
            SLinkedList<UserAccount> accountsOnThisLinkedList; //construct new linkedlist
            accountsOnThisLinkedList.InsertBack(acct);
            table[arrayindex] = accountsOnThisLinkedList; //attach the linked list
        }else{ //table[arrayindex]. Is not Empty
            table[arrayindex].InsertBack(acct);
        }
        return true;
    }
}
    
    // Removal
    // If item exists, removes and returns true
    //   otherwise returns false
bool HashTable::Remove(UserAccount acct){
    //TODO:
    if (Search(acct)==true) {
        return false;
    }else{
        //the item
        return true;
    }
}

    // Search
    // Returns true if item exists, false otherwise
bool HashTable::Search(UserAccount acct) const{
    string username = acct.GetUsername();
    int arrayindex = Hash(username);
    SLinkedList<UserAccount> currentaccount = table[arrayindex];
    
    //this will get me a pointer
    UserAccount* userfound=currentaccount.Retrieve(acct);
    //this will get me the bool
    return currentaccount.Contains(acct);
}
    
    // Retrieval
    // Returns a pointer to a UserAccount object inside the hash table (linked list)
    //   if a matching parameter is found, otherwise return NULL
UserAccount* HashTable::Retrieve(UserAccount acct){
    string username = acct.GetUsername();
    int arrayindex = Hash(username);
    //call the search on that slinkedlist
    SLinkedList<UserAccount> currentaccount = table[arrayindex];
    //this will get me a pointer
    UserAccount* userfound=currentaccount.Retrieve(acct);
    return userfound;
}
    
    // Returns the number of items stored in the hash table
int HashTable::Size() const{
    return size;
}
    
    // Returns the size of the underlying array
int HashTable::MaxSize() const{
    return maxsize;
}
    
    // Returns the load factor as size / maxsize.
    // Note that due to separate chaining, load factor can be > 1.
double HashTable::LoadFactor() const{
    return size/maxsize;
}
    
    // Returns a pointer to the linked list at index i
    // This will be used for grading.
    // Typically hash tables will not provide access to individual chains.
    //SLinkedList<UserAccount>* ListAt(int i)