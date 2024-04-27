#include "Window.h"
#include "ListQueue.h"
#include "Customer.h"

void ListQueue::enqueue(Customer value) {
    list.insertBack(value); // add a new element to the end of the queue
}

void ListQueue::moveHeadToNext() { // move header to the next in the list
    list.headNext();
}

//template <typename T>
Customer ListQueue::dequeue() {
    if (!list.isEmpty()) { // check if the list is not empty before dequeing
        Customer value = list.getFront(); // gets front element of the queue
        list.removeHead(); // removes front element of the queue after retrieving it
        return value; // return the retrieved value
    }
    throw std::out_of_range("Queue is empty"); // throw an exception if the queue is empty when attempting to dequeue
}

//template <typename T>
Customer ListQueue::peekFront() const {
    if (!list.isEmpty()) { // check if list is not empty before peeking
        return list.getFront(); // returning the front element of the queue without removing it
    }
throw std::out_of_range("Queue is empty"); // throw an exception if the queue is empty when attempting to peek at the front element
}

bool ListQueue::isEmpty() const {
    return list.isEmpty(); // return true if the queue is empty, false otherwise
}

int ListQueue::getSize() const {
    return list.getSize(); // return the number of elements in the queue using the public getSize method
}


