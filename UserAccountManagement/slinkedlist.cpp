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
        Node<T>* currentNode = ll.front;
        while (currentNode != NULL) {
            InsertBack(currentNode->data);
            currentNode = currentNode->next;
        }
}
// helper function for deep delete
// Used by destructor and copy/assignment
template <class T>
void SLinkedList<T>::DeleteList(){
    RemoveAll();
}

//public:
// default constructor
template <class T>
SLinkedList<T>::SLinkedList(){
    size=0;
    front=NULL;
    back=NULL;
}

// copy constructor, performs deep copy of list elements
template <class T>
SLinkedList<T>::SLinkedList(const SLinkedList& ll){
        size=0;
        front=NULL;
        back=NULL;
        CopyList(ll);
}

// destructor
template <class T>
SLinkedList<T>::~SLinkedList(){
    DeleteList();
}

// MUTATORS

// Inserts an item at the front of the list
// POST:  List contains item at front
// PARAM: item = item to be inserted
template <class T>
void SLinkedList<T>::InsertFront(T item){
    if (front == NULL) {
        back = front = new Node<T>(item);
        size++;
    }else{
        Node<T>* node = new Node<T>(item);
        node->next = front;
        front = node;
        size++;
    }
}

// Inserts an item at the back of the list
// POST:  List contains item at back
// PARAM: item = item to be inserted
template <class T>
void SLinkedList<T>::InsertBack(T item){
    if (front == NULL) { // same as insert front
        back = front = new Node<T>(item);
        size++;
    }else{
        Node<T>* node = new Node<T>(item);
        back->next = node;
        back = back->next;
        size++;
    }
}

// Removes the first occurrence of the supplied parameter
// Removes and returns true if found, otherwise returns false if parameter is not found or list is empty
template <class T>
bool SLinkedList<T>::Remove(T item){
    if (Contains(item)==true){
        //begin remove procedure
        if (front->data == item) { //remove front node
            Node<T>* temp = front;
            front = front->next;
            delete temp;
            size--;
            return true;
        }else if (back->data == item){ //remove back node
            Node<T>* current = front->next;
            while (current->next != back) { //code will access violation here
                current = current->next;
            } //now current should be previous of back
            Node<T>* temp = back;
            back = current;
            back->next = NULL;
            delete temp;
            size--;
            return true;
        }else{
            //node must be somewhere in the middle
            Node<T>* beforeCurrent = front;
            Node<T>* current = front->next;
            while (current != back){
                if (current->data == item){
                    beforeCurrent->next = current->next;
                    delete current;
                    return true;
                }
                beforeCurrent = beforeCurrent->next;
                current = current->next;
            }
            size--;
            return true;
        }
    }
    return false; //item not found
}

// Removes all items in the list
template <class T>
void SLinkedList<T>::RemoveAll(){
    if (front == NULL) return;
    Node<T>* currentNode = front;
    while (currentNode != NULL) {
        front= front->next;
        delete currentNode;
        size--;
        currentNode = front;
    }
    front = NULL;
    back = NULL;
}

// ACCESSORS

// Returns size of list
template <class T>
int SLinkedList<T>::Size() const{
    return size;
}

// Returns whether the list is empty
template <class T>
bool SLinkedList<T>::IsEmpty() const{
    if (size==0) return true;
    return false;
}

// Returns existence of item
template <class T>
bool SLinkedList<T>::Contains(T item) const{
    if (front == NULL) {
        return false;
    }
    Node<T>* currentNode = front;
    while (currentNode != NULL) {
        if (currentNode->data == item) {
            return true; //item found
        }else{
            currentNode = currentNode->next;
        }
    }
    return false;
}

// Returns a pointer to the in-place list item or NULL if item not found
template <class T>
T* SLinkedList<T>::Retrieve(T item){
    T* dataFound;
    if (front == NULL) return NULL;
    Node<T>* currentNode = front;
    while (currentNode != NULL) {
        if (currentNode->data == item) {
            dataFound = &currentNode->data;
            return dataFound; //item found
        }else{
            currentNode = currentNode->next;
        }
    }
    return NULL;
}

// Returns a vector containing the list contents using push_back
template <class T>
vector<T> SLinkedList<T>:: Dump() const{
    vector<T> linkedlistcotents;
    Node<T>* currentnode = front;
    while (currentnode != NULL) {
        linkedlistcotents.push_back(currentnode->data);
        currentnode = currentnode->next;
    }
    return linkedlistcotents;
}

// OVERLOADED OPERATORS

// must work in the following cases:
// list2 = list1 -> general case
// list2 = list2 -> should do nothing
template <class T>
SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList& ll){
    if (this == &ll) {
        return *this;
    }else{
        SLinkedList* temp = new SLinkedList<T>(ll);
        front = temp->front;
        back = temp->back;
        size = temp->size;
        return *temp;
    }
}

#endif
