#include "Window.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

// constructor
Window::Window() : currentCustomer(nullptr), isIdle(true), idleTime(0) {}

// returns whether the window is currently idle or not
bool Window::getIdleState() const {
    return isIdle;
}

// returns accumulated idle time of the window
int Window::getIdleTime() const {
    return idleTime;
}

// assigns student to this window to be served
// resets idle time
void Window::serveCustomer(Customer* customer) {
    if (customer) {
        currentCustomer = customer; // set the current customer to the new customer
        isIdle = false; // set the window's state to not idle
        idleTime = 0; // reset idle time as it is now serving a student
    }
}

// check if the window is currently serving a customer
bool Window::isEmpty(){
    if (currentCustomer == nullptr) return (true); // returns true if no current student
    else {
        return (false);
    }
}

// updates the clock tick
void Window::updateTimeTick() {
    if (isIdle) {
        idleTime++; // if idle, increment the idle time
    } else if (currentCustomer) {
        
    }
}

// releases student from window if their service is complete
void Window::releaseCustomer() {
    if (!isIdle && currentCustomer && currentCustomer->isFinished()) {
        currentCustomer = nullptr; // clear the current customer
        isIdle = true; // set the window to idle
    }
}

// increments the idle time of window if it is idle
void Window::incrementIdleTime() {
    if (isIdle) {
        idleTime++; // incrememnt idle time only when window is idle
    }
}

// resent the idle time of the window to zero
void Window::resetIdleTime() {
    idleTime = 0;
}

// destructor
Window::~Window() {
   
}
