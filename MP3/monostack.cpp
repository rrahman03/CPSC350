#include "MonoStack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// constructor
MonoStack::MonoStack(int size, char o) : maxSize(size), order(o), top(-1) {
    stackArray = new float[maxSize];
}

// destructor
MonoStack::~MonoStack() {
    delete[] stackArray; 
}

// push function to add a value to the stack
void MonoStack::push(float value) {
    // monotonic stack
    // check if stack is in descending order
    if (order == 'd') {
        // remove elements that are smaller
        while (top != -1 && stackArray[top] < value) {
            --top; // remove element
        }
    } 
    // check if stack is in ascending order
    else if (order == 'i') {
        // remove elements that are larger
        while (top != -1 && stackArray[top] > value) {
            --top; // remove element
        }
    }

    // add new value to the stack
    if (top < maxSize - 1) {
        stackArray[++top] = value; // assign value
    }
}

// pop function
// removes and returns the top value of the stack
float MonoStack::pop() {
    // check if stack is empty
    if (top == -1) {
        return -1; // return -1 to indicate stack is empty
    }
    // return the top value of the stack
    return stackArray[top--];
}

// peek function
// returns the top value of the stack without removing it
float MonoStack::peek() const {
    // check if stack is empty
    if (top == -1) {
        return -1; // return -1 to indicate the stack is empty
    }
    return stackArray[top]; // return top value of the stack
}

// resets the stack to be empty
void MonoStack::clearStack() {
    top = -1; // indicate the stack is empty
}

// returns the count of visible seats in the stack
int MonoStack::visibleCount() const {
    return top + 1; // zero-based index
}
