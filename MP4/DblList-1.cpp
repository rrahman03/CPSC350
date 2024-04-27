#include <iostream>
#include <fstream>
#include <string>
#include "DblList.h"
#include "Customer.h"
#include "Window.h"

// destructor
DblList::~DblList() {
    clear(); // call clear function to deallocate all nodes
}

// function to remove the head of list
void DblList::removeHead()
{}

// get the size of the list 
size_t DblList::getSize() const{ 
    return size; // return the number of elements in the list
}

// check if the list empty
bool DblList::isEmpty() const
{
    if (head == nullptr) // check if the head pointer is null
        return (true); // return true if the list is empty
    else
        return (false); // return false if the list has elements
}

// get the front element of the list
Customer DblList::getFront() const
{
    if (head != nullptr) // checks if list is not empty
        return head->data; // return data of the head node
    
    return Customer(); // return default constructor 
}

void DblList::clear() {
    Node* current = head; // start with head of the list
    while (current != nullptr) { // loop through each node
        Node* next = current->next; // save the next node
        delete current; // delete the current node
        current = next; // move to the next node
    }
    head = nullptr; // reset head
    tail = nullptr; // reset tail
    size = 0; // reset the size of the list to 0
}

// insert an element at back of list
void DblList::insertBack(Customer data) {
    Node* newNode = new Node(data); // create a new node
    if (tail == nullptr) { // if the list is empty
        head = newNode; // set head to new node
        tail = newNode; // set tail to new node
    } else {
        tail->next = newNode; // set current tail next to new node
        newNode->prev = tail; // set the new node's previous to the current tail
        tail = newNode; // update tail to the new node
    }
    size++; // increment size of the list

}

// function to move head pointer
void DblList::headNext() {
    if (head != nullptr) { // check if the list is not empty
        head = head->next; // move the head pointer to the next node
    }
    if (head == nullptr) { // check if list is now empty
        tail = nullptr; // set tail to nullptr
    }
    return;
}

