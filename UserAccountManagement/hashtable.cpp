//
//  hashtable.cpp
//  UserAccountManagement
//
//  Created by Kevin Zhang on 2016-03-26.
//  Copyright © 2016 Kevin Zhang. All rights reserved.
//

#include "hashtable.hpp"
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
    //TODO:
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
    //TODO:
    return false;
}
    
    // write your own private member functions in the following file
//#include "hashtableprivate.hpp"

//public:
    // default constructor
    // creates an array of size 101
HashTable:: HashTable(){
    size = 0;
    maxsize = 101;
    table = new SLinkedList<UserAccount>[101];
}
    
    // parameterized constructor
    // creates an array of size = smallest prime number > 2n
HashTable:: HashTable(int n){
    //TODO:
    // creates an array of size = smallest prime number > 2n
}
    
    // copy constructor
    // Creates deep copy of sourceht
HashTable:: HashTable(const HashTable& sourceht){
    //TODO:
}
    
    // destructor
HashTable::~HashTable(){
    //TODO:
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
    //TODO:
    return false;
}
    
    // Removal
    // If item exists, removes and returns true
    //   otherwise returns false
bool HashTable::Remove(UserAccount acct){
    //TODO:
    return false;
}
    
    // Search
    // Returns true if item exists, false otherwise
bool HashTable::Search(UserAccount acct) const{
    //TODO:
    return false;
}
    
    // Retrieval
    // Returns a pointer to a UserAccount object inside the hash table (linked list)
    //   if a matching parameter is found, otherwise return NULL
UserAccount* HashTable::Retrieve(UserAccount acct){
    //TODO:
    UserAccount* someAccount;
    return someAccount;
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