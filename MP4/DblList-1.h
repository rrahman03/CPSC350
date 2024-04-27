#ifndef DBLLIST_H
#define DBLLIST_H

#include <cstddef> 
#include "Customer.h"

class DblList {
private:
    struct Node {
        Customer data; // data stored in node
        Node* next; // pointer to the next node
        Node* prev; // pointer to the previous node
        Node(Customer data): data(data), next(nullptr), prev(nullptr) {} 
    }; 

    Node* head; // pointer to the first node
    Node* tail; // pointer to the last node
    size_t size = 0; // number of elements in the list

public:
    DblList() : head(nullptr), tail(nullptr), size(0) {} // constructor
    ~DblList(); // destructor
    void clear(); // method to clear list
    void insertBack(Customer data);
    bool isEmpty() const; // method to check if the list is empty
    Customer getFront() const; // method to get the front element
    size_t getSize() const; // Returns the number of elements in the list
    void removeHead(); // method to remove the head element
    void headNext(); // move header to the next

    class Iterator {
    private:
        // pointer to current node in the iteration
        Node* node;
    public:
        // constructor initializing the iterator with a node pointer
        Iterator(Node* n) : node(n) {}

        Iterator& operator++() { // prefix increment
            if (node) node = node->next;
            return *this;
        }
        // compare two iterators
        bool operator!=(const Iterator& other) const {
            return node != other.node;
        }

        // access the data of the node pointed by the iterator
        Customer& operator*() const {
            return node->data;
        }
    };

    // begin and end methods to support iteration
    Iterator begin() {
        return Iterator(head);
    }

    // method to represent end of the list
    Iterator end() {
        return Iterator(nullptr);
    }
};

#endif
