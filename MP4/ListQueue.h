
#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include "DblList.h"

class ListQueue {
private:
   // DblList<T> list; // the queue uses a doubly linked list (DblList to store elements)
   DblList list; // the queue uses a doubly linked list (DblList to store elements)

public:
    // enqueue an element at the back of the queue
    void enqueue(Customer value); // adds a new element to the back of the queue

    // dequeue an element from the front of the queue
    Customer dequeue(); // removes front element from the queue and returns it

    // peek at the front element without removing it
    Customer peekFront() const; // returns the front element without removing it from the queue

    // check if the queue is empty
    bool isEmpty() const; // returns true if the queue has no elements, false otherwise

    // get the number of elements in the queue
   int getSize() const; // returns the number of elements currently in the queue

    // move queue head to next
    void moveHeadToNext();
};

//#include "ListQueue.cpp"
#endif
