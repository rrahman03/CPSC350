#ifndef MONOSTACK_H
#define MONOSTACK_H

#include <string>

class MonoStack {
private:
    float* stackArray; // dynamic array 
    int maxSize;       // maximum size of the stack
    int top;           // index of the top element in the stack
    char order;        // order of the stack ('i' for increasing, 'd' for decreasing)

public:
    // constructor
    MonoStack(int size, char o);
    // destructor
    ~MonoStack();
    // add an element to the stack
    void push(float value);
    // remove and return the top element of the stack
    float pop();
    // return the top element of the stack without removing it
    float peek() const;
    // clear the stack
    void clearStack();
    // return the number of visible elements in the stack
    int visibleCount() const;
};

#endif 
