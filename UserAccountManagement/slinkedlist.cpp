//
//  slinkedlist.cpp
//  UserAccountManagement
//
//  Created by Kevin Zhang on 2016-03-26.
//  Copyright © 2016 Kevin Zhang. All rights reserved.
//

#ifdef _SLINKEDLIST_H_
//#include "slinkedlist.hpp"
//// SLinkedList member attributes
//int size; // number of items stored in list
//Node<T>* front; // references to the front
//Node<T>* back;  //  and back of the list


// helper function for deep copy
// Used by copy constructor and operator=
template <class T>
void SLinkedList<T>::CopyList(const SLinkedList& ll){
   //TODO 
}
// helper function for deep delete
// Used by destructor and copy/assignment
template <class T>
void SLinkedList<T>::DeleteList(){
   //TODO
}

//public:
// default constructor
template <class T>
SLinkedList<T>::SLinkedList(){
    //TODO
}

// copy constructor, performs deep copy of list elements
template <class T>
SLinkedList<T>::SLinkedList(const SLinkedList& ll){
    //TODO
}

// destructor
template <class T>
SLinkedList<T>::~SLinkedList(){
   //TODO
}

// MUTATORS

// Inserts an item at the front of the list
// POST:  List contains item at front
// PARAM: item = item to be inserted
template <class T>
void SLinkedList<T>::InsertFront(T item){
    //TODO
}

// Inserts an item at the back of the list
// POST:  List contains item at back
// PARAM: item = item to be inserted
template <class T>
void SLinkedList<T>::InsertBack(T item){
    //TODO
}

// Removes the first occurrence of the supplied parameter
// Removes and returns true if found, otherwise returns false if parameter is not found or list is empty
template <class T>
bool SLinkedList<T>::Remove(T item){
    //TODO
    return false;
}

// Removes all items in the list
template <class T>
void SLinkedList<T>::RemoveAll(){
    //TODO
}

// ACCESSORS

// Returns size of list
template <class T>
int SLinkedList<T>::Size() const{
    //TODO
    return 0;
}

// Returns whether the list is empty
template <class T>
bool SLinkedList<T>::IsEmpty() const{
    //TODO
    return false;
}

// Returns existence of item
template <class T>
bool SLinkedList<T>::Contains(T item) const{
    //TODO
    return false;
}

// Returns a pointer to the in-place list item or NULL if item not found
template <class T>
T* SLinkedList<T>::Retrieve(T item){
    //TODO
    return NULL;
}

// Returns a vector containing the list contents using push_back
template <class T>
vector<T> SLinkedList<T>:: Dump() const{
    //TODO
    vector<T> someVector;
    return someVector;
}

// OVERLOADED OPERATORS

// must work in the following cases:
// list2 = list1 -> general case
// list2 = list2 -> should do nothing
template <class T>
SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList& ll){
    //TODO
}

#endif
